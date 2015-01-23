#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

//#define KEY_UP        4
//#define KEY_LEFT  3
//#define KEY_DOWN  2
//#define KEY_RIGHT 1

#define KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)//��ȡ����2 
#define KEY3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)//��ȡ����3(WK_UP) 



#define KEY_WKUP    1
#define KEY_UP      2
#define KEY_DOWN    3
#define KEY_SURE    4
#define KEY_RETURN  5

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);    //����ɨ�躯��
void GPS_KEY_Init(void);
u8 GPS_KEY_Scan(u8 mode);

#endif
