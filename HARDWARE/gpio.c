#include "gpio.h"
/*
    GPIO_InitTypeDef GPIO_InitStructure;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOX, ENABLE); //GPIOA时钟以及复用功能时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x; //PX,x
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
    GPIO_Init(GPIOX, &GPIO_InitStructure);
        GPIO_SetBits(LCD_LIGHT_GPIO,LCD_LIGHT_Pin);
        GPIO_ResetBits(LCD_LIGHT_GPIO,LCD_LIGHT_Pin);

GPIOA_Init(0,3,PU);



mode:
0 模拟输入模式(ADC用)
8 上拉输入
3 推挽输出
B 复用输出

AIN 0           //模拟输入
IN_FLOATING 4   //浮空输入
IPD 8           //下拉输入
IPU 8           //上拉输入

Out_PP 3        //推挽输出
Out_OD 7        //开漏输出
AF_PP 0xF       //复用开漏输出
AF_OD 0xB       //复用推挽输出

PU 上拉
PD 下拉

*/

void GPIOA_Init(u16 io, u16 mode, u8 du)
{
    u32 apb2;
    RCC->APB2ENR |= 1 << 2; //使能PORTx时钟
    if (io > 7)
    {
        io -= 8;
        apb2 = 0xf;
        apb2 = apb2 << (io * 4);
        GPIOA->CRH &= ~apb2;
        apb2 = mode;
        apb2 = apb2 << (io * 4);
        GPIOA->CRH |= apb2; //PB.x
    }
    else
    {
        apb2 = 0xf;
        apb2 = apb2 << (io * 4);
        GPIOA->CRL &= ~apb2;
        apb2 = mode;
        apb2 = apb2 << (io * 4);
        GPIOA->CRL |= apb2; //PB.x
    }
    if (du)
        GPIOA->ODR |= 1 << io; //PB.x 输出上拉
    else
        GPIOA->BRR |= 1 << io; //PB.x 输出下拉
}
void GPIOB_Init(u16 io, u16 mode, u8 du)
{
    u32 apb2;
    RCC->APB2ENR |= 1 << 3; //使能PORTx时钟
    if (io > 7)
    {
        io -= 8;
        apb2 = 0xf;
        apb2 = apb2 << (io * 4);
        GPIOB->CRH &= ~apb2;
        apb2 = mode;
        apb2 = apb2 << (io * 4);
        GPIOB->CRH |= apb2; //PB.x
    }
    else
    {
        apb2 = 0xf;
        apb2 = apb2 << (io * 4);
        GPIOB->CRL &= ~apb2;
        apb2 = mode;
        apb2 = apb2 << (io * 4);
        GPIOB->CRL |= apb2; //PB.x
    }

    if (du)
        GPIOB->ODR |= 1 << io; //PB.x 输出上拉
    else
        GPIOB->BRR |= 1 << io; //PB.x 输出下拉
}
void GPIOC_Init(u16 io, u16 mode, u8 du)
{
    u32 apb2;
    RCC->APB2ENR |= 1 << 4; //使能PORTx时钟
    if (io > 7)
    {
        io -= 8;
        apb2 = 0xf;
        apb2 = apb2 << (io * 4);
        GPIOC->CRH &= ~apb2;
        apb2 = mode;
        apb2 = apb2 << (io * 4);
        GPIOC->CRH |= apb2; //PB.x
    }
    else
    {
        apb2 = 0xf;
        apb2 = apb2 << (io * 4);
        GPIOC->CRL &= ~apb2;
        apb2 = mode;
        apb2 = apb2 << (io * 4);
        GPIOC->CRL |= apb2; //PB.x
    }

    if (du)
        GPIOC->ODR |= 1 << io; //PB.x 输出上拉
    else
        GPIOC->BRR |= 1 << io; //PB.x 输出下拉
}
void GPIOD_Init(u16 io, u16 mode, u8 du)
{
    u32 apb2;
    RCC->APB2ENR |= 1 << 5; //使能PORTx时钟
    if (io > 7)
    {
        io -= 8;
        apb2 = 0xf;
        apb2 = apb2 << (io * 4);
        GPIOD->CRH &= ~apb2;
        apb2 = mode;
        apb2 = apb2 << (io * 4);
        GPIOD->CRH |= apb2; //PB.x
    }
    else
    {
        apb2 = 0xf;
        apb2 = apb2 << (io * 4);
        GPIOD->CRL &= ~apb2;
        apb2 = mode;
        apb2 = apb2 << (io * 4);
        GPIOD->CRL |= apb2; //PB.x
    }

    if (du)
        GPIOD->ODR |= 1 << io; //PB.x 输出上拉
    else
        GPIOD->BRR |= 1 << io; //PB.x 输出下拉
}
void GPIOE_Init(u16 io, u16 mode, u8 du)
{
    u32 apb2;
    RCC->APB2ENR |= 1 << 6; //使能PORTx时钟
    if (io > 7)
    {
        io -= 8;
        apb2 = 0xf;
        apb2 = apb2 << (io * 4);
        GPIOE->CRH &= ~apb2;
        apb2 = mode;
        apb2 = apb2 << (io * 4);
        GPIOE->CRH |= apb2; //PB.x
    }
    else
    {
        apb2 = 0xf;
        apb2 = apb2 << (io * 4);
        GPIOE->CRL &= ~apb2;
        apb2 = mode;
        apb2 = apb2 << (io * 4);
        GPIOE->CRL |= apb2; //PB.x
    }
    if (du)
        GPIOE->ODR |= 1 << io; //PB.x 输出上拉
    else
        GPIOE->BRR |= 1 << io; //PB.x 输出下拉
}
void GPIOF_Init(u16 io, u16 mode, u8 du)
{
    u32 apb2;
    RCC->APB2ENR |= 1 << 7; //使能PORTx时钟
    if (io > 7)
    {
        io -= 8;
        apb2 = 0xf;
        apb2 = apb2 << (io * 4);
        GPIOF->CRH &= ~apb2;
        apb2 = mode;
        apb2 = apb2 << (io * 4);
        GPIOF->CRH |= apb2; //PB.x
    }
    else
    {
        apb2 = 0xf;
        apb2 = apb2 << (io * 4);
        GPIOF->CRL &= ~apb2;
        apb2 = mode;
        apb2 = apb2 << (io * 4);
        GPIOF->CRL |= apb2; //PB.x
    }
    if (du)
        GPIOF->ODR |= 1 << io; //PB.x 输出上拉
    else
        GPIOF->BRR |= 1 << io; //PB.x 输出下拉
}
void GPIOG_Init(u16 io, u16 mode, u8 du)
{
    u32 apb2;
    RCC->APB2ENR |= 1 << 8; //使能PORTx时钟
    if (io > 7)
    {
        io -= 8;
        apb2 = 0xf;
        apb2 = apb2 << (io * 4);
        GPIOG->CRH &= ~apb2;
        apb2 = mode;
        apb2 = apb2 << (io * 4);
        GPIOG->CRH |= apb2; //PB.x
    }
    else
    {
        apb2 = 0xf;
        apb2 = apb2 << (io * 4);
        GPIOG->CRL &= ~apb2;
        apb2 = mode;
        apb2 = apb2 << (io * 4);
        GPIOG->CRL |= apb2; //PB.x
    }
    if (du)
        GPIOG->ODR |= 1 << io; //PB.x 输出上拉
    else
        GPIOG->BRR |= 1 << io; //PB.x 输出下拉
}
