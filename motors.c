#include <xc.h>
#include "motors.h"

#define TRIS_MOTR TRISCbits.TRISC0
#define TRIS_MOTL TRISCbits.TRISC6
#define TRIS_MOTL_PWM TRISCbits.TRISC2
#define TRIS_MOTR_PWM TRISCbits.TRISC1

#define LAT_MOTR LATCbits.LATC0
#define LAT_MOTL LATCbits.LATC6
#define LAT_MOTR_PWM LATCbits.LATC2
#define LAT_MOTL_PWM LATCbits.LATC1

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
    LAT_MOTL = left <= 0;
    LAT_MOTR = right <= 0;
    if(left < 0) left = 1000 - left;
    if(right < 0) right = 1000 - right;
    if(left > 1000) left = 1000;
    if(right > 1000) right = 1000;
    left = left * 1024 / 1000;
    right = right * 1024 / 1000;
    CCP2CONbits.DC2B = left & 3;
    CCP1CONbits.DC1B = right & 3;
    CCPR2L = left >> 2;
    CCPR1L = right >> 2;
}