#ifndef __24L01_H
#define __24L01_H
#include "sys.h"

void NRF24L01_Init(void);//��ʼ��
void NRF24L01_RX_Mode(void);//����Ϊ����ģʽ
void NRF24L01_TX_Mode(void);//����Ϊ����ģʽ
static u8 NRF24L01_Write_Buf(u8 reg, u8* pBuf, u8 u8s);//д������
static u8 NRF24L01_Read_Buf(u8 reg, u8* pBuf, u8 u8s);//��������
static u8 NRF24L01_Read_Reg(u8 reg);                     //���Ĵ���
static u8 NRF24L01_Write_Reg(u8 reg, u8 value);//д�Ĵ���
static u8 NRF24L01_Check(void);//���24L01�Ƿ����
//u8 NRF24L01_TxPacket(u8 *txbuf);//����һ����������
//u8 NRF24L01_RxPacket(u8 *rxbuf);//����һ����������


void NRF24L01_Test_0(void);
void NRF24L01_Test_1(void);

u8 NRF24L01_OUT(u8* temp);
u8* NRF24L01_IN(u8* temp);
u8* NRF24L01_TRANS_0(u8* temp);
void NRF24L01_TRANS_1(void);


#endif











