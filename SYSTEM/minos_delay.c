#include "minos_delay.h"
#include "sys_os.h"
#include "sys.h"

/////////////////////////////////////////////////////////////////////////////////////
static u8  fac_us = 0; //us��ʱ������

//��ʼ���ӳٺ���
//��ʹ��ucos��ʱ��,�˺������ʼ��ucos��ʱ�ӽ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
void delay_init()
{
#ifdef OS_CRITICAL_METHOD   //���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
    u32 reload;//��װ��ֵ
#endif
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);   //ѡ���ⲿʱ��  HCLK/8 //Ϊϵͳʱ�ӵ�1/8
    fac_us = SystemCoreClock / 8000000;

#ifdef OS_CRITICAL_METHOD   //���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
    reload = SystemCoreClock / 8000000; //ÿ���ӵļ������� ��λΪK
    reload *= 1000000 / OS_TICKS_PER_SEC; //����OS_TICKS_PER_SEC�趨���ʱ��
    //reloadΪ24λ�Ĵ���,���ֵ:16777216,��72M��,Լ��1.86s����
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;  //����SYSTICK�ж�
    SysTick->LOAD = reload; //ÿ1/OS_TICKS_PER_SEC���ж�һ��
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;   //����SYSTICK
#else
    fac_ms = (u16)fac_us * 1000; //��ucos��,����ÿ��ms��Ҫ��systickʱ����
#endif
}

#ifdef OS_CRITICAL_METHOD   //ʹ����ucos
//��ʱnus
//nusΪҪ��ʱ��us��.
void delay_us(u32 nus)
{
    u32 ticks;
    u32 told, tnow, tcnt = 0;
    u32 reload = SysTick->LOAD; //LOAD��ֵ
    ticks = nus * fac_us;       //��Ҫ�Ľ�����
    tcnt = 0;
    told = SysTick->VAL;        //�ս���ʱ�ļ�����ֵ
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)tcnt += told - tnow; //����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
            else tcnt += reload - tnow + told;
            told = tnow;
            if (tcnt >= ticks)break; //ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
        }
    };
}
//��ʱnms
//nms:Ҫ��ʱ��ms��
void delay_ms(u16 nms)
{
    for (int i = 0; i < nms; i++)
    {
        delay_us((u32)(1000)); //��ͨ��ʽ��ʱ,��ʱucos�޷���������.
    }
}
extern u32 SysTick_Time;
u32 SysTick_Clock(void)
{
    return (((SysTick_Time + 1) * SysTick->LOAD) - SysTick->VAL) / (SystemCoreClock / 8000 / OS_TICKS_PER_SEC);
}

#else //����ucosʱ
//��ʱnus
//nusΪҪ��ʱ��us��.
void delay_us(u32 nus)
{
    u32 temp;
    SysTick->LOAD = nus * fac_us; //ʱ�����
    SysTick->VAL = 0x00;      //��ռ�����
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;        //��ʼ����
    do
    {
        temp = SysTick->CTRL;
    }
    while (temp & 0x01 && !(temp & (1 << 16))); //�ȴ�ʱ�䵽��
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;     //�رռ�����
    SysTick->VAL = 0X00;      //��ռ�����
}
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864
void delay_ms(u16 nms)
{
    u32 temp;
    SysTick->LOAD = (u32)nms * fac_ms; //ʱ�����(SysTick->LOADΪ24bit)
    SysTick->VAL = 0x00;          //��ռ�����
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;        //��ʼ����
    do
    {
        temp = SysTick->CTRL;
    }
    while (temp & 0x01 && !(temp & (1 << 16))); //�ȴ�ʱ�䵽��
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;     //�رռ�����
    SysTick->VAL = 0X00;      //��ռ�����
}
#endif
