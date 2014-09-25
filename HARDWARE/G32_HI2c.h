#ifndef __G32_HI2c_H
#define __G32_HI2c_H
#include "sys.h"
#include "delay.h"
/*****************************************************
REMAP        |   00    |   01    |   10    |   11    |
*****************************************************|
I2C2_SCL     |   PB10  |                             |
I2C2_SDA     |   PB11  |                             |
*****************************************************|
I2C1_SMBAI   |   PB5                                 |
I2C1_SCL     |   PB6   |  PB8                        |
I2C1_SDA     |   PB7   |  PB9                        |
*****************************************************/
void HI2c1_Init(void);
void HI2c_Write(u8 SlaveAddress, u8 REG_Address, u8 data);
void HI2c_Read(u8 SlaveAddress, u8 REG_Address, u8 data);
void HI2c_ReadBuffer(u8 SlaveAddress, u8 REG_Address, u8 len , u8 *data);


#endif

