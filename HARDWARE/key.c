#include "key.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////
//������������
//////////////////////////////////////////////////////////////////////////////////

//������ʼ������
void KEY_Init(void) //IO��ʼ��
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //��ʼ��KEY0-->GPIOA.13,KEY1-->GPIOA.15  ��������
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //ʹ��PORTA,PORTEʱ��

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5 | GPIO_Pin_2 | GPIO_Pin_3; //PE2~4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
    GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2����
//4��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1; //�������ɿ���־
    if (mode)key_up = 1; //֧������
    if (key_up && (KEY3 == 0 || KEY1 == 0 || KEY2 == 0))
    {
        delay_ms(10);//ȥ����
        key_up = 0;
        if (KEY1 == 0)return 1;
        else if (KEY2 == 0)return 2;
        else if (KEY3 == 0)return 3;
    }
    else if (KEY3 == 1 && KEY1 == 1 && KEY2 == 1)key_up = 1;
    return 0;// �ް�������
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

