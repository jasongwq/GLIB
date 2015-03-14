#include "stm32f10x.h"
#include "EXTI.h"

/*			       基本使用方法
 *		EXTI_Configuration(GPIOA,GPIO_Pin_1,0);       表示 PA1 作为外部中断 下降沿触发
 *		EXTI_Configuration(GPIOB,GPIO_Pin_1,0);       表示 PB1 作为外部中断 下降沿触发
 *		EXTI_Configuration(GPIOB,GPIO_Pin_2,0);       表示 PB2 作为外部中断 下降沿触发
 *		EXTI_Configuration(GPIOB,GPIO_Pin_2,1);       表示 PB2 作为外部中断 上升沿触发
 *		EXTI_Configuration(GPIOB,GPIO_Pin_2,2);       表示 PB2 作为外部中断   边沿触发
 *
 */
void EXTI_Configuration(GPIO_TypeDef* GPIO, uint16_t GPIO_Pin, u8 Trigger)
{
    uint8_t  GPIO_PIN_SOURCE,GPIO_PORT_SOURCE;

	uint32_t EXTI_Line;

	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	if(GPIO==GPIOA){GPIO_PORT_SOURCE=GPIO_PortSourceGPIOA;RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);}
	else if(GPIO==GPIOB){GPIO_PORT_SOURCE=GPIO_PortSourceGPIOB;RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);}
	else if(GPIO==GPIOC){GPIO_PORT_SOURCE=GPIO_PortSourceGPIOC;RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);}
	else if(GPIO==GPIOD){GPIO_PORT_SOURCE=GPIO_PortSourceGPIOD;RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);}
	else if(GPIO==GPIOE){GPIO_PORT_SOURCE=GPIO_PortSourceGPIOE;RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);}
	else {}
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIO, &GPIO_InitStructure);

	if(GPIO_Pin==GPIO_Pin_0){EXTI_Line=EXTI_Line0;GPIO_PIN_SOURCE=GPIO_PinSource0;}
	else if(GPIO_Pin==GPIO_Pin_1 ){EXTI_Line=EXTI_Line1; GPIO_PIN_SOURCE=GPIO_PinSource1;}
	else if(GPIO_Pin==GPIO_Pin_2 ){EXTI_Line=EXTI_Line2; GPIO_PIN_SOURCE=GPIO_PinSource2; }
	else if(GPIO_Pin==GPIO_Pin_3 ){EXTI_Line=EXTI_Line3; GPIO_PIN_SOURCE=GPIO_PinSource3; }
	else if(GPIO_Pin==GPIO_Pin_4 ){EXTI_Line=EXTI_Line4; GPIO_PIN_SOURCE=GPIO_PinSource4; }
	else if(GPIO_Pin==GPIO_Pin_5 ){EXTI_Line=EXTI_Line5; GPIO_PIN_SOURCE=GPIO_PinSource5; }
	else if(GPIO_Pin==GPIO_Pin_6 ){EXTI_Line=EXTI_Line6; GPIO_PIN_SOURCE=GPIO_PinSource6; }
	else if(GPIO_Pin==GPIO_Pin_7 ){EXTI_Line=EXTI_Line7; GPIO_PIN_SOURCE=GPIO_PinSource7; }
	else if(GPIO_Pin==GPIO_Pin_8 ){EXTI_Line=EXTI_Line8; GPIO_PIN_SOURCE=GPIO_PinSource8; }
	else if(GPIO_Pin==GPIO_Pin_9 ){EXTI_Line=EXTI_Line9; GPIO_PIN_SOURCE=GPIO_PinSource9; }
	else if(GPIO_Pin==GPIO_Pin_10){EXTI_Line=EXTI_Line10;GPIO_PIN_SOURCE=GPIO_PinSource10;}
	else if(GPIO_Pin==GPIO_Pin_11){EXTI_Line=EXTI_Line11;GPIO_PIN_SOURCE=GPIO_PinSource11;}
	else if(GPIO_Pin==GPIO_Pin_12){EXTI_Line=EXTI_Line12;GPIO_PIN_SOURCE=GPIO_PinSource12;}
	else if(GPIO_Pin==GPIO_Pin_13){EXTI_Line=EXTI_Line13;GPIO_PIN_SOURCE=GPIO_PinSource13;}
	else if(GPIO_Pin==GPIO_Pin_14){EXTI_Line=EXTI_Line14;GPIO_PIN_SOURCE=GPIO_PinSource14;}
	else if(GPIO_Pin==GPIO_Pin_15){EXTI_Line=EXTI_Line15;GPIO_PIN_SOURCE=GPIO_PinSource15;}
	else {}


	GPIO_EXTILineConfig(GPIO_PORT_SOURCE, GPIO_PIN_SOURCE);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line; 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;

	if(Trigger==0)EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	else if(Trigger==1)EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	else if(Trigger==2)EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;

	EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
	EXTI_Init(&EXTI_InitStructure);
}




void EXTI_NVIC_Configuration(u8 Line ,u8 PriorityGroup,u8 PreemptionPriority,u8 SubPriority)
{
	NVIC_InitTypeDef NVIC_InitStructure;

    if(PriorityGroup==0)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	else if(PriorityGroup==1)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	else if(PriorityGroup==2)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	else if(PriorityGroup==3)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	else if(PriorityGroup==4)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	else {}
  
    // Enable the EXTI9_5 Interrupt 
    if(Line==0)NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//EXTI9_5_IRQn; //EXTI2_IRQn EXTI4_IRQn EXTI15_10_IRQn
	else if(Line==1)NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	else if(Line==2)NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
	else if(Line==3)NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	else if(Line==4)NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	else if(Line==5 || Line==6 ||Line==7 ||Line==8 ||Line==9)NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	else if(Line>=10 && Line<=15)NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	else {}
    if(PreemptionPriority!=0)NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/*********************************各条外部中断线的中断函数模板***********************************************
void EXTI0_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    {

        // Clear the EXTI Line 0 
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
void EXTI1_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line1) != RESET)
    {

        // Clear the EXTI Line 1 
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}
void EXTI2_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line2) != RESET)
    {

        // Clear the EXTI Line 2 
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
}
void EXTI3_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line3) != RESET)
    {

        // Clear the EXTI Line 3 
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}
void EXTI4_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    {

        // Clear the EXTI Line 4 
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
}
void EXTI9_5_IRQChannel(void)
{
    if(EXTI_GetITStatus(EXTI_Line5) != RESET)
    {

        // Clear the EXTI Line 5 
        EXTI_ClearITPendingBit(EXTI_Line5);
    }
    else if(EXTI_GetITStatus(EXTI_Line6) != RESET)
    {

        // Clear the EXTI Line 6 
        EXTI_ClearITPendingBit(EXTI_Line6);
    }
    else if(EXTI_GetITStatus(EXTI_Line7) != RESET)
    {

        // Clear the EXTI Line 7 
        EXTI_ClearITPendingBit(EXTI_Line7);
    }
    else if(EXTI_GetITStatus(EXTI_Line8) != RESET)
    {

        // Clear the EXTI Line 8 
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
    else if(EXTI_GetITStatus(EXTI_Line9) != RESET)
    {

        // Clear the EXTI Line 9
        EXTI_ClearITPendingBit(EXTI_Line9);
    }
}
void EXTI15_10_IRQHandler(void) 
{
    if(EXTI_GetITStatus(EXTI_Line10) != RESET)
    {
    
        // Clear the EXTI Line 10  
        EXTI_ClearITPendingBit(EXTI_Line10);
    }
	else if(EXTI_GetITStatus(EXTI_Line11) != RESET)
    {
    
        // Clear the EXTI Line 11  
        EXTI_ClearITPendingBit(EXTI_Line11);
    }
	else if(EXTI_GetITStatus(EXTI_Line12) != RESET)
    {
    
        // Clear the EXTI Line 12  
        EXTI_ClearITPendingBit(EXTI_Line12);
    }
	else if(EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
    
        // Clear the EXTI Line 13   
        EXTI_ClearITPendingBit(EXTI_Line13);
    }
	else if(EXTI_GetITStatus(EXTI_Line14) != RESET)
    {
    
        // Clear the EXTI Line 14   
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
	else if(EXTI_GetITStatus(EXTI_Line15) != RESET)
    {
    
        // Clear the EXTI Line 15  
        EXTI_ClearITPendingBit(EXTI_Line15);
    }
}



NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  // Enable the EXTI9_5 Interrupt 
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; //EXTI2_IRQn EXTI4_IRQn EXTI15_10_IRQn
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
*/
