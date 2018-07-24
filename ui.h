#ifndef UI_H
#define	UI_H

void initUI(void);
void setLEDs(char r, char y, char g);
bit getBTN1(void);
bit getBTN2(void);
bit getBTNs(void);
void setLEDR(char v);
void setLEDY(char v);
void setLEDG(char v);
bit getLEDR(void);
bit getLEDY(void);
bit getLEDG(void);

#endif
