#ifndef __ADC_H
#define __ADC_H
#include "sys.h"
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//ADC ����
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////
//#define Adc_Init ADC1_Init
void ADC1_Init(void);
void Adc_Init(void);
u16 Get_Adc(u8 ch);
extern __IO uint16_t ADC_ConvertedValue[];

#endif
