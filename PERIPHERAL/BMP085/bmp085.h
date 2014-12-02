#ifndef _BMP085_H_
#define _BMP085_H_
#ifdef __cplusplus
       extern "C" {
#endif
#include <math.h>
#include "G32_I2c.h"
#include "USART.h"

#define BMP085_PRESSURE_45  0x34 //delay_ms(4.5)
#define BMP085_PRESSURE_75  0x74 //delay_ms(7.5)
#define BMP085_PRESSURE_135 0xb4 //delay_ms(13.5)
#define BMP085_PRESSURE_255 0xf4 //delay_ms(25.5)





/*---------------------*
*    器件I2C地址定义   * 
*----------------------*/
#define BMP085_Addr         0xee            //气压传感器器件地址

/*---------------------* 
*   BMP085 数据类型    * 
*----------------------*/
typedef struct
{
  int32_t temp;
  int32_t pressure;
  float   altitude;
}tg_BMP085_TYPE;

/*---------------------* 
*   BMP085 参数        * 
*----------------------*/
#define P0_PRESSURE 101325.0f    //标准海拔pa



extern void BMP085_Init(void);
extern void BMP085_Read(tg_BMP085_TYPE * ptResult);         //普通完整的测量温度气压(有至少10ms时序延时)
//校准传感器
extern void BMP085_Calibrate(void);                         //主要校准气压对应高度信息
//打印传感器数据
extern void BMP085_Printf(tg_BMP085_TYPE * ptResult);
extern void Calculate(int32_t inUt, int32_t inUp, tg_BMP085_TYPE *ptOut);
extern int32_t bmp085ReadTemp(void);
extern int32_t bmp085ReadPressure(void);


extern void BMP085_temperature_start(void);
extern int32_t BMP085_temperature_get(void);
extern int32_t BMP085_pressure_get(void);
extern void BMP085_pressure_start(void);
extern void BMP085_Calculate(int16_t ut,tg_BMP085_TYPE *ptResult);
#ifdef __cplusplus
}
#endif

#endif



