#include "stm32f10x.h"
#ifndef __EXTI_H
#define __EXTI_H 

/*			       ����ʹ�÷���
 *		EXTI_Configuration(GPIOA,GPIO_Pin_1,0);       ��ʾ PA1 ��Ϊ�ⲿ�ж� �½��ش���
 *		EXTI_Configuration(GPIOB,GPIO_Pin_1,0);       ��ʾ PB1 ��Ϊ�ⲿ�ж� �½��ش���
 *		EXTI_Configuration(GPIOB,GPIO_Pin_2,0);       ��ʾ PB2 ��Ϊ�ⲿ�ж� �½��ش���
 *		EXTI_Configuration(GPIOB,GPIO_Pin_2,1);       ��ʾ PB2 ��Ϊ�ⲿ�ж� �����ش���
 *		EXTI_Configuration(GPIOB,GPIO_Pin_2,2);       ��ʾ PB2 ��Ϊ�ⲿ�ж�   ���ش���
 *
 *		
 *	    EXTI_NVIC_Configuration(2 , 5, 1, 4);		2 ��ʾ���õ���EXTI2_IRQn�ж�  5 ��ʾ�жϷ����Ѿ��ֺ�������ִ�п�����
 *													1 ��ʾǿռ���ȼ�����		  4 ��ʾ�����ȼ�����
 *		EXTI_GenerateSWInterrupt(EXTI_Line6);  //��������ж�
 *
 *
 */

void EXTI_Configuration(GPIO_TypeDef* GPIO,uint16_t GPIO_Pin, u8 Trigger);
void EXTI_NVIC_Configuration(u8 Line ,u8 PriorityGroup,u8 PreemptionPriority,u8 SubPriority);

#endif
