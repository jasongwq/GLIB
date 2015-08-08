#ifndef __USR_USART_H_
#define __USR_USART_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "sys.h"
#include "sys_usart.h"
#include "stm32_config.h"

#if VERSIONS ==1
#define Printf_USART USART1
#endif
#if VERSIONS ==2
#define Printf_USART USART1
#endif


extern void (*ReceiveProtocol1)(u8 com_data);
extern void (*ReceiveProtocol2)(u8 com_data);
extern void (*ReceiveProtocol3)(u8 com_data);

extern u8 UsrtWifiENTMFlag;
extern u8 UsrtWifiAtRxBuffer[50];
	
#ifdef __cplusplus
}
#endif
#endif

