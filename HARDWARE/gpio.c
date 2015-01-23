#include "gpio.h"
/*
    GPIO_InitTypeDef GPIO_InitStructure;
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOX, ENABLE); //GPIOAʱ���Լ����ù���ʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x; //PX,x
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
    GPIO_Init(GPIOX, &GPIO_InitStructure);
        GPIO_SetBits(LCD_LIGHT_GPIO,LCD_LIGHT_Pin);
        GPIO_ResetBits(LCD_LIGHT_GPIO,LCD_LIGHT_Pin);

GPIOA_Init(0,3,PU);



mode:
0 ģ������ģʽ(ADC��)
8 ��������
3 �������
B �������

AIN 0           //ģ������
IN_FLOATING 4   //��������
IPD 8           //��������
IPU 8           //��������

Out_PP 3        //�������
Out_OD 7        //��©���
AF_PP 0xF       //���ÿ�©���
AF_OD 0xB       //�����������

PU ����
PD ����

*/

void GPIOA_Init(u16 io, u16 mode, u8 du)
{
    u32 apb2;
    RCC->APB2ENR |= 1 << 2; //ʹ��PORTxʱ��
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
        GPIOA->ODR |= 1 << io; //PB.x �������
    else
        GPIOA->BRR |= 1 << io; //PB.x �������
}
void GPIOB_Init(u16 io, u16 mode, u8 du)
{
    u32 apb2;
    RCC->APB2ENR |= 1 << 3; //ʹ��PORTxʱ��
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
        GPIOB->ODR |= 1 << io; //PB.x �������
    else
        GPIOB->BRR |= 1 << io; //PB.x �������
}
void GPIOC_Init(u16 io, u16 mode, u8 du)
{
    u32 apb2;
    RCC->APB2ENR |= 1 << 4; //ʹ��PORTxʱ��
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
        GPIOC->ODR |= 1 << io; //PB.x �������
    else
        GPIOC->BRR |= 1 << io; //PB.x �������
}
void GPIOD_Init(u16 io, u16 mode, u8 du)
{
    u32 apb2;
    RCC->APB2ENR |= 1 << 5; //ʹ��PORTxʱ��
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
        GPIOD->ODR |= 1 << io; //PB.x �������
    else
        GPIOD->BRR |= 1 << io; //PB.x �������
}
void GPIOE_Init(u16 io, u16 mode, u8 du)
{
    u32 apb2;
    RCC->APB2ENR |= 1 << 6; //ʹ��PORTxʱ��
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
        GPIOE->ODR |= 1 << io; //PB.x �������
    else
        GPIOE->BRR |= 1 << io; //PB.x �������
}
void GPIOF_Init(u16 io, u16 mode, u8 du)
{
    u32 apb2;
    RCC->APB2ENR |= 1 << 7; //ʹ��PORTxʱ��
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
        GPIOF->ODR |= 1 << io; //PB.x �������
    else
        GPIOF->BRR |= 1 << io; //PB.x �������
}
void GPIOG_Init(u16 io, u16 mode, u8 du)
{
    u32 apb2;
    RCC->APB2ENR |= 1 << 8; //ʹ��PORTxʱ��
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
        GPIOG->ODR |= 1 << io; //PB.x �������
    else
        GPIOG->BRR |= 1 << io; //PB.x �������
}
