#ifndef __RTC_H
#define __RTC_H
#ifdef __cplusplus
extern "C" {
#endif
#include "sys.h"
//Mini STM32������
//RTCʵʱʱ�� ��������
//����ԭ��@ALIENTEK
//2010/6/6

//ʱ��ṹ��
typedef struct
{
    vu8 hour;
    vu8 min;
    vu8 sec;
	  vu8  week;//��
    //����������
    vu16 w_year;
    vu8  w_month;
    vu8  w_date;
    
} _calendar_obj;
extern _calendar_obj calendar;  //�����ṹ��

extern u8 const mon_table[12];  //�·��������ݱ�
void Disp_Time(u8 x, u8 y, u8 size); //���ƶ�λ�ÿ�ʼ��ʾʱ��
void Disp_Week(u8 x, u8 y, u8 size, u8 lang); //��ָ��λ����ʾ����
u8 RTC_Init(void);        //��ʼ��RTC,����0,ʧ��;1,�ɹ�;
u8 Is_Leap_Year(u16 year);//ƽ��,�����ж�
u8 RTC_Get(void);         //����ʱ��
u8 RTC_Get_Week(u16 year, u8 month, u8 day);
u8 RTC_Set(u16 syear, u8 smon, u8 sday, u8 hour, u8 min, u8 sec); //����ʱ��
extern void get_time(u8 *time);
extern void RTCSec2Cale(_calendar_obj* cale, u32 timecount , u8 u8Compulsoryrefresh); //��ת������
extern u32 RTCCale2Sec(_calendar_obj cale); //ʱ��ת������

#ifdef __cplusplus
}
#endif
#endif
