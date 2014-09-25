#include "key.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////
//按键驱动代码
//////////////////////////////////////////////////////////////////////////////////

//按键初始化函数
void KEY_Init(void) //IO初始化
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //初始化KEY0-->GPIOA.13,KEY1-->GPIOA.15  上拉输入
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能PORTA,PORTE时钟

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5 | GPIO_Pin_2 | GPIO_Pin_3; //PE2~4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
    GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOE2,3,4
}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下
//4，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!
u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1; //按键按松开标志
    if (mode)key_up = 1; //支持连按
    if (key_up && (KEY3 == 0 || KEY1 == 0 || KEY2 == 0))
    {
        delay_ms(10);//去抖动
        key_up = 0;
        if (KEY1 == 0)return 1;
        else if (KEY2 == 0)return 2;
        else if (KEY3 == 0)return 3;
    }
    else if (KEY3 == 1 && KEY1 == 1 && KEY2 == 1)key_up = 1;
    return 0;// 无按键按下
}


#define GPS_KEY0  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define GPS_KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)
#define GPS_KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)
#define GPS_KEY3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)
#define GPS_KEY4  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)


void GPS_KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}
u8 GPS_KEY_Scan(u8 mode)
{
    static u8 key_up = 1;
    if (mode)key_up = 1;
    if (key_up && (GPS_KEY0 == 1 || GPS_KEY1 == 0 || GPS_KEY2 == 0 || GPS_KEY3 == 0 || GPS_KEY4 == 0))
    {
        delay_ms(10);
        key_up = 0;
        if (GPS_KEY0 == 1)return KEY_WKUP;
        else if (GPS_KEY1 == 0)return KEY_UP;
        else if (GPS_KEY3 == 0)return KEY_DOWN;
        else if (GPS_KEY2 == 0)return KEY_SURE;
        else if (GPS_KEY4 == 0)return KEY_RETURN;
    }
    else if (GPS_KEY0 == 0 && GPS_KEY1 == 1 && GPS_KEY2 == 1 && GPS_KEY3 == 1 && GPS_KEY4 == 1)key_up = 1;
    return 0;
}

