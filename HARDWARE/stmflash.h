#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//STM32 FLASH ��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/13
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
/*


//Ҫд�뵽STM32 FLASH���ַ�������
u8 TEXT_Buffer[]={"STM32 FLASH sEST"};
#define SIZE sizeof(TEXT_Buffer)                    //���鳤��
#define FLASH_SAVE_ADDR  0X08035000                 //����FLASH �����ַ(����Ϊż��)
        u8 datatemp[SIZE];
        STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
        STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);


��ִ������д����ʱ���κζ�����Ķ�����������ס���ߣ���д������ɺ������������
ȷ�ؽ��У����ڽ���д���������ʱ�����ܽ��д�������ݵĶ�ȡ������*/
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
//�û������Լ�����Ҫ����
#define STM32_FLASH_SIZE 256      //��ѡSTM32��FLASH������С(��λΪK)
#define STM32_FLASH_WREN 1        //ʹ��FLASHд��(0��������;1��ʹ��)
//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH��ʼ��ַ
#define STM32_FLASH_BASE 0x08000000     //STM32 FLASH����ʼ��ַ
//FLASH������ֵ

u16 STMFLASH_ReadHalfWord(u32 faddr);         //��������
void STMFLASH_Write(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite);   //��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(u32 ReadAddr, u16 *pBuffer, u16 NumToRead);      //��ָ����ַ��ʼ����ָ�����ȵ�����


#endif

















