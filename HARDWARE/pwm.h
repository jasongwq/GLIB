#ifndef __PWM_H_
#define __PWM_H_
#include "sys.h"
/*****************************************************
REMAP        |   00    |   01    |   10    |   11    |
*****************************************************|
TIM2_CH1_ETR |   PA0   |PA15(JTDI)| (PA0)  |(PA15)   |
TIM2_CH2     |   PA1   |PB3(JTDO) | (PA1)  |(PB3 )   |
TIM2_CH3     |        PA2        |    (PB10)(!36)    |
TIM2_CH4     |        PA3        |    (PB11)(!36)    |
*****************************************************|
TIM3_CH1     |   PA6   |PB4(JNTRST)|       |(PC6)(64 100 144)|
TIM3_CH2     |   PA7   |   PB5   |         |(PC7)    |
TIM3_CH3     |        PB0        |         |(PC8)    |
TIM3_CH4     |        PB1        |         |(PC9)    |
*****************************************************|
TIM4_CH1     |   PB6   |(PD12)(100 144)|   |         |
TIM4_CH2     |   PB7   |(PD13)(100 144)|   |         |
TIM4_CH3     |   PB8   |(PD14)(100 144)|   |         |
TIM4_CH4     |   PB9   |(PD15)(100 144)|   |         |
*****************************************************|
TIM5_CH1     |   PA0   |                             |
TIM5_CH2     |   PA1   |                             |
TIM5_CH3     |   PA2   |                             |
TIM5_CH4     |   PA3   |                             |
*****************************************************|
TIM8_ETR     |   PA0   |                             |
TIM8_CH1     |   PC6   |                             |
TIM8_CH2     |   PC7   |                             |
TIM8_CH3     |   PC8   |                             |
TIM8_CH4     |   PC9   |                             |
TIM8_BKIN    |   PA6   |                             |
TIM8_CH1N    |   PA7   |                             |
TIM8_CH2N    |   PB0   |                             |
TIM8_CH3N    |   PB1   |                             |
*****************************************************|
TIM1_ETR     |        PA12       |   PE7 (100 144)   |
TIM1_CH1     |        PA8        |   PE9 (100 144)   |
TIM1_CH2     |        PA9 (Tx)   |   PE11(100 144)   |
TIM1_CH3     |        PA10(Rx)   |   PE13(100 144)   |
TIM1_CH4     |        PA11(CANRx)|   PE14(100 144)   |
TIM1_BKIN    |PB12(!36)|   PA6   |   PE15(100 144)   |
TIM1_CH1N    |PB13(!36)|   PA7   |   PE8 (100 144)   |
TIM1_CH2N    |PB14(!36)|   PB0   |   PE10(100 144)   |
TIM1_CH3N    |PB15(!36)|   PB1   |   PE12(100 144)   |
*****************************************************/

void TIM2_PWM_Init(u16 arr, u16 psc);
void TIM3_PWM_Init(u16 arr, u16 psc);
void TIM4_PWM_Init(u16 arr, u16 psc);
void TIM5_PWM_Init(u16 arr, u16 psc);
void TIM1_PWM_Init(u16 arr, u16 psc);
void TIM8_PWM_Init(u16 arr, u16 psc);
#define TIM_SetCompare(TIMx,Comparex,Compare) TIMx->CCR##Comparex=(Compare);
#define TIM_GetCompare(TIMx,Comparex) TIMx->CCR##Comparex

/*
999 计数
0   分频
TIM2_PWM_Init(999,0);//899 不分频 不分频,PWM频率=72000/900=80Khz
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2);

        TIM2_PWM_Init(900,1);//80kHz
        TIM_SetCompare1(TIM2,100);
        TIM_SetCompare2(TIM2,200);
        TIM_SetCompare3(TIM2,300);
        TIM_SetCompare4(TIM2,400);

        TIM3_PWM_Init(900,10);//80kHz
        TIM_SetCompare1(TIM3,100);
        TIM_SetCompare2(TIM3,200);
        TIM_SetCompare3(TIM3,300);
        TIM_SetCompare4(TIM3,400);

        TIM4_PWM_Init(900,100);//80kHz
        TIM_SetCompare1(TIM4,100);
        TIM_SetCompare2(TIM4,200);
        TIM_SetCompare3(TIM4,300);
        TIM_SetCompare4(TIM4,400);

        TIM5_PWM_Init(900,1000);//80kHz
        TIM_SetCompare1(TIM5,100);
        TIM_SetCompare2(TIM5,200);
        TIM_SetCompare3(TIM5,300);
        TIM_SetCompare4(TIM5,400);

        TIM8_PWM_Init(900,36);//80kHz
        TIM_SetCompare1(TIM8,100);
        TIM_SetCompare2(TIM8,200);
        TIM_SetCompare3(TIM8,300);
        TIM_SetCompare4(TIM8,400);

        TIM1_PWM_Init(900,36);//80kHz
        TIM_SetCompare1(TIM1,100);
        TIM_SetCompare2(TIM1,200);
        TIM_SetCompare3(TIM1,300);
        TIM_SetCompare4(TIM1,400);
*/
#endif
