//三维磁阻仪传感器
#include "HMC5883L.h"
#include "stdio.h"


tg_HMC5883L_TYPE hmc5883l;

/*** 硬件 ***/
#define I2c_Write      HI2c_Write
#define I2c_ReadBuffer HI2c_ReadBuffer
#define I2c_Init       HI2c1_Init
/*** 硬件 ***/

/*** 软件 ***/
//#define I2c_Write      Soft_I2c2_Write
//#define I2c_ReadBuffer Soft_I2c2_ReadBuffer
//#define I2c_Init       Soft_I2c2_Init
/*** 软件 ***/
//#define I2c_Write      Soft_I2c1_Write
//#define I2c_ReadBuffer Soft_I2c1_ReadBuffer
//#define I2c_Init       Soft_I2c1_Init


void  HMC5883L_Init(void)
{
		I2c_Init();
    I2c_Write(HMC5883L_Addr, HMC5883L_REGA,0x14);
    I2c_Write(HMC5883L_Addr, HMC5883L_MODE, ContinuousConversion); //连续测量模式
}

/******************************************************************************
/ 函数功能:读取HMC5883的数据
******************************************************************************/
void HMC5883L_Read(tg_HMC5883L_TYPE *ptResult)
{
    uint8_t tmp[6];
    int32_t s32Val;

    I2c_Write(HMC5883L_Addr, HMC5883L_REGA, 0x14); //30Hz
    I2c_Write(HMC5883L_Addr, HMC5883L_MODE, 0x00); //连续测量模式
    delay_ms(10);
    I2c_ReadBuffer(HMC5883L_Addr, HMC5883L_HX_H, 6, tmp);


    ptResult->hx  = (int16_t)((tmp[0] << 8) | tmp[1]) + HMC5883L_OFFSET_X;
    s32Val = (int16_t)((tmp[4] << 8) | tmp[5]) + HMC5883L_OFFSET_Y;
    s32Val = (s32Val * HMC5883L_GAIN_Y) / 10000;
    ptResult->hy  = (int16_t)s32Val;
    ptResult->hz  = (int16_t)((tmp[2] << 8) | tmp[3]);
}

/******************************************************************************
/ 函数功能:启动HMC5883开始转换(适用于启动-中断-读取数据的程序)
/ 使用说明:启动-中断-查询 (启动)
******************************************************************************/
void HMC5883L_Start(void)
{
   I2c_Write(HMC5883L_Addr, HMC5883L_REGA, 0x14);
   I2c_Write(HMC5883L_Addr, HMC5883L_MODE, 0x00);
}

/******************************************************************************
/ 函数功能:读取HMC5883的数据(适用于启动-中断-读取数据的程序)
/ 使用说明:启动-中断-查询 (查询)
******************************************************************************/
void HMC5883L_MultRead(tg_HMC5883L_TYPE *ptResult)
{
    static uint8_t tmp[6];
    int32_t s32Val;

    I2c_ReadBuffer(HMC5883L_Addr, HMC5883L_HX_H, 6, tmp); //多读读出传感器数据
		//delay_ms(5);
        //修正数据(根据x轴修正y轴输出)
        ptResult->hx  = (int16_t)((tmp[0] << 8) | tmp[1]) + HMC5883L_OFFSET_X;
        s32Val = (int16_t)((tmp[4] << 8) | tmp[5]) + HMC5883L_OFFSET_Y;
        s32Val = (s32Val * HMC5883L_GAIN_Y);
        ptResult->hy = (int16_t)s32Val;
        ptResult->hz = (int16_t)((tmp[2] << 8) | tmp[3]);
				
		if (ptResult->hx > 0x7fff)ptResult->hx -= 0xffff;
    if (ptResult->hy > 0x7fff)ptResult->hy -= 0xffff;
//    }
//    else
//        Sys_Printf(DEBUG_USART, "flase");
}

/******************************************************************************
/ 函数功能:HMC5883校准
/ 使用说明:启动-中断-查询 (查询)
******************************************************************************/
void HMC5883L_Calibrate(void)
{
    I2c_Write(HMC5883L_Addr, HMC5883L_REGA, 0x15); //30Hz,启动自检模式
    I2c_Write(HMC5883L_Addr, HMC5883L_MODE, 0x01); //单一测量模式
    delay_ms(10);
    I2c_Write(HMC5883L_Addr, HMC5883L_REGA, 0x14);
    I2c_Write(HMC5883L_Addr, HMC5883L_MODE, 0x00); //回到工作模式
}



/******************************************************************************
/ 函数功能:打印HMC的传感器数据
******************************************************************************/
void HMC5883L_Printf(tg_HMC5883L_TYPE *ptResult)
{
    int16_t x, y;
    float angle;
    __align(8) char temp [160];
		u8 tmp;
    x = ptResult->hx;
    y = ptResult->hy;
    //求出方向
    if (x > 0x7fff)x -= 0xffff;
    if (y > 0x7fff)y -= 0xffff;
    angle = atan2(y, x) * (180 / 3.14159265) + 180; //160us计算时间
    ptResult->ha = (int16_t)(angle * 10); // 得到方向精确到0.1°
//    tmp=sprintf((char *)temp,"HMC5883L:\thx: %4d,\thy: %4d,\thz: %4d,\t%4d\n\r",
//            ptResult->hx, ptResult->hy, ptResult->hz, ptResult->ha/10);
		/********校正输出********/
    tmp=sprintf((char *)temp,"%4d %4d %4d;\r\n",
            ptResult->hx, ptResult->hy,ptResult->hz);
		/********角度输出********/
		tmp+=sprintf((char *)temp+tmp,"%4d ",
            ptResult->ha);
		
    Sys_sPrintf(Printf_USART, (u8*)temp,tmp);
}
