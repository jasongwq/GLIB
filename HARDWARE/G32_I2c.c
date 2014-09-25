#include "G32_I2c.h"
#include "G32_I2c_Config.h"
/*****************************************************
REMAP        |   00    |   01    |   10    |   11    |
*****************************************************|
Soft_I2cx2_SCL     |   PB10  |                       |
Soft_I2cx2_SDA     |   PB11  |                       |
*****************************************************|
Soft_I2cx1_SMBAI   |   PB5                           |
Soft_I2cx1_SCL     |   PB6   |  PB8                  |
Soft_I2cx1_SDA     |   PB7   |  PB9                  |
*****************************************************/
/*
软件模拟I2cx
2014/7/8
2013/7/19
*/
#define Soft_I2cx_SCL_H Soft_I2cx_SCL_GPIO->BSRR = Soft_I2cx_SCL_PIN//GPIO_SetBits(Soft_I2cx_SCL_GPIO,Soft_I2cx_SCL_PIN)
#define Soft_I2cx_SCL_L Soft_I2cx_SCL_GPIO->BRR = Soft_I2cx_SCL_PIN//GPIO_ResetBits(Soft_I2cx_SCL_GPIO,Soft_I2cx_SCL_PIN)

#define Soft_I2cx_SDA_H Soft_I2cx_SDA_GPIO->BSRR = Soft_I2cx_SDA_PIN//GPIO_SetBits(Soft_I2cx_SDA_GPIO,Soft_I2cx_SDA_PIN)
#define Soft_I2cx_SDA_L Soft_I2cx_SDA_GPIO->BRR = Soft_I2cx_SDA_PIN//GPIO_ResetBits(Soft_I2cx_SDA_GPIO,Soft_I2cx_SDA_PIN)

#define Soft_I2cx_SCL_Read ((Soft_I2cx_SCL_GPIO->IDR&(Soft_I2cx_SCL_PIN))?1:0)//GPIO_ReadInputDataBit(Soft_I2cx_SCL_GPIO,Soft_I2cx_SCL_PIN)
#define Soft_I2cx_SDA_Read ((Soft_I2cx_SDA_GPIO->IDR&(Soft_I2cx_SDA_PIN))?1:0)//GPIO_ReadInputDataBit(Soft_I2cx_SDA_GPIO,Soft_I2cx_SDA_PIN)

/*****************************************************/
#define RCC_Soft_I2cx_SCL RCC_Soft_I2c1_SCL
#define Soft_I2cx_SCL_GPIO    Soft_I2c1_SCL_GPIO
#define Soft_I2cx_SCL_PIN     Soft_I2c1_SCL_PIN
#define RCC_Soft_I2cx_SDA RCC_Soft_I2c1_SDA
#define Soft_I2cx_SDA_GPIO    Soft_I2c1_SDA_GPIO
#define Soft_I2cx_SDA_PIN     Soft_I2c1_SDA_PIN
#define Soft_I2cx_Init        Soft_I2c1_Init
#define Soft_I2cx_Delay       Soft_I2c1_Delay
#define Soft_I2cx_Start       Soft_I2c1_Start
#define Soft_I2cx_Stop        Soft_I2c1_Stop
#define Soft_I2cx_Ack         Soft_I2c1_Ack
#define Soft_I2cx_NoAck       Soft_I2c1_NoAck
#define Soft_I2cx_WaitAck     Soft_I2c1_WaitAck
#define Soft_I2cx_SendBety    Soft_I2c1_SendBety
#define Soft_I2cx_ReceiveBety Soft_I2c1_ReceiveBety
#define Soft_I2cx_Write       Soft_I2c1_Write
#define Soft_I2cx_WriteBuffer Soft_I2c1_WriteBuffer
#define Soft_I2cx_Read        Soft_I2c1_Read
#define Soft_I2cx_ReadBuffer  Soft_I2c1_ReadBuffer
/*****************************************************/
void Soft_I2cx_Init(void)
{
    GPIO_InitTypeDef Soft_I2cx_GPIO;
    RCC_APB2PeriphClockCmd(RCC_Soft_I2cx_SCL, ENABLE); //使能Px端口时钟
    Soft_I2cx_GPIO.GPIO_Pin = Soft_I2cx_SCL_PIN;
    Soft_I2cx_GPIO.GPIO_Speed = GPIO_Speed_10MHz;
    Soft_I2cx_GPIO.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(Soft_I2cx_SCL_GPIO, &Soft_I2cx_GPIO);
    RCC_APB2PeriphClockCmd(RCC_Soft_I2cx_SDA, ENABLE); //使能Px端口时钟
    Soft_I2cx_GPIO.GPIO_Pin = Soft_I2cx_SDA_PIN;
    Soft_I2cx_GPIO.GPIO_Speed = GPIO_Speed_2MHz;
    Soft_I2cx_GPIO.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(Soft_I2cx_SDA_GPIO, &Soft_I2cx_GPIO);
}

static void Soft_I2cx_Delay(void)
{
    volatile s8 i = 7;
    while (i)
        i--;
}
static bool Soft_I2cx_Start(void)
{
    Soft_I2cx_SDA_H;
    Soft_I2cx_SCL_H;
    Soft_I2cx_Delay();
    if (!Soft_I2cx_SDA_Read)
        return false;
    Soft_I2cx_SDA_L;
    Soft_I2cx_Delay();
    if (Soft_I2cx_SDA_Read)
        return false;
    Soft_I2cx_SDA_L;
    Soft_I2cx_Delay();
    return true;
}
static void Soft_I2cx_Stop(void)
{
    Soft_I2cx_SCL_L;
    Soft_I2cx_Delay();
    Soft_I2cx_SDA_L;
    Soft_I2cx_Delay();
    Soft_I2cx_SCL_H;
    Soft_I2cx_Delay();
    Soft_I2cx_SDA_H;
    Soft_I2cx_Delay();
}
static void Soft_I2cx_Ack(void)
{
    Soft_I2cx_SCL_L;
    Soft_I2cx_Delay();
    Soft_I2cx_SDA_L;
    Soft_I2cx_Delay();
    Soft_I2cx_SCL_H;
    Soft_I2cx_Delay();
    Soft_I2cx_SCL_L;
    Soft_I2cx_Delay();
}
static void Soft_I2cx_NoAck(void)
{
    Soft_I2cx_SCL_L;
    Soft_I2cx_Delay();
    Soft_I2cx_SDA_H;
    Soft_I2cx_Delay();
    Soft_I2cx_SCL_H;
    Soft_I2cx_Delay();
    Soft_I2cx_SCL_L;
    Soft_I2cx_Delay();
}
static bool Soft_I2cx_WaitAck(void)
{
    Soft_I2cx_SCL_L;
    Soft_I2cx_Delay();
    Soft_I2cx_SDA_H;
    Soft_I2cx_Delay();
    Soft_I2cx_SCL_H;
    Soft_I2cx_Delay();
    if (Soft_I2cx_SDA_Read)
    {
        Soft_I2cx_SCL_L;
        Soft_I2cx_Delay();
        return false;
    }
    Soft_I2cx_SCL_L;
    Soft_I2cx_Delay();
    return true;
}
static void Soft_I2cx_SendBety(u8 byte)
{
    u8 i = 8;
    while (i--)
    {
        Soft_I2cx_SCL_L;
        Soft_I2cx_Delay();
        if (byte & 0x80)
            Soft_I2cx_SDA_H;
        else
            Soft_I2cx_SDA_L;
        byte <<= 1;
        Soft_I2cx_Delay();
        Soft_I2cx_SCL_H;
        Soft_I2cx_Delay();
    }
    Soft_I2cx_SCL_L;
}
static u8 Soft_I2cx_ReceiveBety(void)
{
    u8 i = 8;
    u8 byte = 0;
    Soft_I2cx_SDA_H;
    while (i--)
    {
        byte <<= 1;
        Soft_I2cx_SCL_L;
        Soft_I2cx_Delay();
        Soft_I2cx_SCL_H;
        Soft_I2cx_Delay();
        if (Soft_I2cx_SDA_Read)
            byte |= 0x01;
    }
    Soft_I2cx_SCL_L;
    return byte;
}
/******************************************************************************
/ 函数功能:单字节写入
/ 输入参数:
/   @arg SlaveAddress   从器件地址
/   @arg REG_Address    寄存器地址
/   @arg data       欲写入的字节数据
/ 输出参数: 读出的字节数据
/ 使用说明:这时一个完整的单字节读取函数
******************************************************************************/
bool Soft_I2cx_Write(u8 SlaveAddress, u8 REG_Address, u8 data)
{
    if (!Soft_I2cx_Start())
        return false;
    Soft_I2cx_SendBety(SlaveAddress);
    if (!Soft_I2cx_WaitAck())
    {
        Soft_I2cx_Stop();
        return false;
    }
    Soft_I2cx_SendBety(REG_Address);
    Soft_I2cx_WaitAck();
    Soft_I2cx_SendBety(data);
    if (!Soft_I2cx_WaitAck())
    {
        Soft_I2cx_Stop();
        return false;
    }
    Soft_I2cx_Stop();
    return true;
}
bool Soft_I2cx_WriteBuffer(u8 addr, u8 reg, u8 len , u8 *data)
{
    s8 i;
    if (!Soft_I2cx_Start())
        return false;
    Soft_I2cx_SendBety(addr);
    if (!Soft_I2cx_WaitAck())
    {
        Soft_I2cx_Stop();
        return false;
    }
    Soft_I2cx_SendBety(reg);
    Soft_I2cx_WaitAck();
    for (i = 0; i < len; i++)
    {
        Soft_I2cx_SendBety(data[i]);
        if (!Soft_I2cx_WaitAck())
        {
            Soft_I2cx_Stop();
            return false;
        }
    }
    Soft_I2cx_Stop();
    return true;
}
uint8_t Soft_I2cx_Read(u8 addr, u8 reg)
{
    uint8_t REG_data;
    if (!Soft_I2cx_Start())return false;
    Soft_I2cx_SendBety(addr); //Soft_I2cx_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//ÉèÖÃ¸ßÆðÊ¼µØÖ·+Æ÷¼þµØÖ·
    if (!Soft_I2cx_WaitAck())
    {
        Soft_I2cx_Stop();
        return false;
    }
    Soft_I2cx_SendBety(reg);
    Soft_I2cx_WaitAck();
    Soft_I2cx_Start();
    Soft_I2cx_SendBety(addr + 1);
    Soft_I2cx_WaitAck();

    REG_data = Soft_I2cx_ReceiveBety();
    Soft_I2cx_NoAck();
    Soft_I2cx_Stop();
    return REG_data;
}
bool Soft_I2cx_ReadBuffer(u8 addr, u8 reg, u8 len , u8 *data)
{
    if (!Soft_I2cx_Start())
        return false;
    Soft_I2cx_SendBety(addr);
    if (!Soft_I2cx_WaitAck())
    {
        Soft_I2cx_Stop();
        return false;
    }
    Soft_I2cx_SendBety(reg);
    Soft_I2cx_WaitAck();

    if (!Soft_I2cx_Start())return false;
    Soft_I2cx_SendBety(addr + 1);
    if (!Soft_I2cx_WaitAck())
    {
        Soft_I2cx_Stop();
        return false;
    }
    while (len--)
    {
        *data++ = Soft_I2cx_ReceiveBety();
        if (len < 1)
            Soft_I2cx_NoAck();
        else
            Soft_I2cx_Ack();
    }
    Soft_I2cx_Stop();
    return true;
}
/***MUP6050 Soft_I2cx***/
int8_t i2cwrite(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data)
{
    s8 i;
    if (!Soft_I2cx_Start())
        return FALSE;
    Soft_I2cx_SendBety(addr << 1 | 0x00);
    if (!Soft_I2cx_WaitAck())
    {
        Soft_I2cx_Stop();
        return FALSE;
    }
    Soft_I2cx_SendBety(reg);
    Soft_I2cx_WaitAck();
    for (i = 0; i < len; i++)
    {
        Soft_I2cx_SendBety(data[i]);
        if (!Soft_I2cx_WaitAck())
        {
            Soft_I2cx_Stop();
            return FALSE;
        }
    }
    Soft_I2cx_Stop();
    return TRUE;
}
int8_t i2cread(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *data)
{
    if (!Soft_I2cx_Start())
        return FALSE;
    Soft_I2cx_SendBety(addr << 1 | 0x00);
    if (!Soft_I2cx_WaitAck())
    {
        Soft_I2cx_Stop();
        return FALSE;
    }
    Soft_I2cx_SendBety(reg);
    Soft_I2cx_WaitAck();

    if (!Soft_I2cx_Start())return FALSE;
    Soft_I2cx_SendBety(addr << 1 | 0x01);
    if (!Soft_I2cx_WaitAck())
    {
        Soft_I2cx_Stop();
        return FALSE;
    }
    while (len)
    {
        *data = Soft_I2cx_ReceiveBety();
        if (len == 1)
            Soft_I2cx_NoAck();
        else
            Soft_I2cx_Ack();
        data++;
        len--;
    }
    Soft_I2cx_Stop();
    return TRUE;
}
/***MUP6050 Soft_I2cx***/
/*****************************************************/
#undef RCC_Soft_I2cx_SCL
#undef Soft_I2cx_SCL_GPIO
#undef Soft_I2cx_SCL_PIN
#undef RCC_Soft_I2cx_SDA
#undef Soft_I2cx_SDA_GPIO
#undef Soft_I2cx_SDA_PIN
#undef Soft_I2cx_Init
#undef Soft_I2cx_Delay
#undef Soft_I2cx_Start
#undef Soft_I2cx_Stop
#undef Soft_I2cx_Ack
#undef Soft_I2cx_NoAck
#undef Soft_I2cx_WaitAck
#undef Soft_I2cx_SendBety
#undef Soft_I2cx_ReceiveBety
#undef Soft_I2cx_Write
#undef Soft_I2cx_WriteBuffer
#undef Soft_I2cx_Read
#undef Soft_I2cx_ReadBuffer
/*****************************************************/
/*****************************************************/
#define RCC_Soft_I2cx_SCL RCC_Soft_I2c2_SCL
#define Soft_I2cx_SCL_GPIO    Soft_I2c2_SCL_GPIO
#define Soft_I2cx_SCL_PIN     Soft_I2c2_SCL_PIN
#define RCC_Soft_I2cx_SDA RCC_Soft_I2c2_SDA
#define Soft_I2cx_SDA_GPIO    Soft_I2c2_SDA_GPIO
#define Soft_I2cx_SDA_PIN     Soft_I2c2_SDA_PIN
#define Soft_I2cx_Init        Soft_I2c2_Init
#define Soft_I2cx_Delay       Soft_I2c2_Delay
#define Soft_I2cx_Start       Soft_I2c2_Start
#define Soft_I2cx_Stop        Soft_I2c2_Stop
#define Soft_I2cx_Ack         Soft_I2c2_Ack
#define Soft_I2cx_NoAck       Soft_I2c2_NoAck
#define Soft_I2cx_WaitAck     Soft_I2c2_WaitAck
#define Soft_I2cx_SendBety    Soft_I2c2_SendBety
#define Soft_I2cx_ReceiveBety Soft_I2c2_ReceiveBety
#define Soft_I2cx_Write       Soft_I2c2_Write
#define Soft_I2cx_WriteBuffer Soft_I2c2_WriteBuffer
#define Soft_I2cx_Read        Soft_I2c2_Read
#define Soft_I2cx_ReadBuffer  Soft_I2c2_ReadBuffer
/*****************************************************/
void Soft_I2cx_Init(void)
{
    GPIO_InitTypeDef Soft_I2cx_GPIO;
    RCC_APB2PeriphClockCmd(RCC_Soft_I2cx_SCL, ENABLE); //使能Px端口时钟
    Soft_I2cx_GPIO.GPIO_Pin = Soft_I2cx_SCL_PIN;
    Soft_I2cx_GPIO.GPIO_Speed = GPIO_Speed_10MHz;
    Soft_I2cx_GPIO.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(Soft_I2cx_SCL_GPIO, &Soft_I2cx_GPIO);
    RCC_APB2PeriphClockCmd(RCC_Soft_I2cx_SDA, ENABLE); //使能Px端口时钟
    Soft_I2cx_GPIO.GPIO_Pin = Soft_I2cx_SDA_PIN;
    Soft_I2cx_GPIO.GPIO_Speed = GPIO_Speed_2MHz;
    Soft_I2cx_GPIO.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(Soft_I2cx_SDA_GPIO, &Soft_I2cx_GPIO);
}

static void Soft_I2cx_Delay(void)
{
    volatile s8 i = 7;
    while (i)
        i--;
}
static bool Soft_I2cx_Start(void)
{
    Soft_I2cx_SDA_H;
    Soft_I2cx_SCL_H;
    Soft_I2cx_Delay();
    if (!Soft_I2cx_SDA_Read)
        return false;
    Soft_I2cx_SDA_L;
    Soft_I2cx_Delay();
    if (Soft_I2cx_SDA_Read)
        return false;
    Soft_I2cx_SDA_L;
    Soft_I2cx_Delay();
    return true;
}
static void Soft_I2cx_Stop(void)
{
    Soft_I2cx_SCL_L;
    Soft_I2cx_Delay();
    Soft_I2cx_SDA_L;
    Soft_I2cx_Delay();
    Soft_I2cx_SCL_H;
    Soft_I2cx_Delay();
    Soft_I2cx_SDA_H;
    Soft_I2cx_Delay();
}
static void Soft_I2cx_Ack(void)
{
    Soft_I2cx_SCL_L;
    Soft_I2cx_Delay();
    Soft_I2cx_SDA_L;
    Soft_I2cx_Delay();
    Soft_I2cx_SCL_H;
    Soft_I2cx_Delay();
    Soft_I2cx_SCL_L;
    Soft_I2cx_Delay();
}
static void Soft_I2cx_NoAck(void)
{
    Soft_I2cx_SCL_L;
    Soft_I2cx_Delay();
    Soft_I2cx_SDA_H;
    Soft_I2cx_Delay();
    Soft_I2cx_SCL_H;
    Soft_I2cx_Delay();
    Soft_I2cx_SCL_L;
    Soft_I2cx_Delay();
}
static bool Soft_I2cx_WaitAck(void)
{
    Soft_I2cx_SCL_L;
    Soft_I2cx_Delay();
    Soft_I2cx_SDA_H;
    Soft_I2cx_Delay();
    Soft_I2cx_SCL_H;
    Soft_I2cx_Delay();
    if (Soft_I2cx_SDA_Read)
    {
        Soft_I2cx_SCL_L;
        Soft_I2cx_Delay();
        return false;
    }
    Soft_I2cx_SCL_L;
    Soft_I2cx_Delay();
    return true;
}
static void Soft_I2cx_SendBety(u8 byte)
{
    u8 i = 8;
    while (i--)
    {
        Soft_I2cx_SCL_L;
        Soft_I2cx_Delay();
        if (byte & 0x80)
            Soft_I2cx_SDA_H;
        else
            Soft_I2cx_SDA_L;
        byte <<= 1;
        Soft_I2cx_Delay();
        Soft_I2cx_SCL_H;
        Soft_I2cx_Delay();
    }
    Soft_I2cx_SCL_L;
}
static u8 Soft_I2cx_ReceiveBety(void)
{
    u8 i = 8;
    u8 byte = 0;
    Soft_I2cx_SDA_H;
    while (i--)
    {
        byte <<= 1;
        Soft_I2cx_SCL_L;
        Soft_I2cx_Delay();
        Soft_I2cx_SCL_H;
        Soft_I2cx_Delay();
        if (Soft_I2cx_SDA_Read)
            byte |= 0x01;
    }
    Soft_I2cx_SCL_L;
    return byte;
}
/******************************************************************************
/ 函数功能:单字节写入
/ 输入参数:
/   @arg SlaveAddress   从器件地址
/   @arg REG_Address    寄存器地址
/   @arg data       欲写入的字节数据
/ 输出参数: 读出的字节数据
/ 使用说明:这时一个完整的单字节读取函数
******************************************************************************/
bool Soft_I2cx_Write(u8 SlaveAddress, u8 REG_Address, u8 data)
{
    if (!Soft_I2cx_Start())
        return false;
    Soft_I2cx_SendBety(SlaveAddress);
    if (!Soft_I2cx_WaitAck())
    {
        Soft_I2cx_Stop();
        return false;
    }
    Soft_I2cx_SendBety(REG_Address);
    Soft_I2cx_WaitAck();
    Soft_I2cx_SendBety(data);
    if (!Soft_I2cx_WaitAck())
    {
        Soft_I2cx_Stop();
        return false;
    }
    Soft_I2cx_Stop();
    return true;
}
bool Soft_I2cx_WriteBuffer(u8 addr, u8 reg, u8 len , u8 *data)
{
    s8 i;
    if (!Soft_I2cx_Start())
        return false;
    Soft_I2cx_SendBety(addr);
    if (!Soft_I2cx_WaitAck())
    {
        Soft_I2cx_Stop();
        return false;
    }
    Soft_I2cx_SendBety(reg);
    Soft_I2cx_WaitAck();
    for (i = 0; i < len; i++)
    {
        Soft_I2cx_SendBety(data[i]);
        if (!Soft_I2cx_WaitAck())
        {
            Soft_I2cx_Stop();
            return false;
        }
    }
    Soft_I2cx_Stop();
    return true;
}
uint8_t Soft_I2cx_Read(u8 addr, u8 reg)
{
    uint8_t REG_data;
    if (!Soft_I2cx_Start())return false;
    Soft_I2cx_SendBety(addr); //Soft_I2cx_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//ÉèÖÃ¸ßÆðÊ¼µØÖ·+Æ÷¼þµØÖ·
    if (!Soft_I2cx_WaitAck())
    {
        Soft_I2cx_Stop();
        return false;
    }
    Soft_I2cx_SendBety(reg);
    Soft_I2cx_WaitAck();
    Soft_I2cx_Start();
    Soft_I2cx_SendBety(addr + 1);
    Soft_I2cx_WaitAck();

    REG_data = Soft_I2cx_ReceiveBety();
    Soft_I2cx_NoAck();
    Soft_I2cx_Stop();
    return REG_data;
}
bool Soft_I2cx_ReadBuffer(u8 addr, u8 reg, u8 len , u8 *data)
{
    if (!Soft_I2cx_Start())
        return false;
    Soft_I2cx_SendBety(addr);
    if (!Soft_I2cx_WaitAck())
    {
        Soft_I2cx_Stop();
        return false;
    }
    Soft_I2cx_SendBety(reg);
    Soft_I2cx_WaitAck();

    if (!Soft_I2cx_Start())return false;
    Soft_I2cx_SendBety(addr + 1);
    if (!Soft_I2cx_WaitAck())
    {
        Soft_I2cx_Stop();
        return false;
    }
    while (len--)
    {
        *data++ = Soft_I2cx_ReceiveBety();
        if (len < 1)
            Soft_I2cx_NoAck();
        else
            Soft_I2cx_Ack();
    }
    Soft_I2cx_Stop();
    return true;
}
/*****************************************************/
#undef RCC_Soft_I2cx_SCL
#undef Soft_I2cx_SCL_GPIO
#undef Soft_I2cx_SCL_PIN
#undef RCC_Soft_I2cx_SDA
#undef Soft_I2cx_SDA_GPIO
#undef Soft_I2cx_SDA_PIN
#undef Soft_I2cx_Init
#undef Soft_I2cx_Delay
#undef Soft_I2cx_Start
#undef Soft_I2cx_Stop
#undef Soft_I2cx_Ack
#undef Soft_I2cx_NoAck
#undef Soft_I2cx_WaitAck
#undef Soft_I2cx_SendBety
#undef Soft_I2cx_ReceiveBety
#undef Soft_I2cx_Write
#undef Soft_I2cx_WriteBuffer
#undef Soft_I2cx_Read
#undef Soft_I2cx_ReadBuffer
/*****************************************************/


