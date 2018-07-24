#include "pragma.h"
#include "timer.h"
#include "ui.h"
#include "motors.h"
#include "CNY.h"
#include "calibration.h"
#include <xc.h>

enum {
    MENU,
    RUN
};

int calcPID(float Kp, float Ki, float Kd){
    static int prevErr = 0, integral = 0, err;
    unsigned long long s1 = 0, s2 = 0;
    for(int i = 0; i < 5; i++){
        unsigned int val = getCalCNY(i);
        s1 += val * (i + 1) * 100;
        s2 += val;
    }
    int pos = s1 / s2; // promedio ponderado | posición respecto a la linea
    prevErr = err; // guarda el error antiguo para derivada
    err = 300 - pos; // calcula el error
    integral += err; // suma el error a la integral
    return ((int) (Kp * (float) err) + (Ki * (float) integral) + (Kd * (float) (err - prevErr)));
    //calcula el PID y lo devuelve
}

void loop(){
    static char status = MENU;
    int pid;
    switch(status){
        case MENU:
            setMotors(0, 0);
            setLEDs(1, 0, 0);
//            unsigned int a = getCNY(1);
//            setLEDs(a > 100, a > 500, a > 1000);
            
            break;
            
        case RUN:
            pid = calcPID(1, 0, 0);
            if(pid < 0) setMotors((/*maxSpeed -*/ pid), 0);//maxSpeed);
            else setMotors(0/*maxSpeed*/, (/*maxSpeed - */pid));
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
    while(1) loop();
}
void interrupt ISR(void){
    timerInterrupt();
    cnyInterrupt();
}