//��ά�����Ǵ�����
#include "HMC5883L.h"
#include "stdio.h"


tg_HMC5883L_TYPE hmc5883l;

/*** Ӳ�� ***/
#define I2c_Write      HI2c_Write
#define I2c_ReadBuffer HI2c_ReadBuffer
#define I2c_Init       HI2c1_Init
/*** Ӳ�� ***/

/*** ��� ***/
//#define I2c_Write      Soft_I2c2_Write
//#define I2c_ReadBuffer Soft_I2c2_ReadBuffer
//#define I2c_Init       Soft_I2c2_Init
/*** ��� ***/
//#define I2c_Write      Soft_I2c1_Write
//#define I2c_ReadBuffer Soft_I2c1_ReadBuffer
//#define I2c_Init       Soft_I2c1_Init


void  HMC5883L_Init(void)
{
		I2c_Init();
    I2c_Write(HMC5883L_Addr, HMC5883L_REGA,0x14);
    I2c_Write(HMC5883L_Addr, HMC5883L_MODE, ContinuousConversion); //��������ģʽ
}

/******************************************************************************
/ ��������:��ȡHMC5883������
******************************************************************************/
void HMC5883L_Read(tg_HMC5883L_TYPE *ptResult)
{
    uint8_t tmp[6];
    int32_t s32Val;

    I2c_Write(HMC5883L_Addr, HMC5883L_REGA, 0x14); //30Hz
    I2c_Write(HMC5883L_Addr, HMC5883L_MODE, 0x00); //��������ģʽ
    delay_ms(10);
    I2c_ReadBuffer(HMC5883L_Addr, HMC5883L_HX_H, 6, tmp);


    ptResult->hx  = (int16_t)((tmp[0] << 8) | tmp[1]) + HMC5883L_OFFSET_X;
    s32Val = (int16_t)((tmp[4] << 8) | tmp[5]) + HMC5883L_OFFSET_Y;
    s32Val = (s32Val * HMC5883L_GAIN_Y) / 10000;
    ptResult->hy  = (int16_t)s32Val;
    ptResult->hz  = (int16_t)((tmp[2] << 8) | tmp[3]);
}

/******************************************************************************
/ ��������:����HMC5883��ʼת��(����������-�ж�-��ȡ���ݵĳ���)
/ ʹ��˵��:����-�ж�-��ѯ (����)
******************************************************************************/
void HMC5883L_Start(void)
{
   I2c_Write(HMC5883L_Addr, HMC5883L_REGA, 0x14);
   I2c_Write(HMC5883L_Addr, HMC5883L_MODE, 0x00);
}

/******************************************************************************
/ ��������:��ȡHMC5883������(����������-�ж�-��ȡ���ݵĳ���)
/ ʹ��˵��:����-�ж�-��ѯ (��ѯ)
******************************************************************************/
void HMC5883L_MultRead(tg_HMC5883L_TYPE *ptResult)
{
    static uint8_t tmp[6];
    int32_t s32Val;

    I2c_ReadBuffer(HMC5883L_Addr, HMC5883L_HX_H, 6, tmp); //�����������������
		//delay_ms(5);
        //��������(����x������y�����)
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
/ ��������:HMC5883У׼
/ ʹ��˵��:����-�ж�-��ѯ (��ѯ)
******************************************************************************/
void HMC5883L_Calibrate(void)
{
    I2c_Write(HMC5883L_Addr, HMC5883L_REGA, 0x15); //30Hz,�����Լ�ģʽ
    I2c_Write(HMC5883L_Addr, HMC5883L_MODE, 0x01); //��һ����ģʽ
    delay_ms(10);
    I2c_Write(HMC5883L_Addr, HMC5883L_REGA, 0x14);
    I2c_Write(HMC5883L_Addr, HMC5883L_MODE, 0x00); //�ص�����ģʽ
}



/******************************************************************************
/ ��������:��ӡHMC�Ĵ���������
******************************************************************************/
void HMC5883L_Printf(tg_HMC5883L_TYPE *ptResult)
{
    int16_t x, y;
    float angle;
    __align(8) char temp [160];
		u8 tmp;
    x = ptResult->hx;
    y = ptResult->hy;
    //�������
    if (x > 0x7fff)x -= 0xffff;
    if (y > 0x7fff)y -= 0xffff;
    angle = atan2(y, x) * (180 / 3.14159265) + 180; //160us����ʱ��
    ptResult->ha = (int16_t)(angle * 10); // �õ�����ȷ��0.1��
//    tmp=sprintf((char *)temp,"HMC5883L:\thx: %4d,\thy: %4d,\thz: %4d,\t%4d\n\r",
//            ptResult->hx, ptResult->hy, ptResult->hz, ptResult->ha/10);
		/********У�����********/
    tmp=sprintf((char *)temp,"%4d %4d %4d;\r\n",
            ptResult->hx, ptResult->hy,ptResult->hz);
		/********�Ƕ����********/
		tmp+=sprintf((char *)temp+tmp,"%4d ",
            ptResult->ha);
		
    Sys_sPrintf(Printf_USART, (u8*)temp,tmp);
}
