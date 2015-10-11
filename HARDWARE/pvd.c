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
  EXTI_InitStructure.EXTI_Line = EXTI_Line16;// PVD���ӵ��ж���16�� 
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//ʹ���ж�ģʽ 
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//��ѹ�������½�Խ���趨��ֵʱ�������жϡ�
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;// ʹ���ж���
  EXTI_Init(&EXTI_InitStructure);// ��ʼ
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
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�ж����ȼ����� 
  
  /* Enable the PVD Interrupt */ //����PVD�ж�
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
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);//��Դ������ʱ�ӿ��� 

  /* Configure EXTI Line to generate an interrupt on falling edge */
  PVD_EXTI_Configuration();

  /* NVIC configuration */
  PVD_NVIC_Configuration();
 
  /* Configure the PVD Level to 2.9V */
  PWR_PVDLevelConfig(PWR_PVDLevel_2V9);// �趨��ط�ֵ 

  /* Enable the PVD Output */
  PWR_PVDCmd(ENABLE);// ʹ��PVD 
}
