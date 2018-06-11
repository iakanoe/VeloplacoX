#include "pragma.h"
#include "timer.h"
#include "ui.h"
#include "motors.h"
#include "CNY.h"
#include <xc.h>

enum {
    MENU
};

void loop(){
    static char status = MENU;
    switch(status){
        case MENU:
            setMotors(0, 0);
            setLEDs(1, 0, 0);
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