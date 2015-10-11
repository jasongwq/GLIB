#include "stm32f10x.h"
#include "sys.h"
#include "gpio.h"
#include "data_transfer.h"


/**
  * @brief Configures EXTI Lines.
  * @param None
  * @retval None
  */
void PVD_EXTI_Configuration(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;

  /* Configure EXTI Line16(PVD Output) to generate an interrupt on rising and
     falling edges */
  EXTI_ClearITPendingBit(EXTI_Line16); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line16;// PVD连接到中断线16上 
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//使用中断模式 
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//电压上升或下降越过设定阀值时都产生中断。
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;// 使能中断线
  EXTI_Init(&EXTI_InitStructure);// 初始
}
/**
  * @brief Configures NVIC and Vector Table base location.
  * @param None
  * @retval None
  */
void PVD_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断优先级配置 
  
  /* Enable the PVD Interrupt */ //设置PVD中断
  NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/

void PVD_IRQHandler(void)
{
if(EXTI_GetITStatus(EXTI_Line16) != RESET)
{
	extern void StmFlash_Save(void);
//RelayControlOn();
//StmFlash_Save();
/* Clear the Key Button EXTI line pending bit */
EXTI_ClearITPendingBit(EXTI_Line16);
}
}
void PvdInit(void)
{
  /* Enable PWR and BKP clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);//电源管理部分时钟开启 

  /* Configure EXTI Line to generate an interrupt on falling edge */
  PVD_EXTI_Configuration();

  /* NVIC configuration */
  PVD_NVIC_Configuration();
 
  /* Configure the PVD Level to 2.9V */
  PWR_PVDLevelConfig(PWR_PVDLevel_2V9);// 设定监控阀值 

  /* Enable the PVD Output */
  PWR_PVDCmd(ENABLE);// 使能PVD 
}
