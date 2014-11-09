#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////
/**************************
REMAP     |  0    |  1    |
SPI1_NSS  |  PA4  |  PA15 |
SPI1_SCK  |  PA5  |  PB3  |
SPI1_MISO |  PA6  |  PB4  |
SPI1_MOSI |  PA7  |  PB5  |
**************************|
SPI2_NSS  |  PB12 |       |
SPI2_SCK  |  PB13 |       |
SPI2_MISO |  PB14 |       |
SPI2_MOSI |  PB15 |       |
**************************/
/*********(互联型)********|
SPI3_NSS  |  PA15 |  PA4  |
SPI3_SCK  |  PB3  |  PC10 |
SPI3_MISO |  PB3  |  PC11 |
SPI3_MOSI |  PB3  |  PC12 |
*********(互联型)*********/
//2013/7/24
/*************************/
//////////////////////////////////////////////////////////////////////////////////


void SPI1_Init(void);            //初始化SPIx口
void SPI1_SetSpeed(u8 SpeedSet); //设置SPIx速度
u8   SPI1_ReadWriteByte(u8 TxData);//SPIx总线读写一个字节

void SPI2_Init(void);            //初始化SPIx口
void SPI2_SetSpeed(u8 SpeedSet); //设置SPIx速度
u8   SPI2_ReadWriteByte(u8 TxData);//SPIx总线读写一个字节

#endif

