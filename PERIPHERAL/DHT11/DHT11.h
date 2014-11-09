
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


//IO方向设置
#define DHT11_IO_IN  GPIOD_Init(13,IPD,PU);
#define DHT11_IO_OUT GPIOD_Init(13,Out_PP,PU);
////IO操作函数											   
#define	DHT11_DQ_OUT_Set   Set_D13 
#define	DHT11_DQ_OUT_Clr   Clr_D13
#define	DHT11_DQ_IN            D13  


u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11



#endif
