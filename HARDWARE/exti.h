#include "stm32f10x.h"
#ifndef __EXTI_H
#define __EXTI_H 

/*			       基本使用方法
 *		EXTI_Configuration(GPIOA,GPIO_Pin_1,0);       表示 PA1 作为外部中断 下降沿触发
 *		EXTI_Configuration(GPIOB,GPIO_Pin_1,0);       表示 PB1 作为外部中断 下降沿触发
 *		EXTI_Configuration(GPIOB,GPIO_Pin_2,0);       表示 PB2 作为外部中断 下降沿触发
 *		EXTI_Configuration(GPIOB,GPIO_Pin_2,1);       表示 PB2 作为外部中断 上升沿触发
 *		EXTI_Configuration(GPIOB,GPIO_Pin_2,2);       表示 PB2 作为外部中断   边沿触发
 *
 *		
 *	    EXTI_NVIC_Configuration(2 , 5, 1, 4);		2 表示设置的是EXTI2_IRQn中断  5 表示中断分组已经分好了这里执行空命令
 *													1 表示强占优先级的数		  4 表示从优先级的数
 *		EXTI_GenerateSWInterrupt(EXTI_Line6);  //产生软件中断
 *
 *
 */

void EXTI_Configuration(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin, u8 Trigger);
void EXTI_NVIC_Configuration(u8 Line ,u8 PriorityGroup,u8 PreemptionPriority,u8 SubPriority);

#endif
