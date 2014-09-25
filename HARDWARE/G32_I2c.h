#ifndef __G32_I2c_H
#define __G32_I2c_H
#include "sys.h"
#include "delay.h"

/*
2013/7/19
*/
#define true 1
#define false 0
#define bool  uint8_t

#define TRUE  0
#define FALSE -1

/*** I2c1 ***/
extern void Soft_I2c1_Init (void);
extern bool Soft_I2c1_Write(u8 addr, u8 reg, u8 data);
extern bool Soft_I2c1_WriteBuffer(u8 addr, u8 reg, u8 len , u8 *data);
extern bool Soft_I2c1_Read(u8 addr, u8 reg);
extern bool Soft_I2c1_ReadBuffer (u8 addr, u8 reg, u8 len , u8 *data);
/*** I2c1 ***/
/*** I2c2 ***/
extern void Soft_I2c2_Init (void);
extern bool Soft_I2c2_Write(u8 addr, u8 reg, u8 data);
extern bool Soft_I2c2_WriteBuffer(u8 addr, u8 reg, u8 len , u8 *data);
extern bool Soft_I2c2_Read(u8 addr, u8 reg);
extern bool Soft_I2c2_ReadBuffer (u8 addr, u8 reg, u8 len , u8 *data);
/*** I2c2 ***/

/***MUP6050 I2c***/
extern int8_t i2cwrite(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);
extern int8_t i2cread (uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data);
/***MUP6050 I2c***/

#endif
