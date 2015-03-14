#ifndef __GPIO_H
#define __GPIO_H
#ifdef __cplusplus
       extern "C" {
#endif
#include "sys.h"
#define PU 1//
#define PD 0//

#define AIN 0         //模拟输入
#define IN_FLOATING 4 //浮空输入
#define IPD 8         //下拉输入
#define IPU 8         //上拉输入

#define Out_PP 3      //推挽输出
#define Out_OD 7      //开漏输出
#define AF_PP 0xF     //复用开漏输出
#define AF_OD 0xB     //复用推挽输出
//
//


extern void GPIOA_Init(u16 io, u16 mode, u8 du);
extern void GPIOB_Init(u16 io, u16 mode, u8 du);
extern void GPIOC_Init(u16 io, u16 mode, u8 du);
extern void GPIOD_Init(u16 io, u16 mode, u8 du);
extern void GPIOE_Init(u16 io, u16 mode, u8 du);
extern void GPIOF_Init(u16 io, u16 mode, u8 du);
extern void GPIOG_Init(u16 io, u16 mode, u8 du);


#define PA0_OUT   GPIOA_Init(0 ,Out_PP,PU);
#define PA1_OUT   GPIOA_Init(1 ,Out_PP,PU);
#define PA2_OUT   GPIOA_Init(2 ,Out_PP,PU);
#define PA3_OUT   GPIOA_Init(3 ,Out_PP,PU);
#define PA4_OUT   GPIOA_Init(4 ,Out_PP,PU);
#define PA5_OUT   GPIOA_Init(5 ,Out_PP,PU);
#define PA6_OUT   GPIOA_Init(6 ,Out_PP,PU);
#define PA7_OUT   GPIOA_Init(7 ,Out_PP,PU);
#define PA8_OUT   GPIOA_Init(8 ,Out_PP,PU);
#define PA9_OUT   GPIOA_Init(9 ,Out_PP,PU);
#define PA10_OUT  GPIOA_Init(10,Out_PP,PU);
#define PA11_OUT  GPIOA_Init(11,Out_PP,PU);
#define PA12_OUT  GPIOA_Init(12,Out_PP,PU);
#define PA13_OUT  RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);GPIOA_Init(13,Out_PP,PU);
#define PA14_OUT  RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);GPIOA_Init(14,Out_PP,PU);
#define PA15_OUT  RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);GPIOA_Init(15,Out_PP,PU);

#define PB0_OUT   GPIOB_Init(0 ,Out_PP,PU);
#define PB1_OUT   GPIOB_Init(1 ,Out_PP,PU);
#define PB2_OUT   GPIOB_Init(2 ,Out_PP,PU);
#define PB3_OUT   RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);GPIOB_Init(3 ,Out_PP,PU);
#define PB4_OUT   RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);GPIOB_Init(4 ,Out_PP,PU);
#define PB5_OUT   GPIOB_Init(5 ,Out_PP,PU);
#define PB6_OUT   GPIOB_Init(6 ,Out_PP,PU);
#define PB7_OUT   GPIOB_Init(7 ,Out_PP,PU);
#define PB8_OUT   GPIOB_Init(8 ,Out_PP,PU);
#define PB9_OUT   GPIOB_Init(9 ,Out_PP,PU);
#define PB10_OUT  GPIOB_Init(10,Out_PP,PU);
#define PB11_OUT  GPIOB_Init(11,Out_PP,PU);
#define PB12_OUT  GPIOB_Init(12,Out_PP,PU);
#define PB13_OUT  GPIOB_Init(13,Out_PP,PU);
#define PB14_OUT  GPIOB_Init(14,Out_PP,PU);
#define PB15_OUT  GPIOB_Init(15,Out_PP,PU);

#define PC0_OUT   GPIOC_Init(0 ,Out_PP,PU);
#define PC1_OUT   GPIOC_Init(1 ,Out_PP,PU);
#define PC2_OUT   GPIOC_Init(2 ,Out_PP,PU);
#define PC3_OUT   GPIOC_Init(3 ,Out_PP,PU);
#define PC4_OUT   GPIOC_Init(4 ,Out_PP,PU);
#define PC5_OUT   GPIOC_Init(5 ,Out_PP,PU);
#define PC6_OUT   GPIOC_Init(6 ,Out_PP,PU);
#define PC7_OUT   GPIOC_Init(7 ,Out_PP,PU);
#define PC8_OUT   GPIOC_Init(8 ,Out_PP,PU);
#define PC9_OUT   GPIOC_Init(9 ,Out_PP,PU);
#define PC10_OUT  GPIOC_Init(10,Out_PP,PU);
#define PC11_OUT  GPIOC_Init(11,Out_PP,PU);
#define PC12_OUT  GPIOC_Init(12,Out_PP,PU);
#define PC13_OUT  GPIOC_Init(13,Out_PP,PU);
#define PC14_OUT  GPIOC_Init(14,Out_PP,PU);
#define PC15_OUT  GPIOC_Init(15,Out_PP,PU);

#define PD0_OUT   GPIOD_Init(0 ,Out_PP,PU);
#define PD1_OUT   GPIOD_Init(1 ,Out_PP,PU);
#define PD2_OUT   GPIOD_Init(2 ,Out_PP,PU);
#define PD3_OUT   GPIOD_Init(3 ,Out_PP,PU);
#define PD4_OUT   GPIOD_Init(4 ,Out_PP,PU);
#define PD5_OUT   GPIOD_Init(5 ,Out_PP,PU);
#define PD6_OUT   GPIOD_Init(6 ,Out_PP,PU);
#define PD7_OUT   GPIOD_Init(7 ,Out_PP,PU);
#define PD8_OUT   GPIOD_Init(8 ,Out_PP,PU);
#define PD9_OUT   GPIOD_Init(9 ,Out_PP,PU);
#define PD10_OUT  GPIOD_Init(10,Out_PP,PU);
#define PD11_OUT  GPIOD_Init(11,Out_PP,PU);
#define PD12_OUT  GPIOD_Init(12,Out_PP,PU);
#define PD13_OUT  GPIOD_Init(13,Out_PP,PU);
#define PD14_OUT  GPIOD_Init(14,Out_PP,PU);
#define PD15_OUT  GPIOD_Init(15,Out_PP,PU);

#define PE0_OUT   GPIOE_Init(0 ,Out_PP,PU);
#define PE1_OUT   GPIOE_Init(1 ,Out_PP,PU);
#define PE2_OUT   GPIOE_Init(2 ,Out_PP,PU);
#define PE3_OUT   GPIOE_Init(3 ,Out_PP,PU);
#define PE4_OUT   GPIOE_Init(4 ,Out_PP,PU);
#define PE5_OUT   GPIOE_Init(5 ,Out_PP,PU);
#define PE6_OUT   GPIOE_Init(6 ,Out_PP,PU);
#define PE7_OUT   GPIOE_Init(7 ,Out_PP,PU);
#define PE8_OUT   GPIOE_Init(8 ,Out_PP,PU);
#define PE9_OUT   GPIOE_Init(9 ,Out_PP,PU);
#define PE10_OUT  GPIOE_Init(10,Out_PP,PU);
#define PE11_OUT  GPIOE_Init(11,Out_PP,PU);
#define PE12_OUT  GPIOE_Init(12,Out_PP,PU);
#define PE13_OUT  GPIOE_Init(13,Out_PP,PU);
#define PE14_OUT  GPIOE_Init(14,Out_PP,PU);
#define PE15_OUT  GPIOE_Init(15,Out_PP,PU);

#define PF0_OUT   GPIOF_Init(0 ,Out_PP,PU);
#define PF1_OUT   GPIOF_Init(1 ,Out_PP,PU);
#define PF2_OUT   GPIOF_Init(2 ,Out_PP,PU);
#define PF3_OUT   GPIOF_Init(3 ,Out_PP,PU);
#define PF4_OUT   GPIOF_Init(4 ,Out_PP,PU);
#define PF5_OUT   GPIOF_Init(5 ,Out_PP,PU);
#define PF6_OUT   GPIOF_Init(6 ,Out_PP,PU);
#define PF7_OUT   GPIOF_Init(7 ,Out_PP,PU);
#define PF8_OUT   GPIOF_Init(8 ,Out_PP,PU);
#define PF9_OUT   GPIOF_Init(9 ,Out_PP,PU);
#define PF10_OUT  GPIOF_Init(10,Out_PP,PU);
#define PF11_OUT  GPIOF_Init(11,Out_PP,PU);
#define PF12_OUT  GPIOF_Init(12,Out_PP,PU);
#define PF13_OUT  GPIOF_Init(13,Out_PP,PU);
#define PF14_OUT  GPIOF_Init(14,Out_PP,PU);
#define PF15_OUT  GPIOF_Init(15,Out_PP,PU);

#define PG0_OUT   GPIOG_Init(0 ,Out_PP,PU);
#define PG1_OUT   GPIOG_Init(1 ,Out_PP,PU);
#define PG2_OUT   GPIOG_Init(2 ,Out_PP,PU);
#define PG3_OUT   GPIOG_Init(3 ,Out_PP,PU);
#define PG4_OUT   GPIOG_Init(4 ,Out_PP,PU);
#define PG5_OUT   GPIOG_Init(5 ,Out_PP,PU);
#define PG6_OUT   GPIOG_Init(6 ,Out_PP,PU);
#define PG7_OUT   GPIOG_Init(7 ,Out_PP,PU);
#define PG8_OUT   GPIOG_Init(8 ,Out_PP,PU);
#define PG9_OUT   GPIOG_Init(9 ,Out_PP,PU);
#define PG10_OUT  GPIOG_Init(10,Out_PP,PU);
#define PG11_OUT  GPIOG_Init(11,Out_PP,PU);
#define PG12_OUT  GPIOG_Init(12,Out_PP,PU);
#define PG13_OUT  GPIOG_Init(13,Out_PP,PU);
#define PG14_OUT  GPIOG_Init(14,Out_PP,PU);
#define PG15_OUT  GPIOG_Init(15,Out_PP,PU);

#define PA0_In   GPIOA_Init(0 ,IPU,PU);
#define PA1_In   GPIOA_Init(1 ,IPU,PU);
#define PA2_In   GPIOA_Init(2 ,IPU,PU);
#define PA3_In   GPIOA_Init(3 ,IPU,PU);
#define PA4_In   GPIOA_Init(4 ,IPU,PU);
#define PA5_In   GPIOA_Init(5 ,IPU,PU);
#define PA6_In   GPIOA_Init(6 ,IPU,PU);
#define PA7_In   GPIOA_Init(7 ,IPU,PU);
#define PA8_In   GPIOA_Init(8 ,IPU,PU);
#define PA9_In   GPIOA_Init(9 ,IPU,PU);
#define PA10_In  GPIOA_Init(10,IPU,PU);
#define PA11_In  GPIOA_Init(11,IPU,PU);
#define PA12_In  GPIOA_Init(12,IPU,PU);
#define PA13_In  RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);GPIOA_Init(13,IPU,PU);
#define PA14_In  RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);GPIOA_Init(14,IPU,PU);
#define PA15_In  RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);GPIOA_Init(15,IPU,PU);

#define PB0_In   GPIOB_Init(0 ,IPU,PU);
#define PB1_In   GPIOB_Init(1 ,IPU,PU);
#define PB2_In   GPIOB_Init(2 ,IPU,PU);
#define PB3_In   RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);GPIOB_Init(3 ,IPU,PU);
#define PB4_In   RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);GPIOB_Init(4 ,IPU,PU);
#define PB5_In   GPIOB_Init(5 ,IPU,PU);
#define PB6_In   GPIOB_Init(6 ,IPU,PU);
#define PB7_In   GPIOB_Init(7 ,IPU,PU);
#define PB8_In   GPIOB_Init(8 ,IPU,PU);
#define PB9_In   GPIOB_Init(9 ,IPU,PU);
#define PB10_In  GPIOB_Init(10,IPU,PU);
#define PB11_In  GPIOB_Init(11,IPU,PU);
#define PB12_In  GPIOB_Init(12,IPU,PU);
#define PB13_In  GPIOB_Init(13,IPU,PU);
#define PB14_In  GPIOB_Init(14,IPU,PU);
#define PB15_In  GPIOB_Init(15,IPU,PU);

#define PC0_In   GPIOC_Init(0 ,IPU,PU);
#define PC1_In   GPIOC_Init(1 ,IPU,PU);
#define PC2_In   GPIOC_Init(2 ,IPU,PU);
#define PC3_In   GPIOC_Init(3 ,IPU,PU);
#define PC4_In   GPIOC_Init(4 ,IPU,PU);
#define PC5_In   GPIOC_Init(5 ,IPU,PU);
#define PC6_In   GPIOC_Init(6 ,IPU,PU);
#define PC7_In   GPIOC_Init(7 ,IPU,PU);
#define PC8_In   GPIOC_Init(8 ,IPU,PU);
#define PC9_In   GPIOC_Init(9 ,IPU,PU);
#define PC10_In  GPIOC_Init(10,IPU,PU);
#define PC11_In  GPIOC_Init(11,IPU,PU);
#define PC12_In  GPIOC_Init(12,IPU,PU);
#define PC13_In  GPIOC_Init(13,IPU,PU);
#define PC14_In  GPIOC_Init(14,IPU,PU);
#define PC15_In  GPIOC_Init(15,IPU,PU);

#define PD0_In   GPIOD_Init(0 ,IPU,PU);
#define PD1_In   GPIOD_Init(1 ,IPU,PU);
#define PD2_In   GPIOD_Init(2 ,IPU,PU);
#define PD3_In   GPIOD_Init(3 ,IPU,PU);
#define PD4_In   GPIOD_Init(4 ,IPU,PU);
#define PD5_In   GPIOD_Init(5 ,IPU,PU);
#define PD6_In   GPIOD_Init(6 ,IPU,PU);
#define PD7_In   GPIOD_Init(7 ,IPU,PU);
#define PD8_In   GPIOD_Init(8 ,IPU,PU);
#define PD9_In   GPIOD_Init(9 ,IPU,PU);
#define PD10_In  GPIOD_Init(10,IPU,PU);
#define PD11_In  GPIOD_Init(11,IPU,PU);
#define PD12_In  GPIOD_Init(12,IPU,PU);
#define PD13_In  GPIOD_Init(13,IPU,PU);
#define PD14_In  GPIOD_Init(14,IPU,PU);
#define PD15_In  GPIOD_Init(15,IPU,PU);

#define PE0_In   GPIOE_Init(0 ,IPU,PU);
#define PE1_In   GPIOE_Init(1 ,IPU,PU);
#define PE2_In   GPIOE_Init(2 ,IPU,PU);
#define PE3_In   GPIOE_Init(3 ,IPU,PU);
#define PE4_In   GPIOE_Init(4 ,IPU,PU);
#define PE5_In   GPIOE_Init(5 ,IPU,PU);
#define PE6_In   GPIOE_Init(6 ,IPU,PU);
#define PE7_In   GPIOE_Init(7 ,IPU,PU);
#define PE8_In   GPIOE_Init(8 ,IPU,PU);
#define PE9_In   GPIOE_Init(9 ,IPU,PU);
#define PE10_In  GPIOE_Init(10,IPU,PU);
#define PE11_In  GPIOE_Init(11,IPU,PU);
#define PE12_In  GPIOE_Init(12,IPU,PU);
#define PE13_In  GPIOE_Init(13,IPU,PU);
#define PE14_In  GPIOE_Init(14,IPU,PU);
#define PE15_In  GPIOE_Init(15,IPU,PU);

#define PF0_In   GPIOF_Init(0 ,IPU,PU);
#define PF1_In   GPIOF_Init(1 ,IPU,PU);
#define PF2_In   GPIOF_Init(2 ,IPU,PU);
#define PF3_In   GPIOF_Init(3 ,IPU,PU);
#define PF4_In   GPIOF_Init(4 ,IPU,PU);
#define PF5_In   GPIOF_Init(5 ,IPU,PU);
#define PF6_In   GPIOF_Init(6 ,IPU,PU);
#define PF7_In   GPIOF_Init(7 ,IPU,PU);
#define PF8_In   GPIOF_Init(8 ,IPU,PU);
#define PF9_In   GPIOF_Init(9 ,IPU,PU);
#define PF10_In  GPIOF_Init(10,IPU,PU);
#define PF11_In  GPIOF_Init(11,IPU,PU);
#define PF12_In  GPIOF_Init(12,IPU,PU);
#define PF13_In  GPIOF_Init(13,IPU,PU);
#define PF14_In  GPIOF_Init(14,IPU,PU);
#define PF15_In  GPIOF_Init(15,IPU,PU);

#define PG0_In   GPIOG_Init(0 ,IPU,PU);
#define PG1_In   GPIOG_Init(1 ,IPU,PU);
#define PG2_In   GPIOG_Init(2 ,IPU,PU);
#define PG3_In   GPIOG_Init(3 ,IPU,PU);
#define PG4_In   GPIOG_Init(4 ,IPU,PU);
#define PG5_In   GPIOG_Init(5 ,IPU,PU);
#define PG6_In   GPIOG_Init(6 ,IPU,PU);
#define PG7_In   GPIOG_Init(7 ,IPU,PU);
#define PG8_In   GPIOG_Init(8 ,IPU,PU);
#define PG9_In   GPIOG_Init(9 ,IPU,PU);
#define PG10_In  GPIOG_Init(10,IPU,PU);
#define PG11_In  GPIOG_Init(11,IPU,PU);
#define PG12_In  GPIOG_Init(12,IPU,PU);
#define PG13_In  GPIOG_Init(13,IPU,PU);
#define PG14_In  GPIOG_Init(14,IPU,PU);
#define PG15_In  GPIOG_Init(15,IPU,PU);


//快速IO
#define Set_A0   GPIOA->BSRR=1<<0 ;
#define Set_A1   GPIOA->BSRR=1<<1 ;
#define Set_A2   GPIOA->BSRR=1<<2;
#define Set_A3   GPIOA->BSRR=1<<3;
#define Set_A4   GPIOA->BSRR=1<<4;
#define Set_A5   GPIOA->BSRR=1<<5;
#define Set_A6   GPIOA->BSRR=1<<6;
#define Set_A7   GPIOA->BSRR=1<<7;
#define Set_A8   GPIOA->BSRR=1<<8;
#define Set_A9   GPIOA->BSRR=1<<9 ;
#define Set_A10  GPIOA->BSRR=1<<10;
#define Set_A11  GPIOA->BSRR=1<<11;
#define Set_A12  GPIOA->BSRR=1<<12;
#define Set_A13  GPIOA->BSRR=1<<13;
#define Set_A14  GPIOA->BSRR=1<<14;
#define Set_A15  GPIOA->BSRR=1<<15;
#define Set_A(n) GPIOA->BSRR=1<<n;

#define Set_B0   GPIOB->BSRR=1<<0 ;
#define Set_B1   GPIOB->BSRR=1<<1;
#define Set_B2   GPIOB->BSRR=1<<2;
#define Set_B3   GPIOB->BSRR=1<<3;
#define Set_B4   GPIOB->BSRR=1<<4;
#define Set_B5   GPIOB->BSRR=1<<5;
#define Set_B6   GPIOB->BSRR=1<<6;
#define Set_B7   GPIOB->BSRR=1<<7;
#define Set_B8   GPIOB->BSRR=1<<8;
#define Set_B9   GPIOB->BSRR=1<<9 ;
#define Set_B10  GPIOB->BSRR=1<<10;
#define Set_B11  GPIOB->BSRR=1<<11;
#define Set_B12  GPIOB->BSRR=1<<12;
#define Set_B13  GPIOB->BSRR=1<<13;
#define Set_B14  GPIOB->BSRR=1<<14;
#define Set_B15  GPIOB->BSRR=1<<15;
#define Set_B(n) GPIOB->BSRR=1<<n;


#define Set_C0   GPIOC->BSRR=1<<0 ;
#define Set_C1   GPIOC->BSRR=1<<1;
#define Set_C2   GPIOC->BSRR=1<<2;
#define Set_C3   GPIOC->BSRR=1<<3;
#define Set_C4   GPIOC->BSRR=1<<4;
#define Set_C5   GPIOC->BSRR=1<<5;
#define Set_C6   GPIOC->BSRR=1<<6;
#define Set_C7   GPIOC->BSRR=1<<7;
#define Set_C8   GPIOC->BSRR=1<<8;
#define Set_C9   GPIOC->BSRR=1<<9 ;
#define Set_C10  GPIOC->BSRR=1<<10;
#define Set_C11  GPIOC->BSRR=1<<11;
#define Set_C12  GPIOC->BSRR=1<<12;
#define Set_C13  GPIOC->BSRR=1<<13;
#define Set_C14  GPIOC->BSRR=1<<14;
#define Set_C15  GPIOC->BSRR=1<<15;
#define Set_C(n) GPIOC->BSRR=1<<n;

#define Set_D0   GPIOD->BSRR=1<<0 ;
#define Set_D1   GPIOD->BSRR=1<<1;
#define Set_D2   GPIOD->BSRR=1<<2;
#define Set_D3   GPIOD->BSRR=1<<3;
#define Set_D4   GPIOD->BSRR=1<<4;
#define Set_D5   GPIOD->BSRR=1<<5;
#define Set_D6   GPIOD->BSRR=1<<6;
#define Set_D7   GPIOD->BSRR=1<<7;
#define Set_D8   GPIOD->BSRR=1<<8;
#define Set_D9   GPIOD->BSRR=1<<9 ;
#define Set_D10  GPIOD->BSRR=1<<10;
#define Set_D11  GPIOD->BSRR=1<<11;
#define Set_D12  GPIOD->BSRR=1<<12;
#define Set_D13  GPIOD->BSRR=1<<13;
#define Set_D14  GPIOD->BSRR=1<<14;
#define Set_D15  GPIOD->BSRR=1<<15;
#define Set_D(n) GPIOD->BSRR=1<<n;

#define Set_E0   GPIOE->BSRR=1<<0 ;
#define Set_E1   GPIOE->BSRR=1<<1;
#define Set_E2   GPIOE->BSRR=1<<2;
#define Set_E3   GPIOE->BSRR=1<<3;
#define Set_E4   GPIOE->BSRR=1<<4;
#define Set_E5   GPIOE->BSRR=1<<5;
#define Set_E6   GPIOE->BSRR=1<<6;
#define Set_E7   GPIOE->BSRR=1<<7;
#define Set_E8   GPIOE->BSRR=1<<8;
#define Set_E9   GPIOE->BSRR=1<<9 ;
#define Set_E10  GPIOE->BSRR=1<<10;
#define Set_E11  GPIOE->BSRR=1<<11;
#define Set_E12  GPIOE->BSRR=1<<12;
#define Set_E13  GPIOE->BSRR=1<<13;
#define Set_E14  GPIOE->BSRR=1<<14;
#define Set_E15  GPIOE->BSRR=1<<15;
#define Set_E(n) GPIOE->BSRR=1<<n;

#define Set_F0   GPIOF->BSRR=1<<0 ;
#define Set_F1   GPIOF->BSRR=1<<1;
#define Set_F2   GPIOF->BSRR=1<<2;
#define Set_F3   GPIOF->BSRR=1<<3;
#define Set_F4   GPIOF->BSRR=1<<4;
#define Set_F5   GPIOF->BSRR=1<<5;
#define Set_F6   GPIOF->BSRR=1<<6;
#define Set_F7   GPIOF->BSRR=1<<7;
#define Set_F8   GPIOF->BSRR=1<<8;
#define Set_F9   GPIOF->BSRR=1<<9 ;
#define Set_F10  GPIOF->BSRR=1<<10;
#define Set_F11  GPIOF->BSRR=1<<11;
#define Set_F12  GPIOF->BSRR=1<<12;
#define Set_F13  GPIOF->BSRR=1<<13;
#define Set_F14  GPIOF->BSRR=1<<14;
#define Set_F15  GPIOF->BSRR=1<<15;
#define Set_F(n) GPIOF->BSRR=1<<n;

#define Set_G0   GPIOG->BSRR=1<<0 ;
#define Set_G1   GPIOG->BSRR=1<<1;
#define Set_G2   GPIOG->BSRR=1<<2;
#define Set_G3   GPIOG->BSRR=1<<3;
#define Set_G4   GPIOG->BSRR=1<<4;
#define Set_G5   GPIOG->BSRR=1<<5;
#define Set_G6   GPIOG->BSRR=1<<6;
#define Set_G7   GPIOG->BSRR=1<<7;
#define Set_G8   GPIOG->BSRR=1<<8;
#define Set_G9   GPIOG->BSRR=1<<9 ;
#define Set_G10  GPIOG->BSRR=1<<10;
#define Set_G11  GPIOG->BSRR=1<<11;
#define Set_G12  GPIOG->BSRR=1<<12;
#define Set_G13  GPIOG->BSRR=1<<13;
#define Set_G14  GPIOG->BSRR=1<<14;
#define Set_G15  GPIOG->BSRR=1<<15;
#define Set_G(n) GPIOG->BSRR=1<<n;

//#define Set_GPIO()

#define Clr_A0   GPIOA->BRR=1<<0;
#define Clr_A1   GPIOA->BRR=1<<1;
#define Clr_A2   GPIOA->BRR=1<<2;
#define Clr_A3   GPIOA->BRR=1<<3;
#define Clr_A4   GPIOA->BRR=1<<4;
#define Clr_A5   GPIOA->BRR=1<<5;
#define Clr_A6   GPIOA->BRR=1<<6;
#define Clr_A7   GPIOA->BRR=1<<7;
#define Clr_A8   GPIOA->BRR=1<<8;
#define Clr_A9   GPIOA->BRR=1<<9 ;
#define Clr_A10  GPIOA->BRR=1<<10;
#define Clr_A11  GPIOA->BRR=1<<11;
#define Clr_A12  GPIOA->BRR=1<<12;
#define Clr_A13  GPIOA->BRR=1<<13;
#define Clr_A14  GPIOA->BRR=1<<14;
#define Clr_A15  GPIOA->BRR=1<<15;
#define Clr_A(n) GPIOA->BRR=1<<n;

#define Clr_B0   GPIOB->BRR=1<<0 ;
#define Clr_B1   GPIOB->BRR=1<<1;
#define Clr_B2   GPIOB->BRR=1<<2;
#define Clr_B3   GPIOB->BRR=1<<3;
#define Clr_B4   GPIOB->BRR=1<<4;
#define Clr_B5   GPIOB->BRR=1<<5;
#define Clr_B6   GPIOB->BRR=1<<6;
#define Clr_B7   GPIOB->BRR=1<<7;
#define Clr_B8   GPIOB->BRR=1<<8;
#define Clr_B9   GPIOB->BRR=1<<9 ;
#define Clr_B10  GPIOB->BRR=1<<10;
#define Clr_B11  GPIOB->BRR=1<<11;
#define Clr_B12  GPIOB->BRR=1<<12;
#define Clr_B13  GPIOB->BRR=1<<13;
#define Clr_B14  GPIOB->BRR=1<<14;
#define Clr_B15  GPIOB->BRR=1<<15;
#define Clr_B(n) GPIOB->BRR=1<<n;


#define Clr_C0   GPIOC->BRR=1<<0 ;
#define Clr_C1   GPIOC->BRR=1<<1;
#define Clr_C2   GPIOC->BRR=1<<2;
#define Clr_C3   GPIOC->BRR=1<<3;
#define Clr_C4   GPIOC->BRR=1<<4;
#define Clr_C5   GPIOC->BRR=1<<5;
#define Clr_C6   GPIOC->BRR=1<<6;
#define Clr_C7   GPIOC->BRR=1<<7;
#define Clr_C8   GPIOC->BRR=1<<8;
#define Clr_C9   GPIOC->BRR=1<<9 ;
#define Clr_C10  GPIOC->BRR=1<<10;
#define Clr_C11  GPIOC->BRR=1<<11;
#define Clr_C12  GPIOC->BRR=1<<12;
#define Clr_C13  GPIOC->BRR=1<<13;
#define Clr_C14  GPIOC->BRR=1<<14;
#define Clr_C15  GPIOC->BRR=1<<15;
#define Clr_C(n) GPIOC->BRR=1<<n;

#define Clr_D0   GPIOD->BRR=1<<0 ;
#define Clr_D1   GPIOD->BRR=1<<1;
#define Clr_D2   GPIOD->BRR=1<<2;
#define Clr_D3   GPIOD->BRR=1<<3;
#define Clr_D4   GPIOD->BRR=1<<4;
#define Clr_D5   GPIOD->BRR=1<<5;
#define Clr_D6   GPIOD->BRR=1<<6;
#define Clr_D7   GPIOD->BRR=1<<7;
#define Clr_D8   GPIOD->BRR=1<<8;
#define Clr_D9   GPIOD->BRR=1<<9 ;
#define Clr_D10  GPIOD->BRR=1<<10;
#define Clr_D11  GPIOD->BRR=1<<11;
#define Clr_D12  GPIOD->BRR=1<<12;
#define Clr_D13  GPIOD->BRR=1<<13;
#define Clr_D14  GPIOD->BRR=1<<14;
#define Clr_D15  GPIOD->BRR=1<<15;
#define Clr_D(n) GPIOD->BRR=1<<n;

#define Clr_E0   GPIOE->BRR=1<<0 ;
#define Clr_E1   GPIOE->BRR=1<<1;
#define Clr_E2   GPIOE->BRR=1<<2;
#define Clr_E3   GPIOE->BRR=1<<3;
#define Clr_E4   GPIOE->BRR=1<<4;
#define Clr_E5   GPIOE->BRR=1<<5;
#define Clr_E6   GPIOE->BRR=1<<6;
#define Clr_E7   GPIOE->BRR=1<<7;
#define Clr_E8   GPIOE->BRR=1<<8;
#define Clr_E9   GPIOE->BRR=1<<9 ;
#define Clr_E10  GPIOE->BRR=1<<10;
#define Clr_E11  GPIOE->BRR=1<<11;
#define Clr_E12  GPIOE->BRR=1<<12;
#define Clr_E13  GPIOE->BRR=1<<13;
#define Clr_E14  GPIOE->BRR=1<<14;
#define Clr_E15  GPIOE->BRR=1<<15;
#define Clr_E(n) GPIOE->BRR=1<<n;

#define Clr_F0   GPIOF->BRR=1<<0 ;
#define Clr_F1   GPIOF->BRR=1<<1;
#define Clr_F2   GPIOF->BRR=1<<2;
#define Clr_F3   GPIOF->BRR=1<<3;
#define Clr_F4   GPIOF->BRR=1<<4;
#define Clr_F5   GPIOF->BRR=1<<5;
#define Clr_F6   GPIOF->BRR=1<<6;
#define Clr_F7   GPIOF->BRR=1<<7;
#define Clr_F8   GPIOF->BRR=1<<8;
#define Clr_F9   GPIOF->BRR=1<<9 ;
#define Clr_F10  GPIOF->BRR=1<<10;
#define Clr_F11  GPIOF->BRR=1<<11;
#define Clr_F12  GPIOF->BRR=1<<12;
#define Clr_F13  GPIOF->BRR=1<<13;
#define Clr_F14  GPIOF->BRR=1<<14;
#define Clr_F15  GPIOF->BRR=1<<15;
#define Clr_F(n) GPIOF->BRR=1<<n;

#define Clr_G0   GPIOG->BRR=1<<0 ;
#define Clr_G1   GPIOG->BRR=1<<1;
#define Clr_G2   GPIOG->BRR=1<<2;
#define Clr_G3   GPIOG->BRR=1<<3;
#define Clr_G4   GPIOG->BRR=1<<4;
#define Clr_G5   GPIOG->BRR=1<<5;
#define Clr_G6   GPIOG->BRR=1<<6;
#define Clr_G7   GPIOG->BRR=1<<7;
#define Clr_G8   GPIOG->BRR=1<<8;
#define Clr_G9   GPIOG->BRR=1<<9 ;
#define Clr_G10  GPIOG->BRR=1<<10;
#define Clr_G11  GPIOG->BRR=1<<11;
#define Clr_G12  GPIOG->BRR=1<<12;
#define Clr_G13  GPIOG->BRR=1<<13;
#define Clr_G14  GPIOG->BRR=1<<14;
#define Clr_G15  GPIOG->BRR=1<<15;
#define Clr_G(n) GPIOG->BRR=1<<n;

////////////////////////////////////////////
//快速 读IO
#define A0       ((GPIOA->IDR&(1<<0))?1:0)
#define A1       ((GPIOA->IDR&(1<<1))?1:0)
#define A2       ((GPIOA->IDR&(1<<2))?1:0)
#define A3       ((GPIOA->IDR&(1<<3))?1:0)
#define A4       ((GPIOA->IDR&(1<<4))?1:0)
#define A5       ((GPIOA->IDR&(1<<5))?1:0)
#define A6       ((GPIOA->IDR&(1<<6))?1:0)
#define A7       ((GPIOA->IDR&(1<<7))?1:0)
#define A8       ((GPIOA->IDR&(1<<8))?1:0)
#define A9       ((GPIOA->IDR&(1<<9))?1:0)
#define A10      ((GPIOA->IDR&(1<<10))?1:0)
#define A11      ((GPIOA->IDR&(1<<11))?1:0)
#define A12      ((GPIOA->IDR&(1<<12))?1:0)
#define A13      ((GPIOA->IDR&(1<<13))?1:0)
#define A14      ((GPIOA->IDR&(1<<14))?1:0)
#define A15      ((GPIOA->IDR&(1<<15))?1:0)
#define A(n)     ((GPIOA->IDR&(1<<n))?1:0)

#define B0       ((GPIOB->IDR&(1<<0))?1:0)
#define B1       ((GPIOB->IDR&(1<<1))?1:0)
#define B2       ((GPIOB->IDR&(1<<2))?1:0)
#define B3       ((GPIOB->IDR&(1<<3))?1:0)
#define B4       ((GPIOB->IDR&(1<<4))?1:0)
#define B5       ((GPIOB->IDR&(1<<5))?1:0)
#define B6       ((GPIOB->IDR&(1<<6))?1:0)
#define B7       ((GPIOB->IDR&(1<<7))?1:0)
#define B8       ((GPIOB->IDR&(1<<8))?1:0)
#define B9       ((GPIOB->IDR&(1<<9))?1:0)
#define B10      ((GPIOB->IDR&(1<<10))?1:0)
#define B11      ((GPIOB->IDR&(1<<11))?1:0)
#define B12      ((GPIOB->IDR&(1<<12))?1:0)
#define B13      ((GPIOB->IDR&(1<<13))?1:0)
#define B14      ((GPIOB->IDR&(1<<14))?1:0)
#define B15      ((GPIOB->IDR&(1<<15))?1:0)
#define B(n)     ((GPIOB->IDR&(1<<n))?1:0)

#define C0       ((GPIOC->IDR&(1<<0))?1:0)
#define C1       ((GPIOC->IDR&(1<<1))?1:0)
#define C2       ((GPIOC->IDR&(1<<2))?1:0)
#define C3       ((GPIOC->IDR&(1<<3))?1:0)
#define C4       ((GPIOC->IDR&(1<<4))?1:0)
#define C5       ((GPIOC->IDR&(1<<5))?1:0)
#define C6       ((GPIOC->IDR&(1<<6))?1:0)
#define C7       ((GPIOC->IDR&(1<<7))?1:0)
#define C8       ((GPIOC->IDR&(1<<8))?1:0)
#define C9       ((GPIOC->IDR&(1<<9))?1:0)
#define C10      ((GPIOC->IDR&(1<<10))?1:0)
#define C11      ((GPIOC->IDR&(1<<11))?1:0)
#define C12      ((GPIOC->IDR&(1<<12))?1:0)
#define C13      ((GPIOC->IDR&(1<<13))?1:0)
#define C14      ((GPIOC->IDR&(1<<14))?1:0)
#define C15      ((GPIOC->IDR&(1<<15))?1:0)
#define C(n)     ((GPIOC->IDR&(1<<n))?1:0)

#define D0       ((GPIOD->IDR&(1<<0))?1:0)
#define D1       ((GPIOD->IDR&(1<<1))?1:0)
#define D2       ((GPIOD->IDR&(1<<2))?1:0)
#define D3       ((GPIOD->IDR&(1<<3))?1:0)
#define D4       ((GPIOD->IDR&(1<<4))?1:0)
#define D5       ((GPIOD->IDR&(1<<5))?1:0)
#define D6       ((GPIOD->IDR&(1<<6))?1:0)
#define D7       ((GPIOD->IDR&(1<<7))?1:0)
#define D8       ((GPIOD->IDR&(1<<8))?1:0)
#define D9       ((GPIOD->IDR&(1<<9))?1:0)
#define D10      ((GPIOD->IDR&(1<<10))?1:0)
#define D11      ((GPIOD->IDR&(1<<11))?1:0)
#define D12      ((GPIOD->IDR&(1<<12))?1:0)
#define D13      ((GPIOD->IDR&(1<<13))?1:0)
#define D14      ((GPIOD->IDR&(1<<14))?1:0)
#define D15      ((GPIOD->IDR&(1<<15))?1:0)
#define D(n)     ((GPIOD->IDR&(1<<n))?1:0)

#define E0       ((GPIOE->IDR&(1<<0))?1:0)
#define E1       ((GPIOE->IDR&(1<<1))?1:0)
#define E2       ((GPIOE->IDR&(1<<2))?1:0)
#define E3       ((GPIOE->IDR&(1<<3))?1:0)
#define E4       ((GPIOE->IDR&(1<<4))?1:0)
#define E5       ((GPIOE->IDR&(1<<5))?1:0)
#define E6       ((GPIOE->IDR&(1<<6))?1:0)
#define E7       ((GPIOE->IDR&(1<<7))?1:0)
#define E8       ((GPIOE->IDR&(1<<8))?1:0)
#define E9       ((GPIOE->IDR&(1<<9))?1:0)
#define E10      ((GPIOE->IDR&(1<<10))?1:0)
#define E11      ((GPIOE->IDR&(1<<11))?1:0)
#define E12      ((GPIOE->IDR&(1<<12))?1:0)
#define E13      ((GPIOE->IDR&(1<<13))?1:0)
#define E14      ((GPIOE->IDR&(1<<14))?1:0)
#define E15      ((GPIOE->IDR&(1<<15))?1:0)
#define E(n)     ((GPIOE->IDR&(1<<n))?1:0)

#define F0       ((GPIOF->IDR&(1<<0))?1:0)
#define F1       ((GPIOF->IDR&(1<<1))?1:0)
#define F2       ((GPIOF->IDR&(1<<2))?1:0)
#define F3       ((GPIOF->IDR&(1<<3))?1:0)
#define F4       ((GPIOF->IDR&(1<<4))?1:0)
#define F5       ((GPIOF->IDR&(1<<5))?1:0)
#define F6       ((GPIOF->IDR&(1<<6))?1:0)
#define F7       ((GPIOF->IDR&(1<<7))?1:0)
#define F8       ((GPIOF->IDR&(1<<8))?1:0)
#define F9       ((GPIOF->IDR&(1<<9))?1:0)
#define F10      ((GPIOF->IDR&(1<<10))?1:0)
#define F11      ((GPIOF->IDR&(1<<11))?1:0)
#define F12      ((GPIOF->IDR&(1<<12))?1:0)
#define F13      ((GPIOF->IDR&(1<<13))?1:0)
#define F14      ((GPIOF->IDR&(1<<14))?1:0)
#define F15      ((GPIOF->IDR&(1<<15))?1:0)

#define G0       ((GPIOG->IDR&(1<<0))?1:0)
#define G1       ((GPIOG->IDR&(1<<1))?1:0)
#define G2       ((GPIOG->IDR&(1<<2))?1:0)
#define G3       ((GPIOG->IDR&(1<<3))?1:0)
#define G4       ((GPIOG->IDR&(1<<4))?1:0)
#define G5       ((GPIOG->IDR&(1<<5))?1:0)
#define G6       ((GPIOG->IDR&(1<<6))?1:0)
#define G7       ((GPIOG->IDR&(1<<7))?1:0)
#define G8       ((GPIOG->IDR&(1<<8))?1:0)
#define G9       ((GPIOG->IDR&(1<<9))?1:0)
#define G10      ((GPIOG->IDR&(1<<10))?1:0)
#define G11      ((GPIOG->IDR&(1<<11))?1:0)
#define G12      ((GPIOG->IDR&(1<<12))?1:0)
#define G13      ((GPIOG->IDR&(1<<13))?1:0)
#define G14      ((GPIOG->IDR&(1<<14))?1:0)
#define G15      ((GPIOG->IDR&(1<<15))?1:0)

#define F(n)     ((GPIOF->IDR&(1<<n))?1:0)
#define G(n)     ((GPIOG->IDR&(1<<n))?1:0)
#ifdef __cplusplus
        }
#endif

#endif
