#ifndef _HMC5883L_H_
#define _HMC5883L_H_
#include <math.h>
#include "usr_usart.h"
#include "G32_I2c.h"
#include "G32_HI2c.h"
/*---------------------*
*    器件I2C地址定义   *
*----------------------*/
#define HMC5883L_Addr       0x3C            //磁场传感器器件地址 默认（出厂） HMC5883LL  7位从机地址为0x3C的写入操作，或0x3D的读出操作。  

/***************************** HMC5883L 宏定义 *********************************/
/*  HMC5883L内部寄存器  */
#define HMC5883L_REGA   0x00
#define HMC5883L_REGB   0x01
#define HMC5883L_MODE   0x02
#define HMC5883L_HX_H   0x03
#define HMC5883L_HX_L   0x04
#define HMC5883L_HZ_H   0x05
#define HMC5883L_HZ_L   0x06
#define HMC5883L_HY_H   0x07
#define HMC5883L_HY_L   0x08
#define HMC5883L_STATE  0x09
#define HMC5883L_IRA    0x0a    //读序列号使用的寄存器
#define HMC5883L_IRB    0x0b
#define HMC5883L_IRC    0x0c


#define ConfigRegA           0x00
#define ConfigRegB           0x01
#define magGain              0x40
#define PositiveBiasConfig   0x11
#define NegativeBiasConfig   0x12
#define NormalOperation      0x10
#define ModeRegister         0x02
#define ContinuousConversion 0x00
#define SingleConversion     0x01

// ConfigRegA valid sample averaging for 5883L
#define SampleAveraging_1    0x00
#define SampleAveraging_2    0x01
#define SampleAveraging_4    0x02
#define SampleAveraging_8    0x03

// ConfigRegA valid data output rates for 5883L
#define DataOutputRate_0_75HZ 0x00
#define DataOutputRate_1_5HZ  0x01
#define DataOutputRate_3HZ    0x02
#define DataOutputRate_7_5HZ  0x03
#define DataOutputRate_15HZ   0x04
#define DataOutputRate_30HZ   0x05
#define DataOutputRate_75HZ   0x06
/*   HMC5883 数据类型   */
typedef struct
{
    int16_t  hx;
    int16_t  hy;
    int16_t  hz;
    uint16_t ha;
} tg_HMC5883L_TYPE;
extern tg_HMC5883L_TYPE hmc5883l;

/*   HMC5883 校正参数   */
// 漂移系数。单位：1单位地磁场强度
#define HMC5883L_OFFSET_X  (-26)
#define HMC5883L_OFFSET_Y  (133)

//比例因子
//#define HMC5883L_GAIN_X     1f
//#define HMC5883L_GAIN_Y   1.04034582
#define HMC5883L_GAIN_Y     0.9450     //实际1.04034582,这里便于整除 

extern void HMC5883L_Init(void);
extern void HMC5883L_Read(tg_HMC5883L_TYPE* ptResult);      //普通完整测量(有至少20ms时序延时)
extern void HMC5883L_Start(void);                           //启动-中断-读取 (启动)有10ms延时
extern void HMC5883L_MultRead(tg_HMC5883L_TYPE* ptResult);  //启动-中断-读取 (读取)
extern void HMC5883L_Calibrate(void);
extern void HMC5883L_Printf(tg_HMC5883L_TYPE* ptResult);

#endif



