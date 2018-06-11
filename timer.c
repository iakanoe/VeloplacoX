#include <xc.h>
#include "timer.h"

unsigned long millisCounter = 0;
unsigned int fractionCounter = 0;

unsigned long millis(void){
    return millisCounter;
}

void timerInterrupt(void){
    if(!INTCONbits.TMR0IF) return;
    fractionCounter += 680;
    if(1000 <= fractionCounter){
        fractionCounter -= 1000;
        millisCounter++;
    }
    INTCONbits.TMR0IF = 0;
}

void initTimer(void){
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    T0CON = 0xC4;
}
