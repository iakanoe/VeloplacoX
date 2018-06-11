#include <xc.h>
#include "ui.h"

#define TRIS_LEDR TRISBbits.RB1
#define TRIS_LEDY TRISBbits.RB2
#define TRIS_LEDG TRISBbits.RB3

#define TRIS_BTN1 TRISBbits.RB0
#define TRIS_BTN2 TRISBbits.RB5

#define PORT_LEDR LATBbits.LB1
#define PORT_LEDY LATBbits.LB2
#define PORT_LEDG LATBbits.LB3

#define PORT_BTN1 PORTBbits.RB0
#define PORT_BTN2 PORTBbits.RB5

void initUI(void){
    TRIS_LEDR = 0;
    PORT_LEDR = 0;
    
    TRIS_LEDY = 0;
    PORT_LEDY = 0;
    
    TRIS_LEDG = 0;
    PORT_LEDG = 0;
    
    TRIS_BTN1 = 1;
    TRIS_BTN2 = 1;
}

void setLEDs(char r, char y, char g){
    setLEDR(r);
    setLEDY(y);
    setLEDG(g);
}

unsigned char getBTN1(void){
    return !PORT_BTN1;
}

unsigned char getBTN2(void){
    return !PORT_BTN2;
}

unsigned char getBTNs(void){
    return getBTN1() || getBTN2();
}

void setLEDR(char v){
    PORT_LEDR = v;
}

void setLEDY(char v){
    PORT_LEDY = v;
}

void setLEDG(char v){
    PORT_LEDG = v;
}

char getLEDR(void){
    return PORT_LEDR;
}

char getLEDY(void){
    return PORT_LEDY;
}

char getLEDG(void){
    return PORT_LEDG;
}
