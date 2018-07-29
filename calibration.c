#include "CNY.h"
#include "calibration.h"
#include <xc.h>


#define map(x, a, b, c, d) (c + ((d - c) / (b - a)) * (x - a))
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
unsigned int mins[5], maxs[5];

void initCal(void){
    for(int i = 0; i < 5; i++){
        mins[i] = 1023;
        maxs[i] = 0;
    }
}

void calibrateCNY(unsigned int channel){
    unsigned int val = getCNY(channel);
    mins[channel] = min(val, mins[channel]);
    maxs[channel] = max(val, maxs[channel]);
}

unsigned int getCalCNY(unsigned int channel){
    unsigned int val = getCNY(channel);
    mins[channel] = min(val, mins[channel]);
    maxs[channel] = max(val, maxs[channel]);
    val = map(val, mins[channel], maxs[channel], 0, 1000);
    return val;
}
