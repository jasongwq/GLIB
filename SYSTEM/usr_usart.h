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
#define Printf_USART USART3
#endif
				 
#ifdef __cplusplus
        }
#endif
#endif

