#include "G32_timer_cap.h"
#include "stm32f10x_it.h"
//#include "usart.h"
/**
 * stm32f103vct6 100pin
 * data
 */
// #include "G32_timer_cap.h"
/*
��
//    ***����***
//    TIM5_Cap_Init(0XFFFF, 72 - 1);
//    while (1)
//    {
//        delay_ms(10);
//        if (TIM5CH1_CAPTURE_STA & 0X80) //�ɹ�������һ��������
//        {
//            temp = TIM5CH1_CAPTURE_STA & 0X3F;
//            temp *= 65536; //���ʱ���ܺ�
//            temp += TIM5CH1_CAPTURE_VAL; //�õ��ܵĸߵ�ƽʱ��
//            USART_OUT(USART1, "HIGH��:%d us\r\n", temp); //��ӡ�ܵĸߵ�ƽʱ��
//            TIM5CH1_CAPTURE_STA = 0; //������һ�β���
//        }
//    }
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
#define USER_CAP_FILTER 0x08


#if CAP_TIM1_CH1
u8  TIM1_CAPTURE_STA_CH1 = 0;
u16 TIM1_CAPTURE_VAL_CH1 = 0;
#endif
#if CAP_TIM1_CH2
u8  TIM1_CAPTURE_STA_CH2 = 0;
u16 TIM1_CAPTURE_VAL_CH2 = 0;
#endif
#if CAP_TIM1_CH3
u8  TIM1_CAPTURE_STA_CH3 = 0;
u16 TIM1_CAPTURE_VAL_CH3 = 0;
#endif
#if CAP_TIM1_CH4
u8  TIM1_CAPTURE_STA_CH4 = 0;
u16 TIM1_CAPTURE_VAL_CH4 = 0;
#endif
#if CAP_TIM2_CH1
u8  TIM2_CAPTURE_STA_CH1 = 0;
u16 TIM2_CAPTURE_VAL_CH1 = 0;
#endif
#if CAP_TIM2_CH2
u8  TIM2_CAPTURE_STA_CH2 = 0;
u16 TIM2_CAPTURE_VAL_CH2 = 0;
#endif
#if CAP_TIM2_CH3
u8  TIM2_CAPTURE_STA_CH3 = 0;
u16 TIM2_CAPTURE_VAL_CH3 = 0;
#endif
#if CAP_TIM2_CH4
u8  TIM2_CAPTURE_STA_CH4 = 0;
u16 TIM2_CAPTURE_VAL_CH4 = 0;
#endif
#if CAP_TIM3_CH1
u8  TIM3_CAPTURE_STA_CH1 = 0;
u16 TIM3_CAPTURE_VAL_CH1 = 0;
#endif
#if CAP_TIM3_CH2
u8  TIM3_CAPTURE_STA_CH2 = 0;
u16 TIM3_CAPTURE_VAL_CH2 = 0;
#endif
#if CAP_TIM3_CH3
u8  TIM3_CAPTURE_STA_CH3 = 0;
u16 TIM3_CAPTURE_VAL_CH3 = 0;
#endif
#if CAP_TIM3_CH4
u8  TIM3_CAPTURE_STA_CH4 = 0;
u16 TIM3_CAPTURE_VAL_CH4 = 0;
#endif
#if CAP_TIM4_CH1
u8  TIM4_CAPTURE_STA_CH1 = 0;
u16 TIM4_CAPTURE_VAL_CH1 = 0;
#endif
#if CAP_TIM4_CH2
u8  TIM4_CAPTURE_STA_CH2 = 0;
u16 TIM4_CAPTURE_VAL_CH2 = 0;
#endif
#if CAP_TIM4_CH3
u8  TIM4_CAPTURE_STA_CH3 = 0;
u16 TIM4_CAPTURE_VAL_CH3 = 0;
#endif
#if CAP_TIM4_CH4
u8  TIM4_CAPTURE_STA_CH4 = 0;
u16 TIM4_CAPTURE_VAL_CH4 = 0;
#endif
#if CAP_TIM5_CH1
u8  TIM5_CAPTURE_STA_CH1 = 0;
u16 TIM5_CAPTURE_VAL_CH1 = 0;
#endif
#if CAP_TIM5_CH2
u8  TIM5_CAPTURE_STA_CH2 = 0;
u16 TIM5_CAPTURE_VAL_CH2 = 0;
#endif
#if CAP_TIM5_CH3
u8  TIM5_CAPTURE_STA_CH3 = 0;
u16 TIM5_CAPTURE_VAL_CH3 = 0;
#endif
#if CAP_TIM5_CH4
u8  TIM5_CAPTURE_STA_CH4 = 0;
u16 TIM5_CAPTURE_VAL_CH4 = 0;
#endif
#if CAP_TIM8_CH1
u8  TIM8_CAPTURE_STA_CH1 = 0;
u16 TIM8_CAPTURE_VAL_CH1 = 0;
#endif
#if CAP_TIM8_CH2
u8  TIM8_CAPTURE_STA_CH2 = 0;
u16 TIM8_CAPTURE_VAL_CH2 = 0;
#endif
#if CAP_TIM8_CH3
u8  TIM8_CAPTURE_STA_CH3 = 0;
u16 TIM8_CAPTURE_VAL_CH3 = 0;
#endif
#if CAP_TIM8_CH4
u8  TIM8_CAPTURE_STA_CH4 = 0;
u16 TIM8_CAPTURE_VAL_CH4 = 0;
#endif
#define TIM_CAPTURE_STA_CH(x,y) TIM##x##_CAPTURE_STA_CH##y
#define TIM_CAPTURE_VAL_CH(x,y) TIM##x##_CAPTURE_VAL_CH##y
#define DEFTIM_CAP_CH(timx,ch) \
    if ((TIM_CAPTURE_STA_CH(timx,ch) & 0X80) == 0)\
    {\
        if (TIM_GetITStatus(TIMx, TIM_IT_CC##ch) != RESET)\
        {\
            if(TIM_CAPTURE_STA_CH(timx,ch) & 0X40)\
            {\
                TIM_CAPTURE_STA_CH(timx,ch) |= 0X80;\
                TIM_CAPTURE_VAL_CH(timx,ch) = TIM_GetCapture##ch(TIMx);\
                TIM_OC##ch##PolarityConfig(TIMx, TIM_ICPolarity_Rising);\
            }else{\
                TIM_CAPTURE_STA_CH(timx,ch) = 0;\
                TIM_CAPTURE_VAL_CH(timx,ch) = 0;\
                TIM_SetCounter(TIMx, 0);\
                TIM_CAPTURE_STA_CH(timx,ch) |= 0X40;\
                TIM_OC##ch##PolarityConfig(TIMx, TIM_ICPolarity_Falling);\
            }\
        }\
    }

#if (CAP_TIM2_CH1)||(CAP_TIM2_CH2)||(CAP_TIM2_CH3)||(CAP_TIM2_CH4)
/**
 * CAP�����ʼ��
 * @param arr [�Զ���װ��ֵ]
 * @param psc [ʼ��Ԥ��Ƶֵ]
 */
void TIM2_Cap_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ�ܶ�ʱ��Xʱ��
#if   (CAP_TIM2_AFIO==0)
#elif (CAP_TIM2_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
#elif (CAP_TIM2_AFIO==2)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);
#elif (CAP_TIM2_AFIO==3)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
#endif
#if CAP_TIM2_CH1
#if   ((CAP_TIM2_AFIO==0)||(CAP_TIM2_AFIO==2))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);             //��ʼ��GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);                 //PA0 ����

#elif ((CAP_TIM2_AFIO==1)||(CAP_TIM2_AFIO==3))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);             //��ʼ��GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_15);                //PA0 ����
#endif
#endif
#if CAP_TIM2_CH2
#if ((CAP_TIM2_AFIO==0)||(CAP_TIM2_AFIO==2))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;     //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);               //��ʼ��GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);                //PA0 ����

#elif ((CAP_TIM2_AFIO==1)||(CAP_TIM2_AFIO==3))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;     //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_3);                //����

#endif
#endif
#if CAP_TIM2_CH3
#if ((CAP_TIM2_AFIO==0)||(CAP_TIM2_AFIO==1))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);                //����               //��ʼ��GPIO
#elif ((CAP_TIM2_AFIO==2)||(CAP_TIM2_AFIO==3))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_10);                //����
#endif
#endif
#if CAP_TIM2_CH4
#if ((CAP_TIM2_AFIO==0)||(CAP_TIM2_AFIO==1))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_3);                //����               //��ʼ��GPIO
#elif ((CAP_TIM2_AFIO==2)||(CAP_TIM2_AFIO==3))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_11);                //����
#endif
#endif
    //��ʼ��TIM2
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM����ģʽ
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //�жϷ����ʼ��
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                     //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //�����ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);     //��������ж� ,����CC1IE�����ж�

    //��ʼ��TIM���벶�����
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //�����ز���
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //���������Ƶ,����Ƶ
    TIM_ICInitStructure.TIM_ICFilter = USER_CAP_FILTER;//IC1F=0000 ���������˲��� ���˲�

#if CAP_TIM2_CH1
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM2_CH2
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM2_CH3
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM2_CH4
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ITConfig(TIM2, TIM_IT_CC4, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
    TIM_Cmd(TIM2, ENABLE);//ʹ��TIM2
}

void TIM2_Cap_IRQ(void)
{
#define TIMx TIM2
#if CAP_TIM2_CH1
    DEFTIM_CAP_CH(2, 1)
#endif
#if CAP_TIM2_CH2
    DEFTIM_CAP_CH(2, 2)
#endif
#if CAP_TIM2_CH3
DEFTIM_CAP_CH(2, 3)
#endif
#if CAP_TIM2_CH4
    DEFTIM_CAP_CH(2, 4)
#endif
    TIM_ClearITPendingBit(TIMx, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update); //����жϱ�־λ
#undef TIMx
}
#endif

//TIM3 CAP���ֳ�ʼ��
//CAP�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
#if (CAP_TIM3_CH1)||(CAP_TIM3_CH2)|(CAP_TIM3_CH3)||(CAP_TIM3_CH4)
void TIM3_Cap_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
#if   (CAP_TIM3_AFIO==0)
#elif (CAP_TIM3_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
#elif (CAP_TIM3_AFIO==3)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
#endif
#if CAP_TIM3_CH1
#if     (CAP_TIM3_AFIO==0)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_6);                //����
#elif (CAP_TIM3_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_6);                //����
#elif (CAP_TIM3_AFIO==3)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_6);                //����
#endif
#endif
#if CAP_TIM3_CH2
#if     (CAP_TIM3_AFIO==0)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_7);                //����
#elif (CAP_TIM3_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);                //����
#elif (CAP_TIM3_AFIO==3)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_7);                //����
#endif
#endif
#if CAP_TIM3_CH3
#if ((CAP_TIM3_AFIO==0)||(CAP_TIM3_AFIO==1))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);                //����
#elif (CAP_TIM3_AFIO==3)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_8);                //����
#endif
#endif
#if CAP_TIM3_CH4
#if ((CAP_TIM3_AFIO==0)||(CAP_TIM3_AFIO==1))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_1);                //����
#elif (CAP_TIM3_AFIO==3)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_9);                //����
#endif
#endif

    //��ʼ��TIM3
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM����ģʽ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //�жϷ����ʼ��
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                     //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //�����ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);     //��������ж� ,����CC1IE�����ж�

    //��ʼ��TIM���벶�����
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //�����ز���
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //���������Ƶ,����Ƶ
    TIM_ICInitStructure.TIM_ICFilter = USER_CAP_FILTER;//IC1F=0000 ���������˲��� ���˲�

#if CAP_TIM3_CH1
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM3_CH2
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM3_CH3
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    TIM_ITConfig(TIM3, TIM_IT_CC3, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM3_CH4
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    TIM_ITConfig(TIM3, TIM_IT_CC4, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
    TIM_Cmd(TIM3, ENABLE);//ʹ��TIM3
}
void TIM3_Cap_IRQ(void)
{
#define TIMx TIM3
#if CAP_TIM3_CH1
    DEFTIM_CAP_CH(3, 1)
#endif
#if CAP_TIM3_CH2
    DEFTIM_CAP_CH(3, 2)
#endif
#if CAP_TIM3_CH3
    DEFTIM_CAP_CH(3, 3)
#endif
#if CAP_TIM3_CH4
    DEFTIM_CAP_CH(3, 4)
#endif
    TIM_ClearITPendingBit(TIMx, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update); //����жϱ�־λ
#undef TIMx
}
#endif
//TIM4 CAP���ֳ�ʼ��
//CAP�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
#if (CAP_TIM4_CH1)||(CAP_TIM4_CH2)||(CAP_TIM4_CH3)||(CAP_TIM4_CH4)
void TIM4_Cap_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
#if   (CAP_TIM4_AFIO==0)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
#elif (CAP_TIM4_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
#endif
#if CAP_TIM4_CH1
#if   (CAP_TIM4_AFIO==0)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_6);                //����
#elif (CAP_TIM4_AFIO==1)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOD, GPIO_Pin_12);                //����
#endif
#endif
#if CAP_TIM4_CH2
#if   (CAP_TIM4_AFIO==0)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_7);                //����
#elif (CAP_TIM4_AFIO==1)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOD, GPIO_Pin_13);                //����
#endif
#endif
#if CAP_TIM4_CH3
#if   (CAP_TIM4_AFIO==0)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_8);                //����
#elif (CAP_TIM4_AFIO==1)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOD, GPIO_Pin_14);                //����
#endif
#endif
#if CAP_TIM4_CH4
#if   (CAP_TIM4_AFIO==0)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_9);                //����
#elif (CAP_TIM4_AFIO==1)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOD, GPIO_Pin_15);                //����
#endif
#endif
    //��ʼ��TIM4
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM����ģʽ
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //�жϷ����ʼ��
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                     //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //�����ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);     //��������ж� ,����CC1IE�����ж�

    //��ʼ��TIM���벶�����
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //�����ز���
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //���������Ƶ,����Ƶ
    TIM_ICInitStructure.TIM_ICFilter = USER_CAP_FILTER;//IC1F=0000 ���������˲��� ���˲�

#if CAP_TIM4_CH1
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
    TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM4_CH2
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
    TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM4_CH3
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
    TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM4_CH4
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
    TIM_ITConfig(TIM4, TIM_IT_CC4, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
    TIM_Cmd(TIM4, ENABLE);//ʹ��TIM4
}
void TIM4_Cap_IRQ(void)
{
#define TIMx TIM4
#if CAP_TIM4_CH1
    DEFTIM_CAP_CH(4, 1)
		#endif
#if CAP_TIM4_CH2
    DEFTIM_CAP_CH(4, 2)
		#endif
#if CAP_TIM4_CH3
    DEFTIM_CAP_CH(4, 3)
		#endif
#if CAP_TIM4_CH4
    DEFTIM_CAP_CH(4, 4)
#endif
    TIM_ClearITPendingBit(TIMx, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update); //����жϱ�־λ
#undef TIMx
}
#endif


//TIM5 CAP���ֳ�ʼ��
//CAP�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
#if (CAP_TIM5_CH1)||(CAP_TIM5_CH2)||(CAP_TIM5_CH3)||(CAP_TIM5_CH4)
void TIM5_Cap_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);    //ʹ�ܶ�ʱ��3ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
#if CAP_TIM5_CH1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);                //����
#endif
#if CAP_TIM5_CH2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);                //����
#endif
#if CAP_TIM5_CH3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);                //����
#endif
#if CAP_TIM5_CH4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_3);                //����
#endif
    //��ʼ��TIM5
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM����ģʽ
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //�жϷ����ʼ��
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;                     //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //�����ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);     //��������ж� ,����CC1IE�����ж�

    //��ʼ��TIM���벶�����
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //�����ز���
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //���������Ƶ,����Ƶ
    TIM_ICInitStructure.TIM_ICFilter = USER_CAP_FILTER;//IC1F=0000 ���������˲��� ���˲�

#if CAP_TIM5_CH1
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
    TIM_ITConfig(TIM5, TIM_IT_CC1, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM5_CH2
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
    TIM_ITConfig(TIM5, TIM_IT_CC2, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM5_CH3
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
    TIM_ITConfig(TIM5, TIM_IT_CC3, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM5_CH4
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
    TIM_ITConfig(TIM5, TIM_IT_CC4, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
    TIM_Cmd(TIM5, ENABLE);//ʹ��TIM5
}
void TIM5_Cap_IRQ(void)
{
#define TIMx TIM5
#if CAP_TIM5_CH1
    DEFTIM_CAP_CH(5, 1)
#endif
#if CAP_TIM5_CH2
    DEFTIM_CAP_CH(5, 2)
#endif
#if CAP_TIM5_CH3
    DEFTIM_CAP_CH(5, 3)
#endif
#if CAP_TIM5_CH4
    DEFTIM_CAP_CH(5, 4)
#endif
    TIM_ClearITPendingBit(TIMx, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update); //����жϱ�־λ
#undef TIMx
}
#endif

//TIM8 CAP���ֳ�ʼ��
//CAP�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
#if (CAP_TIM8_CH1)||(CAP_TIM8_CH2)||(CAP_TIM8_CH3)||(CAP_TIM8_CH4)
void TIM8_Cap_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);   //ʹ�ܶ�ʱ��3ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    //TIM_DeInit(TIM8);
    TIM_DeInit(TIM8);
#if CAP_TIM8_CH1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_6);                //����
#endif
#if CAP_TIM8_CH2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_7);                //����
#endif
#if CAP_TIM8_CH3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_8);                //����
#endif
#if CAP_TIM8_CH4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_9);                //����
#endif
    //��ʼ��TIM8
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM����ģʽ
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //�жϷ����ʼ��
    NVIC_InitStructure.NVIC_IRQChannel = TIM8_CC_IRQn;                     //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //�����ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
    TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);     //��������ж� ,����CC1IE�����ж�

    //��ʼ��TIM���벶�����
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //�����ز���
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //���������Ƶ,����Ƶ
    TIM_ICInitStructure.TIM_ICFilter = USER_CAP_FILTER;//IC1F=0000 ���������˲��� ���˲�

#if CAP_TIM8_CH1
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM8, &TIM_ICInitStructure);
    TIM_ITConfig(TIM8, TIM_IT_CC1, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM8_CH2
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM8, &TIM_ICInitStructure);
    TIM_ITConfig(TIM8, TIM_IT_CC2, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM8_CH3
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM8, &TIM_ICInitStructure);
    TIM_ITConfig(TIM8, TIM_IT_CC3, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM8_CH4
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInit(TIM8, &TIM_ICInitStructure);
    TIM_ITConfig(TIM8, TIM_IT_CC4, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
    TIM_Cmd(TIM8, ENABLE);//ʹ��TIM8
}
void TIM8_Cap_IRQ(void)
{
#define TIMx TIM8
#if CAP_TIM8_CH1
    DEFTIM_CAP_CH(8, 1)
		#endif
#if CAP_TIM8_CH2
    DEFTIM_CAP_CH(8, 2)
		#endif
#if CAP_TIM8_CH3
    DEFTIM_CAP_CH(8, 3)
		#endif
#if CAP_TIM8_CH4
    DEFTIM_CAP_CH(8, 4)
		#endif
    TIM_ClearITPendingBit(TIMx, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update); //����жϱ�־λ
#undef TIMx
}
#endif

//TIM1 CAP���ֳ�ʼ��
//CAP�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
#if (CAP_TIM1_CH1)||(CAP_TIM1_CH2)||(CAP_TIM1_CH3)||(CAP_TIM1_CH4)
void TIM1_Cap_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);    //ʹ�ܶ�ʱ��3ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    TIM_DeInit(TIM1);
#if   (CAP_TIM1_AFIO==0)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
#elif (CAP_TIM1_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
#elif (CAP_TIM1_AFIO==2)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
#endif
#if CAP_TIM1_CH1
#if   ((CAP_TIM1_AFIO==0)||(CAP_TIM1_AFIO==1))
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_8);                //����
#elif (CAP_TIM1_AFIO==2)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOE, GPIO_Pin_9);                //����
#endif
#endif
#if CAP_TIM1_CH2
#if   ((CAP_TIM1_AFIO==0)||(CAP_TIM1_AFIO==1))
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_9);                //����
#elif (CAP_TIM1_AFIO==2)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOE, GPIO_Pin_11);                //����
#endif
#endif
#if CAP_TIM1_CH3
#if   ((CAP_TIM1_AFIO==0)||(CAP_TIM1_AFIO==1))
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_10);                //����
#elif (CAP_TIM1_AFIO==2)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOE, GPIO_Pin_13);                //����
#endif
#endif
#if CAP_TIM1_CH4
#if   ((CAP_TIM1_AFIO==0)||(CAP_TIM1_AFIO==1))
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_11);                //����
#elif (CAP_TIM1_AFIO==2)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);            //��ʼ��GPIO
    GPIO_ResetBits(GPIOE, GPIO_Pin_14);                //����
#endif
#endif
    //��ʼ��TIM1
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM����ģʽ
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

    //�жϷ����ʼ��
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;                     //TIM3�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //�����ȼ�0��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);     //��������ж� ,����CC1IE�����ж�

    //��ʼ��TIM���벶�����
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //�����ز���
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //���������Ƶ,����Ƶ
    TIM_ICInitStructure.TIM_ICFilter = USER_CAP_FILTER;//IC1F=0000 ���������˲��� ���˲�

#if CAP_TIM1_CH1
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM1, &TIM_ICInitStructure);
    TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM1_CH2
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM1, &TIM_ICInitStructure);
    TIM_ITConfig(TIM1, TIM_IT_CC2, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM1_CH3
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM1, &TIM_ICInitStructure);
    TIM_ITConfig(TIM1, TIM_IT_CC3, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
#if CAP_TIM1_CH4
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInit(TIM1, &TIM_ICInitStructure);
    TIM_ITConfig(TIM1, TIM_IT_CC4, ENABLE);     //��������ж� ,����CC1IE�����ж�
#endif
    TIM_Cmd(TIM1, ENABLE);//ʹ��TIM1
}
//��ʱ���жϷ������
void TIM1_Cap_IRQ(void)
{
#define TIMx TIM1
#if CAP_TIM1_CH1
    DEFTIM_CAP_CH(1, 1)
#endif
#if CAP_TIM1_CH2
    DEFTIM_CAP_CH(1, 2)
#endif
#if CAP_TIM1_CH3
    DEFTIM_CAP_CH(1, 3)
#endif
#if CAP_TIM1_CH4
    DEFTIM_CAP_CH(1, 4)
#endif
    TIM_ClearITPendingBit(TIMx, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update); //����жϱ�־λ
#undef TIMx
}
#endif


////u32 time_high(void)
////{
////    u32 temp;
////    while (1)
////    {
////        if (TIM5CH1_CAPTURE_STA & 0X80) //�ɹ�������һ��������
////        {
////            temp = TIM5CH1_CAPTURE_STA & 0X3F;
////            temp *= 65536; //���ʱ���ܺ�
////            temp += TIM5CH1_CAPTURE_VAL; //�õ��ܵĸߵ�ƽʱ��
////            USART_OUT(USART1, "HIGH:&dms %dus\r\n", temp / 1000, temp % 1000); //��ӡ�ܵĸߵ�ƽʱ��
////            TIM5CH1_CAPTURE_STA = 0; //������һ�β���
////            break;
////        }
////    }
////    return temp;
////}


////��ߵ�ƽʱ��
///*****************************************************************************************************************************/



////�����θߵ�ƽ֮�� ʱ��
///***************************************************************************************************************/
//void TIM4_3_Cap_Init(u16 arr, u16 psc)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//    NVIC_InitTypeDef            NVIC_InitStructure;
//    TIM_ICInitTypeDef           TIM4_ICInitStructure;

//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   //ʹ��TIM5ʱ��
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOAʱ��

//    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;    //PA0 ���֮ǰ����
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����
//    GPIO_Init(GPIOB, &GPIO_InitStructure);
//    GPIO_ResetBits(GPIOB, GPIO_Pin_8);                       //PA0 ����

//    //��ʼ����ʱ��5 TIM5
//    TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ
//    TIM_TimeBaseStructure.TIM_Prescaler = psc;  //Ԥ��Ƶ��
//    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

//    //��ʼ��TIM5���벶�����
//    TIM4_ICInitStructure.TIM_Channel        = TIM_Channel_3; //CC1S=01     ѡ������� IC1ӳ�䵽TI1��
//    TIM4_ICInitStructure.TIM_ICPolarity     = TIM_ICPolarity_Rising;        //�����ز���
//    TIM4_ICInitStructure.TIM_ICSelection    = TIM_ICSelection_DirectTI;     //ӳ�䵽TI1��
//    TIM4_ICInitStructure.TIM_ICPrescaler    = TIM_ICPSC_DIV1;                       //���������Ƶ,����Ƶ
//    TIM4_ICInitStructure.TIM_ICFilter = USER_CAP_FILTER;//IC1F=0000 ���������˲��� ���˲�
//    TIM_ICInit(TIM4, &TIM4_ICInitStructure);

//    //�жϷ����ʼ��
//    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                     //TIM3�ж�
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�2��
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //�����ȼ�0��
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQͨ����ʹ��
//    NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

//    TIM_ITConfig(TIM4, TIM_IT_Update | TIM_IT_CC3, ENABLE);     //��������ж� ,����CC1IE�����ж�
//    TIM_Cmd(TIM4, ENABLE ); //ʹ�ܶ�ʱ��5
//}

//#define TIMxCHx_CAPTURE_STA TIM4CH3_CAPTURE_STA
//#define TIMxCHx_CAPTURE_VAL TIM4CH3_CAPTURE_VAL
//u8  TIMxCHx_CAPTURE_STA = 0;//���벶��״̬
//u16 TIMxCHx_CAPTURE_VAL;    //���벶��ֵ
//void TIM4_Cap_IRQ(void)
//{
//    if ((TIMxCHx_CAPTURE_STA & 0X80) == 0) //��δ�ɹ�����
//    {
//        if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
//        {
//            if (TIMxCHx_CAPTURE_STA & 0X40) //�Ѿ����񵽸ߵ�ƽ��
//            {
//                if ((TIMxCHx_CAPTURE_STA & 0X3F) == 0X3F) //�ߵ�ƽ̫����
//                {
//                    TIMxCHx_CAPTURE_STA |= 0X80; //��ǳɹ�������һ��
//                    TIMxCHx_CAPTURE_VAL = 0XFFFF;
//                }
//                else TIMxCHx_CAPTURE_STA++;
//            }
//        }
//        if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)//����1���������¼�
//        {
//            if (TIMxCHx_CAPTURE_STA & 0X40)     //����һ���½���
//            {
//                TIMxCHx_CAPTURE_STA |= 0X80;    //��ǳɹ�����һ��������
//                TIMxCHx_CAPTURE_VAL = TIM_GetCapture3(TIM4);
//            }
//            else                                //��δ��ʼ,��һ�β���������
//            {
//                TIMxCHx_CAPTURE_STA = 0;        //���
//                TIMxCHx_CAPTURE_VAL = 0;
//                TIM_SetCounter(TIM4, 0);
//                TIMxCHx_CAPTURE_STA |= 0X40;    //��ǲ�����������
//            }
//        }
//    }
//    TIM_ClearITPendingBit(TIM4, TIM_IT_CC3 | TIM_IT_Update); //����жϱ�־λ
//}
//u32 time_high_high(void)
//{
//    static u32 temp;
//    while (1)
//    {
//        if (TIM4CH3_CAPTURE_STA & 0X80) //�ɹ�������һ��������
//        {
//            temp = 0;
//            temp = TIM4CH3_CAPTURE_STA & 0X3F;
//            temp *= 65536; //���ʱ���ܺ�
//            temp += TIM4CH3_CAPTURE_VAL; //�õ��ܵĸߵ�ƽʱ��
//            TIM4CH3_CAPTURE_STA = 0; //������һ�β���
//            break;
//        }
//        return temp;
//    }
//    return temp;
//}
////�����θߵ�ƽ֮�� ʱ��
///***************************************************************************************************************/


