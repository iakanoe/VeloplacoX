#include "pragma.h"
#include "timer.h"
#include "ui.h"
#include "motors.h"
#include "CNY.h"
#include "calibration.h"
#include <xc.h>

const float kp = 1;
const float ki = 1;
const float kd = 1;
const int maxSpeed = 500;

enum {
    MENU,
    CALIB,
    RUN
};

int calcPID(const float Kp, const float Ki, const float Kd){
    static int prevErr = 0, integral = 0, err;
    unsigned long long s1 = 0, s2 = 0;
    for(int i = 0; i < 5; i++){
        const unsigned int val = getCalCNY(i);
        s1 += val * (i + 1) * 100;
        s2 += val;
    }
    const int pos = s1 / s2; // promedio ponderado | posición respecto a la linea
    prevErr = err; // guarda el error antiguo para derivada
    err = 300 - pos; // calcula el error
    integral += err; // suma el error a la integral
    return ((int) (Kp * (float) err) + (Ki * (float) integral) + (Kd * (float) (err - prevErr)));
    //calcula el PID y lo devuelve
}

void loop(){
    static char status = MENU;
    static bit cal = 0;
    int pid;
    switch(status){
        case MENU:
            setMotors(0, 0);
            setLEDs(1, cal, 0);
//            unsigned int a = getCNY(1);
//            setLEDs(a > 100, a > 500, a > 1000);
            if(getBTN1()){
                while(getBTN1()) continue;
                cal = 1;
                status = CALIB;
                break;
            }
            if(getBTN2()){
                if(cal) status = RUN;
                else {
                    setMotors(1000, 1000);
                    setLEDs(1, 1, 1);
                }
                while(getBTN2()) continue;
                break;
            }
            break;
            
        case CALIB:
            setLEDs(0, 1, 0);
            setMotors(-250, 250);
            for(int i = 0; i < 10000; i++) calibrateCNY(i % 5);
            setMotors(250, -250);
            for(int i = 0; i < 20000; i++) calibrateCNY(i % 5);
            setMotors(-250, 250);
            for(int i = 0; i < 10000; i++) calibrateCNY(i % 5);
            setMotors(0, 0);
            status = MENU;
            break;
            
        case RUN:
            setLEDs(0, 0, 1);
            pid = calcPID(kp, ki, kd);
            if(pid < 0) setMotors((maxSpeed - pid), maxSpeed);
            else setMotors(maxSpeed, (maxSpeed - pid));
            break;
    }
}

void initInterrupts(void){
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}
void main(){
    initInterrupts();
    initTimer();
    initUI();
    initMotors();
    initCNY();
    initCal();
    while(1) loop();
}
void interrupt ISR(void){
    timerInterrupt();
    cnyInterrupt();
}