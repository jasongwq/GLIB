#ifndef _HMC5883L_H_
#define _HMC5883L_H_
#include <math.h>
#include "usr_usart.h"
#include "G32_I2c.h"
#include "G32_HI2c.h"
/*---------------------*
*    ����I2C��ַ����   *
*----------------------*/
#define HMC5883L_Addr       0x3C            //�ų�������������ַ Ĭ�ϣ������� HMC5883LL  7λ�ӻ���ַΪ0x3C��д���������0x3D�Ķ���������  

/***************************** HMC5883L �궨�� *********************************/
/*  HMC5883L�ڲ��Ĵ���  */
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
#define HMC5883L_IRA    0x0a    //�����к�ʹ�õļĴ���
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
/*   HMC5883 ��������   */
typedef struct
{
    int16_t  hx;
    int16_t  hy;
    int16_t  hz;
    uint16_t ha;
} tg_HMC5883L_TYPE;
extern tg_HMC5883L_TYPE hmc5883l;

/*   HMC5883 У������   */
// Ư��ϵ������λ��1��λ�شų�ǿ��
#define HMC5883L_OFFSET_X  (-26)
#define HMC5883L_OFFSET_Y  (133)

//��������
//#define HMC5883L_GAIN_X     1f
//#define HMC5883L_GAIN_Y   1.04034582
#define HMC5883L_GAIN_Y     0.9450     //ʵ��1.04034582,����������� 

extern void HMC5883L_Init(void);
extern void HMC5883L_Read(tg_HMC5883L_TYPE* ptResult);      //��ͨ��������(������20msʱ����ʱ)
extern void HMC5883L_Start(void);                           //����-�ж�-��ȡ (����)��10ms��ʱ
extern void HMC5883L_MultRead(tg_HMC5883L_TYPE* ptResult);  //����-�ж�-��ȡ (��ȡ)
extern void HMC5883L_Calibrate(void);
extern void HMC5883L_Printf(tg_HMC5883L_TYPE* ptResult);

#endif



