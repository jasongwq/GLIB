#ifndef __SYS_USART_H_
#define __SYS_USART_H_
#include "sys.h"
#include "usart.h"
#include "stm32_config.h"
extern u8 Rx_Buf[3][2][32]; //两个32字节的串口接收缓存
#if VERSIONS ==1
#define Printf_USART USART1
#endif
#if VERSIONS ==2
#define Printf_USART USART3
#endif

void Sys_Printf(USART_TypeDef *USARTx, char *Data, ...);
extern uint8_t *Sys_sPrintf(USART_TypeDef *USARTx, unsigned char *DataToSend, unsigned char num);
void Uart_CheckEvent(void);
#endif
