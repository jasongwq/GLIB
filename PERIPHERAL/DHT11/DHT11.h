
#ifndef __DHT11_H
#define __DHT11_H 


#include "stm32f10x.h"
#include "delay.h"
#include "GPIO.h"

/*
    u8 temperature;  	    
	  u8 humidity;


    if(DHT11_Init())printf(" DHT11_Init_Fail \r\n");
		else printf(" DHT11_Init_Ok \r\n");		
		
		while(1)
    { 
				//printf("%s\t\n",RxBuffer1);
			  DHT11_Read_Data(&temperature,&humidity);
			  printf(" Tem= %d, Hum= %d \r\n",temperature,humidity);
				delay_ms(300);
    }


*/


//IO��������
#define DHT11_IO_IN  GPIOD_Init(13,IPD,PU);
#define DHT11_IO_OUT GPIOD_Init(13,Out_PP,PU);
////IO��������											   
#define	DHT11_DQ_OUT_Set   Set_D13 
#define	DHT11_DQ_OUT_Clr   Clr_D13
#define	DHT11_DQ_IN            D13  


u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11



#endif
