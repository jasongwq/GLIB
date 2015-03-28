#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

//#define KEY_UP        4
//#define KEY_LEFT  3
//#define KEY_DOWN  2
//#define KEY_RIGHT 1

#define KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)//读取按键2 
#define KEY3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)//读取按键3(WK_UP) 



#define KEY_WKUP    1
#define KEY_UP      2
#define KEY_DOWN    3
#define KEY_SURE    4
#define KEY_RETURN  5

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);    //按键扫描函数
void GPS_KEY_Init(void);
u8 GPS_KEY_Scan(u8 mode);

#endif
