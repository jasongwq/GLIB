#ifndef __SYS_H
#define __SYS_H
#ifdef __cplusplus
       extern "C" {
#endif


#include "stm32f10x.h"
#include "stdint.h"

//0,��֧��ucos
//1,֧��ucos
#define SYSTEM_SUPPORT_UCOS     0       //����ϵͳ�ļ����Ƿ�֧��UCOS
#define DEBUG 0

//λ������,ʵ��51���Ƶ�GPIO���ƹ���
//����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 

//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����

#define BYTE0(dwTemp)       (* (char *)(&(dwTemp)))
#define BYTE1(dwTemp)       (*((char *)(&(dwTemp)) + 1))
#define BYTE2(dwTemp)       (*((char *)(&(dwTemp)) + 2))
#define BYTE3(dwTemp)       (*((char *)(&(dwTemp)) + 3))
#define BYTE4(dwTemp)       (*((char *)(&(dwTemp)) + 4))
#define BYTE5(dwTemp)       (*((char *)(&(dwTemp)) + 5))
#define BYTE6(dwTemp)       (*((char *)(&(dwTemp)) + 6))
#define BYTE7(dwTemp)       (*((char *)(&(dwTemp)) + 7))


#define WORD0(dwTemp)       (* (int16_t *)(&dwTemp))
#define WORD1(dwTemp)       (*((int16_t *)(&dwTemp) + 1))

#define Set_Bit(Bety,n)  ((Bety)|= (1<<(n)))
#define Clr_Bit(Bety,n)  ((Bety)&=!(1<<(n)))
#define Read_Bit(Bety,n) (((Bety)>>(n))&(1))

//#define false FALSE
//#define true TRUE
//#define bool BOOL
//typedef enum{FALSE = -1,TRUE =0}BOOL;
#if DEBUG
#define Dprintf printf
#else
#define Dprintf /\
    /Dprintf
#endif
extern void NVIC_Configuration(void);

#ifdef __cplusplus
        }
#endif
#endif
