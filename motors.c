#include <xc.h>
#include "motors.h"

#define TRIS_MOTR TRISCbits.TRISC0
#define TRIS_MOTL TRISCbits.TRISC6
#define TRIS_MOTL_PWM TRISCbits.TRISC1
#define TRIS_MOTR_PWM TRISCbits.TRISC2

#define LAT_MOTR LATCbits.LATC0
#define LAT_MOTL LATCbits.LATC6
#define LAT_MOTR_PWM LATCbits.LATC1
#define LAT_MOTL_PWM LATCbits.LATC2

void initMotors(void){
    TRIS_MOTL = 0;
    TRIS_MOTR = 0;
    
    LAT_MOTR = 0;
    LAT_MOTL = 0;
    
    TRIS_MOTL_PWM = 0;
    TRIS_MOTR_PWM = 0;
    
    PR2 = 249;
    CCPR1L = 0;
    CCPR2L = 0;
    CCP1CONbits.DC1B = 0;
    CCP2CONbits.DC2B = 0;
    T2CON = 0x05;
    CCP1CONbits.CCP1M = 0xF;
    CCP2CONbits.CCP2M = 0xF;
}

void setMotors(signed int left, signed int right){
    setLMotor(left);
    setRMotor(right);
}

void setLMotor(signed int speed){
    LAT_MOTL = speed < 0;
    if(speed < -1000) speed = -1000;
    if(speed > 1000) speed = 1000;
    if(speed < 0) speed += 1000;
    //speed *= 1.023;
    CCP1CONbits.DC1B = speed & 3;
    CCPR1L = speed >> 2;
}

void setRMotor(signed int speed){
    LAT_MOTR = speed < 0;
    if(speed < -1000) speed = -1000;
    if(speed > 1000) speed = 1000;
    if(speed < 0) speed += 1000;
    //speed *= 1.023;
    CCP2CONbits.DC2B = speed & 3;
    CCPR2L = speed >> 2;
}