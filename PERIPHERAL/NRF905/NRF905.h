#ifndef __NRF905_H__
#define __NRF905_H__

#include"sys.h"


//引脚输入模式
#define DR PCin(6)//PC6.37  
#define AM PCin(7)//PC7.38   
#define CD PCin(8)//PC8.39
#define MISO PBin(15)  //PB15.36 
//引脚输出模式
#define CSN PBout(12)   //PB12.33 
#define SCK PBout(13)   //PB13.34   
#define MOSI PBout(14)  //PB14.35 
#define TRX_CE PCout(9)  //PC9.40
#define PWR_UP PAout(8)  //PA8.41
#define TXEN PAout(9)    //PA9.42
//#define uCLK   


#define TxRxBuf_Len 0x20
extern u8 TxRxBuf[TxRxBuf_Len];



void GPIO_NRF905_Init(void);
//u8 SPI_Read(void);
//void SPI_Write(u8 send);
void nRF905Init(void);
void Config_Nrf905(void);
void TxPacket(u8* TxRxBuf);
void SetTxMode(void);
void SetRxMode(void);
u8 CheckDR(void);
void RxPacket(void);
void  RX(void);




#endif







