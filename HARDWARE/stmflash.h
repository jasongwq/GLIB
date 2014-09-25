#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//STM32 FLASH 驱动代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/13
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
/*


//要写入到STM32 FLASH的字符串数组
u8 TEXT_Buffer[]={"STM32 FLASH sEST"};
#define SIZE sizeof(TEXT_Buffer)                    //数组长度
#define FLASH_SAVE_ADDR  0X08035000                 //设置FLASH 保存地址(必须为偶数)
        u8 datatemp[SIZE];
        STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
        STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);


在执行闪存写操作时，任何对闪存的读操作都会锁住总线，在写操作完成后读操作才能正
确地进行；既在进行写或擦除操作时，不能进行代码或数据的读取操作。*/
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
//用户根据自己的需要设置
#define STM32_FLASH_SIZE 256      //所选STM32的FLASH容量大小(单位为K)
#define STM32_FLASH_WREN 1        //使能FLASH写入(0，不是能;1，使能)
//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000     //STM32 FLASH的起始地址
//FLASH解锁键值

u16 STMFLASH_ReadHalfWord(u32 faddr);         //读出半字
void STMFLASH_Write(u32 WriteAddr, u16 *pBuffer, u16 NumToWrite);   //从指定地址开始写入指定长度的数据
void STMFLASH_Read(u32 ReadAddr, u16 *pBuffer, u16 NumToRead);      //从指定地址开始读出指定长度的数据


#endif

















