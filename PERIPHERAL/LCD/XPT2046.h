#ifndef __XPT2046_H
#define __XPT2046_H	    		 

#include "stm32f10x.h"
#include "delay.h"
#include "stm32f10x.h"
//#include "lcd_dis24.h"
#include "SPI.h"
#include <math.h>


#define XPT_2046_MOSI_Init  PB5_OUT
#define XPT_2046_MISO_Init  PB4_In
#define XPT_2046_SCK_Init   PB3_OUT
#define XPT_2046_PEN_Init   PC2_In
#define XPT_2046_CS_Init    PC3_OUT

#define Set_SCK             Set_B3
#define Clr_SCK             Clr_B3
#define Set_MOSI            Set_B5
#define Clr_MOSI            Clr_B5
#define XPT2046_MISO        B4
#define Set_CS              Set_C3
#define Clr_CS              Clr_C3
#define PEN                 C2 
#define Clr_PEN             Clr_C2


void XPT2046_Init(void);
u8   XPT2046_Read_Dat(u16 *x,u16 *y) ;


#endif
