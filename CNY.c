#include <xc.h>
#include "CNY.h"

#define TRIS_CNY1 TRISAbits.RA5
#define TRIS_CNY2 TRISAbits.RA3
#define TRIS_CNY3 TRISAbits.RA2
#define TRIS_CNY4 TRISAbits.RA1
#define TRIS_CNY5 TRISAbits.RA0

const unsigned char channels[] = {4, 3, 2, 1, 0};

#ifdef CNY_ADVANCED
unsigned char actualChannel = 0;
unsigned int data[] = {0, 0, 0, 0, 0};

void initCNY(void){
    TRIS_CNY1 = 1;
    TRIS_CNY2 = 1;
    TRIS_CNY3 = 1;
    TRIS_CNY4 = 1;
    TRIS_CNY5 = 1;
    ADCON1 = 0x0A;
    ADCON2 = 0xBE;
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    ADCON0bits.CHS = channels[actualChannel];
    ADCON0bits.ADON = 1;
    ADCON0bits.GO = 1;
}

void cnyInterrupt(void){
    if(!PIR1bits.ADIF) return;
    data[actualChannel++] = ADRESH << 8 + ADRESL;
    actualChannel %= 5;
    ADCON0bits.CHS = channels[actualChannel];
    ADCON0bits.GO = 1;
    PIR1bits.ADIF = 0;
}

unsigned int getCNY(unsigned char channel){
    if(channel >= 5) return 0;
    return data[channel];
}
#else
void cnyInterrupt(void){return;}
void initCNY(void){
    TRIS_CNY1 = 1;
    TRIS_CNY2 = 1;
    TRIS_CNY3 = 1;
    TRIS_CNY4 = 1;
    TRIS_CNY5 = 1;
    ADCON1 = 0x0A;
    ADCON2 = 0xA5;
}

unsigned int getCNY(unsigned char channel){
    if(channel >= 5) return 0;
    ADCON0bits.CHS = channels[channel];
    ADCON0bits.ADON = 1;
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO) continue;
    ADCON0bits.ADON = 0;
    return ((ADRESH << 8) + ADRESL);
}
#endif