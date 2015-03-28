//��ѹ�ƴ�����


/******************************************************************************
*********************************  Ӧ �� �� �� ********************************
��λ:  1kpa =10hpa
���: UT:0.1��,��304��30.4��
���: UP:pa,��100635��100.635kPa
******************************************************************************/
#include "./bmp085.h"
#include <stdio.h>

/*** ��� ***/
#define I2c_Write      Soft_I2c1_Write
#define I2c_ReadBuffer Soft_I2c1_ReadBuffer
#define I2c_Init       Soft_I2c1_Init
/*** ��� ***/

/****************************** �Զ���������� *******************************/
#define   OSS 0  // BMP085ʹ��
/******************************** �� �� �� �� ********************************/

tg_BMP085_TYPE   bmp085;

//***BMP085ʹ��
short ac1;
short ac2;
short ac3;
unsigned short ac4;
unsigned short ac5;
unsigned short ac6;
short b1;
short b2;
short mb;
short mc;
short md;

float ref_Altitude;

/*---------------------*
*       �ڲ�����       *
*----------------------*/
float BMP085_GetAltitude(int32_t up);


/******************************************************************************
/ ��������:��ʼ��BMP085
******************************************************************************/
void  BMP085_Init(void)
{
    uint8_t tmp[22];

    I2c_ReadBuffer(BMP085_Addr, 0xAA, 22, tmp); //����22������

    //���ϲ���Ϊint16_t����
    ac1 = (int16_t)( (tmp[0] << 8) + tmp[1]  );
    ac2 = (int16_t)( (tmp[2] << 8) + tmp[3]  );
    ac3 = (int16_t)( (tmp[4] << 8) + tmp[5]  );
    ac4 = (uint16_t)( (tmp[6] << 8) + tmp[7]  );
    ac5 = (uint16_t)( (tmp[8] << 8) + tmp[9]  );
    ac6 = (uint16_t)( (tmp[10] << 8) + tmp[11] );
    b1  = (int16_t)( (tmp[12] << 8) + tmp[13] );
    b2  = (int16_t)( (tmp[14] << 8) + tmp[15] );
    mb  = (int16_t)( (tmp[16] << 8) + tmp[17] );
    mc  = (int16_t)( (tmp[18] << 8) + tmp[19] );
    md  = (int16_t)( (tmp[20] << 8) + tmp[21] );

    ref_Altitude = 0;
    //BMP085_Calibrate();
}

/******************************************************************************
******************************************************************************/
static int32_t bmp085ReadTemp(void)
{
    int16_t  temp_ut;
    I2c_Write(BMP085_Addr, 0xF4, 0x2E);
    delay_ms(5); // max time is 4.5ms
    uint8_t tmp[2];
    I2c_ReadBuffer(BMP085_Addr, 0xF6, 2, tmp); //����2������
    temp_ut = (int16_t)( (tmp[0] << 8) + tmp[1]  );
    return (int32_t) temp_ut ;
}



/******************************************************************************
******************************************************************************/
static int32_t bmp085ReadPressure(void)
{
    int32_t pressure = 0;
    I2c_Write(BMP085_Addr, 0xF4, 0x34);
    delay_ms(5); // max time is 4.5ms
    uint8_t tmp[2];
    I2c_ReadBuffer(BMP085_Addr, 0xF6, 2, tmp); //����2������
    pressure = (int16_t)( (tmp[0] << 8) + tmp[1]  );
    pressure &= 0x0000FFFF; //����ȥ�� ԭ��δ֪
    return pressure;
}

/******************************************************************************
/ ��������:����ut��up����ֵ�����¶��������ѹ,�Լ�����
/ ʹ��˵��:350us����ʱ��
******************************************************************************/
void Calculate(int32_t inUt, int32_t inUp, tg_BMP085_TYPE *ptOut)
{
    int32_t  x1, x2, b5, b6, x3, b3, p;
    uint32_t b4, b7;
    float a;

    //**************** ���¶�
    x1 = ((int32_t)inUt - ac6) * ac5 >> 15;
    x2 = ((int32_t) mc << 11) / (x1 + md);
    b5 = x1 + x2;
    ptOut->temp = (b5 + 8) >> 4;

    //**************** ����ѹ
    b6 = b5 - 4000;
    x1 = (b2 * (b6 * b6 >> 12)) >> 11;
    x2 = ac2 * b6 >> 11;
    x3 = x1 + x2;
    b3 = (((int32_t)ac1 * 4 + x3) + 2) / 4;
    x1 = ac3 * b6 >> 13;
    x2 = (b1 * (b6 * b6 >> 12)) >> 16;
    x3 = ((x1 + x2) + 2) >> 2;
    b4 = (ac4 * (uint32_t) (x3 + 32768)) >> 15;
    b7 = ((uint32_t) inUp - b3) * (50000 >> OSS);
    if ( b7 < 0x80000000)p = (b7 * 2) / b4 ;
    else p = (b7 / b4) * 2;
    x1 = (p >> 8) * (p >> 8);
    x1 = (x1 * 3038) >> 16;
    x2 = (-7357 * p) >> 16;
    ptOut->pressure = p + ((x1 + x2 + 3791) >> 4);

    //�㺣�θ߶�
    a = (float)ptOut->pressure;
    a = pow(a / P0_PRESSURE, 0.190294957f);
    a = (1.0 - a) * 44330.0f;
    ptOut->altitude = a - ref_Altitude;
}

/******************************************************************************
/ ��������:��ȡBMP085���������ݶ�ָ��������
******************************************************************************/
void BMP085_Read(tg_BMP085_TYPE *ptResult)
{
    int32_t  ut, up;
    ut = bmp085ReadTemp();      // ��ȡ�¶�
    up = bmp085ReadPressure();  // ��ȡѹǿ
    Calculate(ut, up, ptResult); //����������ṹ��
}


/******************************************************************************
/ ��������:��ӡBMP085�Ĵ���������
******************************************************************************/
void  BMP085_Printf(tg_BMP085_TYPE *ptResult)
{
    char tmp[256];
    u8 num;
    num = sprintf(tmp, "BMP085:  \tt= %d.%d`C\t", ptResult->temp / 10, ptResult->temp % 10);
    num += sprintf(tmp + num, "p= %d.%d Kpa\t", ptResult->pressure / 1000, ptResult->pressure % 1000);
    num += sprintf(tmp + num, "h= %.2fm\n\r", ptResult->altitude);
    Sys_sPrintf(Printf_USART, (u8 *)tmp, num);
}

/******************************************************************************
/ ��������:У׼BMP085�ĺ��θ߶�
******************************************************************************/
void BMP085_Calibrate(void)
{
    int32_t up, ut, i;
    tg_BMP085_TYPE tmp_Bmp085;

    up = ut = 0;
    ref_Altitude = 0;               //��������
    for (i = 0; i < 50; i++)
    {
        ut += bmp085ReadTemp();     // ��ȡ�¶�
        up += bmp085ReadPressure(); // ��ȡѹǿ
    }
    ut /= 50;                        // ȡ�¶�ƽ��ֵ
    up /= 50;                        // ȡ��ѹƽ��ֵ
    Calculate(ut, up, &tmp_Bmp085);     // �����¶���ѹ�͸߶�
    ref_Altitude = tmp_Bmp085.altitude; //�õ�����ֵ
}



void BMP085_temperature_start(void)
{
    I2c_Write(BMP085_Addr, 0xF4, 0x2E);
    // delay_ms(5); // max time is 4.5ms
}
int16_t BMP085_temperature_get(void)
{
    int16_t  temp_ut;
    uint8_t tmp[2];
    I2c_ReadBuffer(BMP085_Addr, 0xF6, 2, tmp); //����2������
    temp_ut = (int16_t)( (tmp[0] << 8) + tmp[1]  );
    return temp_ut;
}
int16_t BMP085_pressure_get(void)
{
	  int32_t temp_up = 0;
    uint8_t tmp[2];
    I2c_ReadBuffer(BMP085_Addr, 0xF6, 2, tmp); //����2������
    temp_up = (int16_t)( (tmp[0] << 8) + tmp[1]  );
    return temp_up;
}
void BMP085_pressure_start(void)
{
    I2c_Write(BMP085_Addr, 0xF4, BMP085_PRESSURE_255);
}
void BMP085_Calculate(int16_t ut, tg_BMP085_TYPE *ptResult)
{
    int32_t pressure = 0;
    uint8_t tmp[2];
    I2c_ReadBuffer(BMP085_Addr, 0xF6, 2, tmp); //����2������
    pressure = (int16_t)( (tmp[0] << 8) + tmp[1]  );
#define FILTERNUM 5
    static int16_t temp_pressure[FILTERNUM];
    static char filter_cnt;
    int32_t temp = 0;
    temp_pressure[filter_cnt] = pressure;
    for (int i = 0; i < FILTERNUM; i++)
    {
        temp += temp_pressure[i];
    }
    pressure = temp / FILTERNUM;
    filter_cnt++;
    if (filter_cnt >= FILTERNUM)filter_cnt = 0;
    pressure &= 0x0000FFFF; //����ȥ�� ԭ��δ֪
    Calculate((int32_t)ut, (int32_t)pressure, ptResult); //����������ṹ��
}


