#ifndef __TIMER_CAP_H
#define __TIMER_CAP_H
#include "sys.h"
#include "G32_Timer_Cap_Config.h"
/*****************************************************
REMAP        |   00    |   01    |   10    |   11    |
*****************************************************|
TIM2_CH1_ETR |   PA0   |   PA15  |  (PA0)  |(PA15)   |
TIM2_CH2     |   PA1   |   PB3   |  (PA1)  |(PB3 )   |
TIM2_CH3     |        PA2        |    (PB10)(!36)    |
TIM2_CH4     |        PA3        |    (PB11)(!36)    |
*****************************************************|
TIM3_CH1     |   PA6   |   PB4   |         |(PC6)(64 100 144)|
TIM3_CH2     |   PA7   |   PB5   |         |(PC7)    |
TIM3_CH3     |        PB0        |         |(PC8)    |
TIM3_CH4     |        PB1        |         |(PC9)    |
*****************************************************|
TIM4_CH1     |   PB6   |(PD12)(100 144)|   |         |
TIM4_CH1     |   PB7   |(PD13)(100 144)|   |         |
TIM4_CH1     |   PB8   |(PD14)(100 144)|   |         |
TIM4_CH1     |   PB9   |(PD15)(100 144)|   |         |
*****************************************************/

extern void TIM1_Cap_Init(u16  arr, u16  psc);
extern void TIM2_Cap_Init(u16  arr, u16  psc);
extern void TIM3_Cap_Init(u16  arr, u16  psc);
extern void TIM4_Cap_Init(u16  arr, u16  psc);
extern void TIM5_Cap_Init(u16  arr, u16  psc);
extern void TIM8_Cap_Init(u16  arr, u16  psc);


#if CAP_TIM1_CH1
extern u8  TIM1_CAPTURE_STA_CH1;
extern u16  TIM1_CAPTURE_VAL_CH1;
#endif
#if CAP_TIM1_CH2
extern u8  TIM1_CAPTURE_STA_CH2;
extern u16  TIM1_CAPTURE_VAL_CH2;
#endif
#if CAP_TIM1_CH3
extern u8  TIM1_CAPTURE_STA_CH3;
extern u16  TIM1_CAPTURE_VAL_CH3;
#endif
#if CAP_TIM1_CH4
extern u8  TIM1_CAPTURE_STA_CH4;
extern u16  TIM1_CAPTURE_VAL_CH4;
#endif
#if CAP_TIM2_CH1
extern u8  TIM2_CAPTURE_STA_CH1;
extern u16  TIM2_CAPTURE_VAL_CH1;
#endif
#if CAP_TIM2_CH2
extern u8  TIM2_CAPTURE_STA_CH2;
extern u16  TIM2_CAPTURE_VAL_CH2;
#endif
#if CAP_TIM2_CH3
extern u8  TIM2_CAPTURE_STA_CH3;
extern u16  TIM2_CAPTURE_VAL_CH3;
#endif
#if CAP_TIM2_CH4
extern u8  TIM2_CAPTURE_STA_CH4;
extern u16  TIM2_CAPTURE_VAL_CH4;
#endif
#if CAP_TIM3_CH1
extern u8  TIM3_CAPTURE_STA_CH1;
extern u16  TIM3_CAPTURE_VAL_CH1;
#endif
#if CAP_TIM3_CH2
extern u8  TIM3_CAPTURE_STA_CH2;
extern u16  TIM3_CAPTURE_VAL_CH2;
#endif
#if CAP_TIM3_CH3
extern u8  TIM3_CAPTURE_STA_CH3;
extern u16  TIM3_CAPTURE_VAL_CH3;
#endif
#if CAP_TIM3_CH4
extern u8  TIM3_CAPTURE_STA_CH4;
extern u16  TIM3_CAPTURE_VAL_CH4;
#endif
#if CAP_TIM4_CH1
extern u8  TIM4_CAPTURE_STA_CH1;
extern u16  TIM4_CAPTURE_VAL_CH1;
#endif
#if CAP_TIM4_CH2
extern u8  TIM4_CAPTURE_STA_CH2;
extern u16  TIM4_CAPTURE_VAL_CH2;
#endif
#if CAP_TIM4_CH3
extern u8  TIM4_CAPTURE_STA_CH3;
extern u16  TIM4_CAPTURE_VAL_CH3;
#endif
#if CAP_TIM4_CH4
extern u8  TIM4_CAPTURE_STA_CH4;
extern u16  TIM4_CAPTURE_VAL_CH4;
#endif
#if CAP_TIM5_CH1
extern u8  TIM5_CAPTURE_STA_CH1;
extern u16  TIM5_CAPTURE_VAL_CH1;
#endif
#if CAP_TIM5_CH2
extern u8  TIM5_CAPTURE_STA_CH2;
extern u16  TIM5_CAPTURE_VAL_CH2;
#endif
#if CAP_TIM5_CH3
extern u8  TIM5_CAPTURE_STA_CH3;
extern u16  TIM5_CAPTURE_VAL_CH3;
#endif
#if CAP_TIM5_CH4
extern u8  TIM5_CAPTURE_STA_CH4;
extern u16  TIM5_CAPTURE_VAL_CH4;
#endif
#if CAP_TIM8_CH1
extern u8  TIM8_CAPTURE_STA_CH1;
extern u16  TIM8_CAPTURE_VAL_CH1;
#endif
#if CAP_TIM8_CH2
extern u8  TIM8_CAPTURE_STA_CH2;
extern u16  TIM8_CAPTURE_VAL_CH2;
#endif
#if CAP_TIM8_CH3
extern u8  TIM8_CAPTURE_STA_CH3;
extern u16  TIM8_CAPTURE_VAL_CH3;
#endif
#if CAP_TIM8_CH4
extern u8  TIM8_CAPTURE_STA_CH4;
extern u16  TIM8_CAPTURE_VAL_CH4;
#endif


#endif
