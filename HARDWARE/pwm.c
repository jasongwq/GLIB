#include "pwm.h"
#include "Pwm_Config.h"
/**
 * stm32f103vct6 100pin
 * data
 */

/*
��
TIM2_PWM_Init(u16 arr, u16 psc)//arr���Զ���װ psc��ʱ��Ԥ��Ƶ��
TIM2_PWM_Init(900,1);//900 ����Ƶ,PWMƵ��=72000/900=80Khz
TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1)��
TIM_SetCompare1(TIM2,100);
TIM_SetCompare2(TIM2,200);
TIM_SetCompare3(TIM2,300);
TIM_SetCompare4(TIM2,400);
*/
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
#if (PWM_TIM2_CH1)||(PWM_TIM2_CH2)||(PWM_TIM2_CH3)||(PWM_TIM2_CH4)
/**
 * PWM�����ʼ��
 * @param arr [�Զ���װ��ֵ]
 * @param psc [ʼ��Ԥ��Ƶֵ]
 */
void TIM2_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ�ܶ�ʱ��Xʱ��
#if   (PWM_TIM2_AFIO==0)
#elif (PWM_TIM2_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
#elif (PWM_TIM2_AFIO==2)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);
#elif (PWM_TIM2_AFIO==3)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
#endif
#if PWM_TIM2_CH1
#if   ((PWM_TIM2_AFIO==0)||(PWM_TIM2_AFIO==2))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);               //��ʼ��GPIO
#elif ((PWM_TIM2_AFIO==1)||(PWM_TIM2_AFIO==3))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);               //��ʼ��GPIO
#endif
#endif
#if PWM_TIM2_CH2
#if ((PWM_TIM2_AFIO==0)||(PWM_TIM2_AFIO==2))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;     //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);               //��ʼ��GPIO
#elif ((PWM_TIM2_AFIO==1)||(PWM_TIM2_AFIO==3))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;     //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);               //��ʼ��GPIO
#endif
#endif
#if PWM_TIM2_CH3
#if ((PWM_TIM2_AFIO==0)||(PWM_TIM2_AFIO==1))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);               //��ʼ��GPIO
#elif ((PWM_TIM2_AFIO==2)||(PWM_TIM2_AFIO==3))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);               //��ʼ��GPIO
#endif
#endif
#if PWM_TIM2_CH4
#if ((PWM_TIM2_AFIO==0)||(PWM_TIM2_AFIO==1))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);               //��ʼ��GPIO
#elif ((PWM_TIM2_AFIO==2)||(PWM_TIM2_AFIO==3))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;      //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);               //��ʼ��GPIO
#endif
#endif
    //��ʼ��TIM2
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM����ģʽ
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM2 PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;             //ѡ��ʱ��ģʽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;     //�������
#if PWM_TIM2_CH1
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);         //����Tָ���Ĳ�����ʼ������TIM2
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);//ʹ��TIM2��Ԥװ�ؼĴ���
#endif
#if PWM_TIM2_CH2
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);         //����Tָ���Ĳ�����ʼ������TIM2
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);//ʹ��TIM2��Ԥװ�ؼĴ���
#endif
#if PWM_TIM2_CH3
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);         //����Tָ���Ĳ�����ʼ������TIM2
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);//ʹ��TIM2��Ԥװ�ؼĴ���
#endif
#if PWM_TIM2_CH4
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);         //����Tָ���Ĳ�����ʼ������TIM2
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);//ʹ��TIM2��Ԥװ�ؼĴ���
#endif
    TIM_Cmd(TIM2, ENABLE);//ʹ��TIM2
}
#endif

//TIM3 PWM���ֳ�ʼ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
#if (PWM_TIM3_CH1)||(PWM_TIM3_CH2)|(PWM_TIM3_CH3)||(PWM_TIM3_CH4)
void TIM3_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
#if   (PWM_TIM3_AFIO==0)
#elif (PWM_TIM3_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
#elif (PWM_TIM3_AFIO==2)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
#endif
#if PWM_TIM3_CH1
#if     (PWM_TIM3_AFIO==0)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#elif (PWM_TIM3_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#elif (PWM_TIM3_AFIO==2)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
#endif
#if PWM_TIM3_CH2
#if     (PWM_TIM3_AFIO==0)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#elif (PWM_TIM3_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#elif (PWM_TIM3_AFIO==2)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
#endif
#if PWM_TIM3_CH3
#if ((PWM_TIM3_AFIO==0)||(PWM_TIM3_AFIO==1))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#elif (PWM_TIM3_AFIO==2)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
#endif
#if PWM_TIM3_CH4
#if ((PWM_TIM3_AFIO==0)||(PWM_TIM3_AFIO==1))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#elif (PWM_TIM3_AFIO==2)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
#endif

    //��ʼ��TIM3
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM3  PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//ѡ��ʱ��ģʽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//�������:TIM����Ƚϼ���

#if PWM_TIM3_CH1
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��Ԥװ�ؼĴ���
#endif
#if PWM_TIM3_CH2
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��Ԥװ�ؼĴ���
#endif
#if PWM_TIM3_CH3
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��Ԥװ�ؼĴ���
#endif
#if PWM_TIM3_CH4
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��Ԥװ�ؼĴ���
#endif
    TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
}
#endif
//TIM4 PWM���ֳ�ʼ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
#if (PWM_TIM4_CH1)||(PWM_TIM4_CH2)||(PWM_TIM4_CH3)||(PWM_TIM4_CH4)
void TIM4_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
#if   (PWM_TIM4_AFIO==0)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
#elif (PWM_TIM4_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
#endif
#if PWM_TIM4_CH1
#if   (PWM_TIM4_AFIO==0)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#elif (PWM_TIM4_AFIO==1)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif
#endif
#if PWM_TIM4_CH2
#if   (PWM_TIM4_AFIO==0)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#elif (PWM_TIM4_AFIO==1)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif
#endif
#if PWM_TIM4_CH3
#if   (PWM_TIM4_AFIO==0)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#elif (PWM_TIM4_AFIO==1)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif
#endif
#if PWM_TIM4_CH4
#if   (PWM_TIM4_AFIO==0)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#elif (PWM_TIM4_AFIO==1)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif
#endif
    //��ʼ��TIM4
    TIM_TimeBaseStructure.TIM_Period = arr - 1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM4  PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������
#if PWM_TIM4_CH1
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��Ԥװ�ؼĴ���
#endif
#if PWM_TIM4_CH2
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��Ԥװ�ؼĴ���
#endif
#if PWM_TIM4_CH3
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��Ԥװ�ؼĴ���
#endif
#if PWM_TIM4_CH4
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��Ԥװ�ؼĴ���
#endif
    TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4
}
#endif


//TIM5 PWM���ֳ�ʼ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
#if (PWM_TIM5_CH1)||(PWM_TIM5_CH2)||(PWM_TIM5_CH3)||(PWM_TIM5_CH4)
void TIM5_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);    //ʹ�ܶ�ʱ��3ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
#if PWM_TIM5_CH1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
#if PWM_TIM5_CH2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
#if PWM_TIM5_CH3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
#if PWM_TIM5_CH4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
    //��ʼ��TIM5
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM5  PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������
#if PWM_TIM5_CH1
    TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM5
    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM5��Ԥװ�ؼĴ���
#endif
#if PWM_TIM5_CH2
    TIM_OC2Init(TIM5, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM5
    TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM5��Ԥװ�ؼĴ���
#endif
#if PWM_TIM5_CH3
    TIM_OC3Init(TIM5, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM5
    TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM5��Ԥװ�ؼĴ���
#endif
#if PWM_TIM5_CH4
    TIM_OC4Init(TIM5, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM5
    TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM5��Ԥװ�ؼĴ���
#endif
    TIM_Cmd(TIM5, ENABLE);  //ʹ��TIM5
}
#endif

//TIM8 PWM���ֳ�ʼ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
#if (PWM_TIM8_CH1)||(PWM_TIM8_CH2)||(PWM_TIM8_CH3)||(PWM_TIM8_CH4)
void TIM8_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    static TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    static TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);   //ʹ�ܶ�ʱ��3ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    //TIM_DeInit(TIM8);
    TIM_DeInit(TIM8);
#if PWM_TIM8_CH1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
#if PWM_TIM8_CH2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
#if PWM_TIM8_CH3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
#if PWM_TIM8_CH4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
    //��ʼ��TIM8
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;//����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;          //ѭ����������ֵ
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM8  PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//ʹ�ܶ�ʱ���������
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;       //�������
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;     //�򿪿���״̬ѡ��ر�
#if PWM_TIM8_CH1
    TIM_OC1Init(TIM8, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
#endif
#if PWM_TIM8_CH2
    TIM_OC2Init(TIM8, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
#endif
#if PWM_TIM8_CH3
    TIM_OC3Init(TIM8, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
#endif
#if PWM_TIM8_CH4
    TIM_OC4Init(TIM8, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);
#endif
    TIM_Cmd(TIM8, ENABLE);  //ʹ��TIM8
    TIM_CtrlPWMOutputs(TIM8, ENABLE); //ʹ�ܶ�ʱ��8��PWM���
}
#endif

//TIM1 PWM���ֳ�ʼ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
#if (PWM_TIM1_CH1)||(PWM_TIM1_CH2)||(PWM_TIM1_CH3)||(PWM_TIM1_CH4)
void TIM1_PWM_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    static TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    static TIM_OCInitTypeDef  TIM_OCInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);    //ʹ�ܶ�ʱ��3ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    TIM_DeInit(TIM1);
#if   (PWM_TIM1_AFIO==0)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
#elif (PWM_TIM1_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
#elif (PWM_TIM1_AFIO==2)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
#endif
#if PWM_TIM1_CH1
#if   ((PWM_TIM1_AFIO==0)||(PWM_TIM1_AFIO==1))
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#elif (PWM_TIM1_AFIO==2)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
#endif
#endif
#if PWM_TIM1_CH2
#if   ((PWM_TIM1_AFIO==0)||(PWM_TIM1_AFIO==1))
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#elif (PWM_TIM1_AFIO==2)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
#endif
#endif
#if PWM_TIM1_CH3
#if   ((PWM_TIM1_AFIO==0)||(PWM_TIM1_AFIO==1))
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#elif (PWM_TIM1_AFIO==2)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
#endif
#endif
#if PWM_TIM1_CH4
#if   ((PWM_TIM1_AFIO==0)||(PWM_TIM1_AFIO==1))
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#elif (PWM_TIM1_AFIO==2)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
#endif
#endif
    //��ʼ��TIM1
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;          //ѭ����������ֵ
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //��ʼ��TIM1  PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//ʹ�ܶ�ʱ���������
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;       //�������
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;     //�򿪿���״̬ѡ��ر�
#if PWM_TIM1_CH1
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��Ԥװ�ؼĴ���
#endif
#if PWM_TIM1_CH2
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��Ԥװ�ؼĴ���
#endif
#if PWM_TIM1_CH3
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��Ԥװ�ؼĴ���
#endif
#if PWM_TIM1_CH4
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��Ԥװ�ؼĴ���
#endif
    TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
    TIM_CtrlPWMOutputs(TIM1, ENABLE); //ʹ�ܶ�ʱ��1��PWM���
}
#endif

void TIM1_SPWM_GPIO_Init(void)
{
    static GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}


//u16 SIN_SPWM[]={
//450,453,456,458,461,464,467,470,473,475,478,481,484,487,490,492,495,498,501,504,506,509,512,515,518,520,523,526,529,532,534,537,540,543,545,548,551,554,556,559,562,565,567,570,573,576,578,581,584,586,589,592,594,597,600,602,605,608,610,613,616,618,621,624,626,629,631,634,636,639,642,644,647,649,652,654,657,659,662,664,667,669,672,674,677,679,681,684,686,689,691,694,696,698,701,703,705,708,710,712,715,717,719,721,724,726,728,730,732,735,737,739,741,743,745,748,750,752,754,756,758,760,762,764,766,768,770,772,774,776,778,780,782,784,786,788,789,791,793,795,797,799,800,802,804,806,807,809,811,812,814,816,817,819,821,822,824,825,827,828,830,831,833,834,836,837,839,840,842,843,844,846,847,848,850,851,852,853,855,856,857,858,860,861,862,863,864,865,866,867,868,869,870,871,872,873,874,875,876,877,878,879,880,881,881,882,883,884,884,885,886,887,887,888,889,889,890,890,891,891,892,893,893,894,894,894,895,895,896,896,896,897,897,897,898,898,898,898,899,899,899,899,899,900,900,900,900,900,900,900,900,900,900,900,900,900,900,900,899,899,899,899,899,898,898,898,898,897,897,897,896,896,896,895,895,894,894,894,893,893,892,891,891,890,890,889,889,888,887,887,886,885,884,884,883,882,881,881,880,879,878,877,876,875,874,873,872,871,870,869,868,867,866,865,864,863,862,861,860,858,857,856,855,853,852,851,850,848,847,846,844,843,842,840,839,837,836,834,833,831,830,828,827,825,824,822,821,819,817,816,814,812,811,809,807,806,804,802,800,799,797,795,793,791,789,788,786,784,782,780,778,776,774,772,770,768,766,764,762,760,758,756,754,752,750,748,745,743,741,739,737,735,732,730,728,726,724,721,719,717,715,712,710,708,705,703,701,698,696,694,691,689,686,684,681,679,677,674,672,669,667,664,662,659,657,654,652,649,647,644,642,639,636,634,631,629,626,624,621,618,616,613,610,608,605,602,600,597,594,592,589,586,584,581,578,576,573,570,567,565,562,559,556,554,551,548,545,543,540,537,534,532,529,526,523,520,518,515,512,509,506,504,501,498,495,492,490,487,484,481,478,475,473,470,467,464,461,458,456,453,450,
//};
//void TIM1_SPWM_UP_IRQ(void)
//{
//  static u32 i=1,time=0;
//  i+=10;
//  if(time)
//  {
//      TIM_SetCompare3(TIM1,900-SIN_SPWM[i]);
//      TIM_SetCompare2(TIM1,900-SIN_SPWM[i]);
//  }
//  else{
//          TIM_SetCompare3(TIM1,SIN_SPWM[i]);
//          TIM_SetCompare2(TIM1,SIN_SPWM[i]);
//  }
//if(i>=sizeof(SIN_SPWM)/2){i=1;
//time++;if(time>=2)time=0;
//}
//  TIM1->SR &= 0xfffe;
//}
//���໥��PWM
void TIM1_SPWM_Init(u16 arr, u16 psc)
{
    static TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    static TIM_OCInitTypeDef  TIM_OCInitStructure;
    static TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
    //static NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);    //ʹ�ܶ�ʱ��3ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    TIM_DeInit(TIM1);
    TIM1_SPWM_GPIO_Init();
    //��ʼ��TIM1
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x00;//ѭ����������ֵ
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
    TIM_ARRPreloadConfig(TIM1, ENABLE);

    //��ʼ��TIM1  PWMģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ
    TIM_OCInitStructure.TIM_OutputState =  TIM_OutputState_Enable;  //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//ʹ�ܶ�ʱ���������
    TIM_OCInitStructure.TIM_Pulse = 120; //��׽�ȽϼĴ���
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //�������
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Reset;     //�򿪿���״̬ѡ��ر�
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;     //�򿪿���״̬ѡ��ر�

    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    //TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM4��Ԥװ�ؼĴ���
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    //TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM4��Ԥװ�ؼĴ���
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);
    //TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM4��Ԥװ�ؼĴ���

    TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
    TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
    TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStructure.TIM_DeadTime = 0x90;
    TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
    TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
    TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
    TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
    //      TIM1->SR = 0;
    //      //����TIM1�����¼��ж�
    //    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE ); //ʹ��ָ����TIM2�ж�,��������ж�

    //    //�ж����ȼ�NVIC����
    //    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM2�ж�
    //    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
    //    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
    //    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
    //    NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
    //      TIM1_UP_IRQ=TIM1_SPWM_UP_IRQ;
    TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
    TIM_CtrlPWMOutputs(TIM1, ENABLE); //ʹ�ܶ�ʱ��1��PWM���
}


