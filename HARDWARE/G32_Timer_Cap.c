#include "G32_timer_cap.h"
#include "stm32f10x_it.h"
//#include "usart.h"
/**
 * stm32f103vct6 100pin
 * data
 */
// #include "G32_timer_cap.h"
/*
例
//    ***捕获***
//    TIM5_Cap_Init(0XFFFF, 72 - 1);
//    while (1)
//    {
//        delay_ms(10);
//        if (TIM5CH1_CAPTURE_STA & 0X80) //成功捕获到了一次上升沿
//        {
//            temp = TIM5CH1_CAPTURE_STA & 0X3F;
//            temp *= 65536; //溢出时间总和
//            temp += TIM5CH1_CAPTURE_VAL; //得到总的高电平时间
//            USART_OUT(USART1, "HIGH高:%d us\r\n", temp); //打印总的高点平时间
//            TIM5CH1_CAPTURE_STA = 0; //开启下一次捕获
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
 * CAP输出初始化
 * @param arr [自动重装载值]
 * @param psc [始终预分频值]
 */
void TIM2_Cap_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//使能定时器X时钟
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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIO外设和AFIO复用功能模块时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);             //初始化GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);                 //PA0 下拉

#elif ((CAP_TIM2_AFIO==1)||(CAP_TIM2_AFIO==3))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIO外设和AFIO复用功能模块时钟
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);             //初始化GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_15);                //PA0 下拉
#endif
#endif
#if CAP_TIM2_CH2
#if ((CAP_TIM2_AFIO==0)||(CAP_TIM2_AFIO==2))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIO外设和AFIO复用功能模块时钟
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;     //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);               //初始化GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);                //PA0 下拉

#elif ((CAP_TIM2_AFIO==1)||(CAP_TIM2_AFIO==3))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能GPIO外设和AFIO复用功能模块时钟
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;     //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_3);                //下拉

#endif
#endif
#if CAP_TIM2_CH3
#if ((CAP_TIM2_AFIO==0)||(CAP_TIM2_AFIO==1))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIO外设和AFIO复用功能模块时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);                //下拉               //初始化GPIO
#elif ((CAP_TIM2_AFIO==2)||(CAP_TIM2_AFIO==3))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能GPIO外设和AFIO复用功能模块时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_10);                //下拉
#endif
#endif
#if CAP_TIM2_CH4
#if ((CAP_TIM2_AFIO==0)||(CAP_TIM2_AFIO==1))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIO外设和AFIO复用功能模块时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_3);                //下拉               //初始化GPIO
#elif ((CAP_TIM2_AFIO==2)||(CAP_TIM2_AFIO==3))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能GPIO外设和AFIO复用功能模块时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;      //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_11);                //下拉
#endif
#endif
    //初始化TIM2
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM计数模式
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    //中断分组初始化
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                     //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //从优先级0级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断

    //初始化TIM输入捕获参数
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //上升沿捕获
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //配置输入分频,不分频
    TIM_ICInitStructure.TIM_ICFilter = USER_CAP_FILTER;//IC1F=0000 配置输入滤波器 不滤波

#if CAP_TIM2_CH1
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM2_CH2
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM2_CH3
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM2_CH4
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_ITConfig(TIM2, TIM_IT_CC4, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
    TIM_Cmd(TIM2, ENABLE);//使能TIM2
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
    TIM_ClearITPendingBit(TIMx, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update); //清除中断标志位
#undef TIMx
}
#endif

//TIM3 CAP部分初始化
//CAP输出初始化
//arr：自动重装值
//psc：时钟预分频数
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
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_6);                //下拉
#elif (CAP_TIM3_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_6);                //下拉
#elif (CAP_TIM3_AFIO==3)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_6);                //下拉
#endif
#endif
#if CAP_TIM3_CH2
#if     (CAP_TIM3_AFIO==0)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_7);                //下拉
#elif (CAP_TIM3_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);                //下拉
#elif (CAP_TIM3_AFIO==3)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_7);                //下拉
#endif
#endif
#if CAP_TIM3_CH3
#if ((CAP_TIM3_AFIO==0)||(CAP_TIM3_AFIO==1))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);                //下拉
#elif (CAP_TIM3_AFIO==3)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_8);                //下拉
#endif
#endif
#if CAP_TIM3_CH4
#if ((CAP_TIM3_AFIO==0)||(CAP_TIM3_AFIO==1))
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_1);                //下拉
#elif (CAP_TIM3_AFIO==3)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_9);                //下拉
#endif
#endif

    //初始化TIM3
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    //中断分组初始化
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                     //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //从优先级0级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断

    //初始化TIM输入捕获参数
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //上升沿捕获
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //配置输入分频,不分频
    TIM_ICInitStructure.TIM_ICFilter = USER_CAP_FILTER;//IC1F=0000 配置输入滤波器 不滤波

#if CAP_TIM3_CH1
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    TIM_ITConfig(TIM3, TIM_IT_CC1, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM3_CH2
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM3_CH3
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    TIM_ITConfig(TIM3, TIM_IT_CC3, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM3_CH4
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    TIM_ITConfig(TIM3, TIM_IT_CC4, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
    TIM_Cmd(TIM3, ENABLE);//使能TIM3
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
    TIM_ClearITPendingBit(TIMx, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update); //清除中断标志位
#undef TIMx
}
#endif
//TIM4 CAP部分初始化
//CAP输出初始化
//arr：自动重装值
//psc：时钟预分频数
#if (CAP_TIM4_CH1)||(CAP_TIM4_CH2)||(CAP_TIM4_CH3)||(CAP_TIM4_CH4)
void TIM4_Cap_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
#if   (CAP_TIM4_AFIO==0)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
#elif (CAP_TIM4_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
#endif
#if CAP_TIM4_CH1
#if   (CAP_TIM4_AFIO==0)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_6);                //下拉
#elif (CAP_TIM4_AFIO==1)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOD, GPIO_Pin_12);                //下拉
#endif
#endif
#if CAP_TIM4_CH2
#if   (CAP_TIM4_AFIO==0)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_7);                //下拉
#elif (CAP_TIM4_AFIO==1)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOD, GPIO_Pin_13);                //下拉
#endif
#endif
#if CAP_TIM4_CH3
#if   (CAP_TIM4_AFIO==0)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_8);                //下拉
#elif (CAP_TIM4_AFIO==1)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOD, GPIO_Pin_14);                //下拉
#endif
#endif
#if CAP_TIM4_CH4
#if   (CAP_TIM4_AFIO==0)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOB, GPIO_Pin_9);                //下拉
#elif (CAP_TIM4_AFIO==1)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOD, GPIO_Pin_15);                //下拉
#endif
#endif
    //初始化TIM4
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM计数模式
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    //中断分组初始化
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                     //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //从优先级0级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断

    //初始化TIM输入捕获参数
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //上升沿捕获
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //配置输入分频,不分频
    TIM_ICInitStructure.TIM_ICFilter = USER_CAP_FILTER;//IC1F=0000 配置输入滤波器 不滤波

#if CAP_TIM4_CH1
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
    TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM4_CH2
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
    TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM4_CH3
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
    TIM_ITConfig(TIM4, TIM_IT_CC3, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM4_CH4
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);
    TIM_ITConfig(TIM4, TIM_IT_CC4, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
    TIM_Cmd(TIM4, ENABLE);//使能TIM4
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
    TIM_ClearITPendingBit(TIMx, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update); //清除中断标志位
#undef TIMx
}
#endif


//TIM5 CAP部分初始化
//CAP输出初始化
//arr：自动重装值
//psc：时钟预分频数
#if (CAP_TIM5_CH1)||(CAP_TIM5_CH2)||(CAP_TIM5_CH3)||(CAP_TIM5_CH4)
void TIM5_Cap_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);    //使能定时器3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
#if CAP_TIM5_CH1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);                //下拉
#endif
#if CAP_TIM5_CH2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);                //下拉
#endif
#if CAP_TIM5_CH3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);                //下拉
#endif
#if CAP_TIM5_CH4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_3);                //下拉
#endif
    //初始化TIM5
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM计数模式
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    //中断分组初始化
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;                     //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //从优先级0级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断

    //初始化TIM输入捕获参数
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //上升沿捕获
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //配置输入分频,不分频
    TIM_ICInitStructure.TIM_ICFilter = USER_CAP_FILTER;//IC1F=0000 配置输入滤波器 不滤波

#if CAP_TIM5_CH1
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
    TIM_ITConfig(TIM5, TIM_IT_CC1, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM5_CH2
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
    TIM_ITConfig(TIM5, TIM_IT_CC2, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM5_CH3
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
    TIM_ITConfig(TIM5, TIM_IT_CC3, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM5_CH4
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
    TIM_ITConfig(TIM5, TIM_IT_CC4, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
    TIM_Cmd(TIM5, ENABLE);//使能TIM5
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
    TIM_ClearITPendingBit(TIMx, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update); //清除中断标志位
#undef TIMx
}
#endif

//TIM8 CAP部分初始化
//CAP输出初始化
//arr：自动重装值
//psc：时钟预分频数
#if (CAP_TIM8_CH1)||(CAP_TIM8_CH2)||(CAP_TIM8_CH3)||(CAP_TIM8_CH4)
void TIM8_Cap_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);   //使能定时器3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
    //TIM_DeInit(TIM8);
    TIM_DeInit(TIM8);
#if CAP_TIM8_CH1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_6);                //下拉
#endif
#if CAP_TIM8_CH2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_7);                //下拉
#endif
#if CAP_TIM8_CH3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_8);                //下拉
#endif
#if CAP_TIM8_CH4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOC, GPIO_Pin_9);                //下拉
#endif
    //初始化TIM8
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM计数模式
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    //中断分组初始化
    NVIC_InitStructure.NVIC_IRQChannel = TIM8_CC_IRQn;                     //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //从优先级0级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断

    //初始化TIM输入捕获参数
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //上升沿捕获
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //配置输入分频,不分频
    TIM_ICInitStructure.TIM_ICFilter = USER_CAP_FILTER;//IC1F=0000 配置输入滤波器 不滤波

#if CAP_TIM8_CH1
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM8, &TIM_ICInitStructure);
    TIM_ITConfig(TIM8, TIM_IT_CC1, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM8_CH2
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM8, &TIM_ICInitStructure);
    TIM_ITConfig(TIM8, TIM_IT_CC2, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM8_CH3
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM8, &TIM_ICInitStructure);
    TIM_ITConfig(TIM8, TIM_IT_CC3, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM8_CH4
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInit(TIM8, &TIM_ICInitStructure);
    TIM_ITConfig(TIM8, TIM_IT_CC4, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
    TIM_Cmd(TIM8, ENABLE);//使能TIM8
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
    TIM_ClearITPendingBit(TIMx, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update); //清除中断标志位
#undef TIMx
}
#endif

//TIM1 CAP部分初始化
//CAP输出初始化
//arr：自动重装值
//psc：时钟预分频数
#if (CAP_TIM1_CH1)||(CAP_TIM1_CH2)||(CAP_TIM1_CH3)||(CAP_TIM1_CH4)
void TIM1_Cap_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef  TIM_ICInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);    //使能定时器3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
    TIM_DeInit(TIM1);
#if   (CAP_TIM1_AFIO==0)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
#elif (CAP_TIM1_AFIO==1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
#elif (CAP_TIM1_AFIO==2)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
#endif
#if CAP_TIM1_CH1
#if   ((CAP_TIM1_AFIO==0)||(CAP_TIM1_AFIO==1))
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_8);                //下拉
#elif (CAP_TIM1_AFIO==2)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOE, GPIO_Pin_9);                //下拉
#endif
#endif
#if CAP_TIM1_CH2
#if   ((CAP_TIM1_AFIO==0)||(CAP_TIM1_AFIO==1))
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_9);                //下拉
#elif (CAP_TIM1_AFIO==2)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOE, GPIO_Pin_11);                //下拉
#endif
#endif
#if CAP_TIM1_CH3
#if   ((CAP_TIM1_AFIO==0)||(CAP_TIM1_AFIO==1))
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_10);                //下拉
#elif (CAP_TIM1_AFIO==2)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOE, GPIO_Pin_13);                //下拉
#endif
#endif
#if CAP_TIM1_CH4
#if   ((CAP_TIM1_AFIO==0)||(CAP_TIM1_AFIO==1))
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOA, GPIO_Pin_11);                //下拉
#elif (CAP_TIM1_AFIO==2)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);            //初始化GPIO
    GPIO_ResetBits(GPIOE, GPIO_Pin_14);                //下拉
#endif
#endif
    //初始化TIM1
    TIM_TimeBaseStructure.TIM_Period = arr - 1;    //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1; //设置用来作为TIMx时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;   //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM计数模式
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    //中断分组初始化
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;                     //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;      //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //从优先级0级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断

    //初始化TIM输入捕获参数
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;    //上升沿捕获
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;   //配置输入分频,不分频
    TIM_ICInitStructure.TIM_ICFilter = USER_CAP_FILTER;//IC1F=0000 配置输入滤波器 不滤波

#if CAP_TIM1_CH1
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInit(TIM1, &TIM_ICInitStructure);
    TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM1_CH2
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIM1, &TIM_ICInitStructure);
    TIM_ITConfig(TIM1, TIM_IT_CC2, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM1_CH3
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM_ICInit(TIM1, &TIM_ICInitStructure);
    TIM_ITConfig(TIM1, TIM_IT_CC3, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
#if CAP_TIM1_CH4
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM_ICInit(TIM1, &TIM_ICInitStructure);
    TIM_ITConfig(TIM1, TIM_IT_CC4, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
#endif
    TIM_Cmd(TIM1, ENABLE);//使能TIM1
}
//定时器中断服务程序
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
    TIM_ClearITPendingBit(TIMx, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4 | TIM_IT_Update); //清除中断标志位
#undef TIMx
}
#endif


////u32 time_high(void)
////{
////    u32 temp;
////    while (1)
////    {
////        if (TIM5CH1_CAPTURE_STA & 0X80) //成功捕获到了一次上升沿
////        {
////            temp = TIM5CH1_CAPTURE_STA & 0X3F;
////            temp *= 65536; //溢出时间总和
////            temp += TIM5CH1_CAPTURE_VAL; //得到总的高电平时间
////            USART_OUT(USART1, "HIGH:&dms %dus\r\n", temp / 1000, temp % 1000); //打印总的高点平时间
////            TIM5CH1_CAPTURE_STA = 0; //开启下一次捕获
////            break;
////        }
////    }
////    return temp;
////}


////测高电平时间
///*****************************************************************************************************************************/



////测两次高电平之间 时间
///***************************************************************************************************************/
//void TIM4_3_Cap_Init(u16 arr, u16 psc)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//    NVIC_InitTypeDef            NVIC_InitStructure;
//    TIM_ICInitTypeDef           TIM4_ICInitStructure;

//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);   //使能TIM5时钟
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //使能GPIOA时钟

//    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;    //PA0 清除之前设置
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 输入
//    GPIO_Init(GPIOB, &GPIO_InitStructure);
//    GPIO_ResetBits(GPIOB, GPIO_Pin_8);                       //PA0 下拉

//    //初始化定时器5 TIM5
//    TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值
//    TIM_TimeBaseStructure.TIM_Prescaler = psc;  //预分频器
//    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

//    //初始化TIM5输入捕获参数
//    TIM4_ICInitStructure.TIM_Channel        = TIM_Channel_3; //CC1S=01     选择输入端 IC1映射到TI1上
//    TIM4_ICInitStructure.TIM_ICPolarity     = TIM_ICPolarity_Rising;        //上升沿捕获
//    TIM4_ICInitStructure.TIM_ICSelection    = TIM_ICSelection_DirectTI;     //映射到TI1上
//    TIM4_ICInitStructure.TIM_ICPrescaler    = TIM_ICPSC_DIV1;                       //配置输入分频,不分频
//    TIM4_ICInitStructure.TIM_ICFilter = USER_CAP_FILTER;//IC1F=0000 配置输入滤波器 不滤波
//    TIM_ICInit(TIM4, &TIM4_ICInitStructure);

//    //中断分组初始化
//    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                     //TIM3中断
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //先占优先级2级
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //从优先级0级
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     //IRQ通道被使能
//    NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

//    TIM_ITConfig(TIM4, TIM_IT_Update | TIM_IT_CC3, ENABLE);     //允许更新中断 ,允许CC1IE捕获中断
//    TIM_Cmd(TIM4, ENABLE ); //使能定时器5
//}

//#define TIMxCHx_CAPTURE_STA TIM4CH3_CAPTURE_STA
//#define TIMxCHx_CAPTURE_VAL TIM4CH3_CAPTURE_VAL
//u8  TIMxCHx_CAPTURE_STA = 0;//输入捕获状态
//u16 TIMxCHx_CAPTURE_VAL;    //输入捕获值
//void TIM4_Cap_IRQ(void)
//{
//    if ((TIMxCHx_CAPTURE_STA & 0X80) == 0) //还未成功捕获
//    {
//        if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
//        {
//            if (TIMxCHx_CAPTURE_STA & 0X40) //已经捕获到高电平了
//            {
//                if ((TIMxCHx_CAPTURE_STA & 0X3F) == 0X3F) //高电平太长了
//                {
//                    TIMxCHx_CAPTURE_STA |= 0X80; //标记成功捕获了一次
//                    TIMxCHx_CAPTURE_VAL = 0XFFFF;
//                }
//                else TIMxCHx_CAPTURE_STA++;
//            }
//        }
//        if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)//捕获1发生捕获事件
//        {
//            if (TIMxCHx_CAPTURE_STA & 0X40)     //捕获到一个下降沿
//            {
//                TIMxCHx_CAPTURE_STA |= 0X80;    //标记成功捕获到一次上升沿
//                TIMxCHx_CAPTURE_VAL = TIM_GetCapture3(TIM4);
//            }
//            else                                //还未开始,第一次捕获上升沿
//            {
//                TIMxCHx_CAPTURE_STA = 0;        //清空
//                TIMxCHx_CAPTURE_VAL = 0;
//                TIM_SetCounter(TIM4, 0);
//                TIMxCHx_CAPTURE_STA |= 0X40;    //标记捕获到了上升沿
//            }
//        }
//    }
//    TIM_ClearITPendingBit(TIM4, TIM_IT_CC3 | TIM_IT_Update); //清除中断标志位
//}
//u32 time_high_high(void)
//{
//    static u32 temp;
//    while (1)
//    {
//        if (TIM4CH3_CAPTURE_STA & 0X80) //成功捕获到了一次上升沿
//        {
//            temp = 0;
//            temp = TIM4CH3_CAPTURE_STA & 0X3F;
//            temp *= 65536; //溢出时间总和
//            temp += TIM4CH3_CAPTURE_VAL; //得到总的高电平时间
//            TIM4CH3_CAPTURE_STA = 0; //开启下一次捕获
//            break;
//        }
//        return temp;
//    }
//    return temp;
//}
////测两次高电平之间 时间
///***************************************************************************************************************/


