#ifndef _BMP085_H_
#define _BMP085_H_
#ifdef __cplusplus
       extern "C" {
#endif
#include <math.h>
#include "G32_I2c.h"
#include "usr_usart.h"
#define BMP085_PRESSURE_45  0x34 //delay_ms(4.5)
#define BMP085_PRESSURE_75  0x74 //delay_ms(7.5)
#define BMP085_PRESSURE_135 0xb4 //delay_ms(13.5)
#define BMP085_PRESSURE_255 0xf4 //delay_ms(25.5)





/*---------------------*
*    ����I2C��ַ����   * 
*----------------------*/
#define BMP085_Addr         0xee            //��ѹ������������ַ

/*---------------------* 
*   BMP085 ��������    * 
*----------------------*/
typedef struct
{
  int32_t temp;
  int32_t pressure;
  float   altitude;
}tg_BMP085_TYPE;

/*---------------------* 
*   BMP085 ����        * 
*----------------------*/
#define P0_PRESSURE 101325.0f    //��׼����pa



extern void BMP085_Init(void);
extern void BMP085_Read(tg_BMP085_TYPE * ptResult);         //��ͨ�����Ĳ����¶���ѹ(������10msʱ����ʱ)
//У׼������
extern void BMP085_Calibrate(void);                         //��ҪУ׼��ѹ��Ӧ�߶���Ϣ
//��ӡ����������
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



