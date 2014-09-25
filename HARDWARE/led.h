#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////
#define LED1 PBout(4)// PB5
#define LED2 PDout(6)// PD6
#define LED3 PDout(3)// PD3


void LED_Init(void);


#endif
