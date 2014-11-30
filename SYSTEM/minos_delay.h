#ifndef __MINOS_DELAY_H
#define __MINOS_DELAY_H
#ifdef __cplusplus
       extern "C" {
#endif
#include "sys.h"
void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);
u32 SysTick_Clock(void);
//						static u32 currenttime = 0;
//						u32 lasttime = 0;
//						lasttime=currenttime;
//            currenttime=SysTick_Clock();
//						PID_ALT.dout = -PID_ALT.D * (Alt_Error_Last - Alt_Error)*(1000000/(currenttime-lasttime));
#ifdef __cplusplus
        }
#endif
#endif
