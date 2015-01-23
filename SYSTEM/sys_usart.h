#ifndef __SYS_USART_H_
#define __SYS_USART_H_
#include "sys.h"
#include "usart.h"
#include "Usart_Config.h"
extern u8 Rx_Buf[3][2][32]; //两个32字节的串口接收缓存
extern u8 TxBuffer[EN_USART_ + EN_USART2_ + EN_USART3_][0xff]; //发送缓存

int Sys_Printf(USART_TypeDef* USARTx, char* Data, ...);
extern uint8_t *Sys_sPrintf(USART_TypeDef *USARTx, unsigned char *DataToSend, unsigned char num);
void Uart_CheckEvent(void);
#endif
