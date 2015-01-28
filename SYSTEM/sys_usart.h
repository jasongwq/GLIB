#ifndef __SYS_USART_H_
#define __SYS_USART_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "sys.h"
#include "usart.h"
#include "Usart_Config.h"
extern u8 Rx_Buf[3][2][32]; //����32�ֽڵĴ��ڽ��ջ���
extern u8 TxBuffer[EN_USART_ + EN_USART2_ + EN_USART3_][0xff]; //���ͻ���

int Sys_Printf(USART_TypeDef* USARTx, char* Data, ...);
extern uint8_t *Sys_sPrintf(USART_TypeDef *USARTx, unsigned char *DataToSend, unsigned char num);
extern void vSys_Printf(USART_TypeDef *USARTx, char *Data, ...);
void Uart_CheckEvent(void);

#ifdef __cplusplus
}
#endif
#endif

