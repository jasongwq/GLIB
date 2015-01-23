#include "sys.h"
#include <stdio.h>
//#include "stm32_config.h"
//#include "usart.h"
#include "sys_usart.h"

void USART_DMA_Config(USART_TypeDef *USARTx, u32 SendBuff);
/*
//��
    if(USART2_RX_STA&0x8000)
    {
        u16 vol=0;
        u8 i;
        for(i=0;i<(USART2_RX_STA&0x3fff);i++)
        {
            vol=vol*10+(USART2_RX_BUF[i]-0x30);
        }
        USART2_RX_STA=0;
        USART_OUT(USART2,"%d\r\n",vol);
        Dac1_Set_Vol(vol);
    }
*********************************************
REMAP |  00      |   01         | 11        |
      |  TX  RX  |   TX  RX     | TX  RX    |
******|**********|**************|*******    |
USART1|  A9  A10 |   B6  B7     |           |
******|**********|**************|*******    |
USART2|  A2  A3  |   (D5  D6)   |           |
      |          |  (100)(144)  |           |
******|**********|**************|*******    |
USART3|  B10 B11 |   (C10 C11)  | (D8  D9)  |
      |          | (64 100 144) | (100 144) |
*********************************************
2013/8/27                            ********
2013/7/21                            ********
*/
//////////////////////////////////////////////////////////////////////////////////
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"                   //ucos ʹ��
#endif
//__align(4) char USART_TX_BUF[USART_SEND_LEN];

//////////////////////////////////////////////////////////////////
#if EN_USART_RX   //���ʹ���˽���
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
u8 USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��  ������ɱ�־
//bit14��  ���յ�0x0d
//bit13~0��    ���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA = 0;     //����״̬���
void ATK_Usart1_IQR(void)
{
    u8 res;
    if (USART1->SR & (1 << 5)) //���յ�����
    {
        res = USART1->DR;
        if ((USART_RX_STA & 0x8000) == 0) //����δ���
        {
            if (USART_RX_STA & 0x4000) //���յ���0x0d
            {
                if (res != 0x0a)USART_RX_STA = 0; //���մ���,���¿�ʼ
                else USART_RX_STA |= 0x8000; //���������
            }
            else  //��û�յ�0X0D
            {
                if (res == 0x0d)USART_RX_STA |= 0x4000;
                else
                {
                    USART_RX_BUF[USART_RX_STA & 0X3FFF] = res;
                    USART_RX_STA++;
                    if (USART_RX_STA > (USART_REC_LEN - 1))USART_RX_STA = 0; //�������ݴ���,���¿�ʼ����
                }
            }
        }
    }
#ifdef OS_TICKS_PER_SEC     //���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
    OSIntExit();
#endif
}
#endif
#if EN_USART_
//��ʼ��IO ����1
//bound:������
void uart_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
#if EN_USART_RX
    NVIC_InitTypeDef NVIC_InitStructure;
#endif
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //ʹ��USART1

#if AF_USART1_==1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); //GPIOAʱ���Լ����ù���ʱ��
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);//������ӳ��
    //USART1_TX AF  PB.6
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //PB.6
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //USART1_RX AF  PB.7
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#elif AF_USART1_==0
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��GPIOAʱ��
    //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //USART1_RX   PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#else
#error Error_AF_USART1_
#endif
#if EN_USART1_DMA_T
    USART_DMA_Config(USART1,(u32)TxBuffer[EN_USART_-1]);
#endif
    //USART ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
    USART_Init(USART1, &USART_InitStructure); //��ʼ������
    //Usart1 NVIC ����
#if EN_USART_RX                                                 //���ʹ���˽���
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3 ;  //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;          //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);                             //����ָ���Ĳ�����ʼ��VIC�Ĵ���
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
#endif
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���
}
#endif

#if EN_USART2_RX   //���ʹ���˽���
u8 USART2_RX_BUF[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u16 USART2_RX_STA = 0;                //����״̬���
void ATK_Usart2_IQR(void)
{
    u8 res;
#ifdef OS_TICKS_PER_SEC     //���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
    OSIntEnter();
#endif
    if (USART2->SR & (1 << 5)) //���յ�����
    {
        res = USART2->DR;
        if ((USART2_RX_STA & 0x8000) == 0) //����δ���
        {
            if (USART2_RX_STA & 0x4000) //���յ���0x0d
            {
                if (res != 0x0a)USART2_RX_STA = 0; //���մ���,���¿�ʼ
                else USART2_RX_STA |= 0x8000; //���������
            }
            else  //��û�յ�0X0D
            {
                if (res == 0x0d)USART2_RX_STA |= 0x4000;
                else
                {
                    USART2_RX_BUF[USART2_RX_STA & 0X3FFF] = res;
                    USART2_RX_STA++;
                    if (USART2_RX_STA > (USART2_REC_LEN - 1))USART2_RX_STA = 0; //�������ݴ���,���¿�ʼ����
                }
            }
        }
    }
}
#endif

#if EN_USART2_
void uart2_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
#if EN_USART2_RX
    NVIC_InitTypeDef NVIC_InitStructure;
#endif
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //ʹ��USART2
#if AF_USART2_==1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE); //GPIOXʱ���Լ����ù���ʱ��
    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);//������ӳ��
    //USART2_TX AF  PD.5
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //PB.6
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    //USART2_RX AF  PD.6
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOD, &GPIO_InitStructure);
#elif AF_USART2_==0

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��GPIOAʱ��
    //USART2_TX   PA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //USART2_RX   PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#else
#error Error_AF_USART2_
#endif
#if EN_USART2_DMA_T
    USART_DMA_Config(USART2,(u32)TxBuffer[EN_USART_ + EN_USART2_-1]);
#endif
    //USART ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ

    USART_Init(USART2, &USART_InitStructure); //��ʼ������
    //Usart2 NVIC ����
#if EN_USART2_RX         //���ʹ���˽���
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3 ; //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ���
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
#endif
    USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���
}
#endif

#if EN_USART3_RX   //���ʹ���˽���
u8 USART3_RX_BUF[USART3_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u16 USART3_RX_STA = 0;                //����״̬���
void ATK_Usart3_IQR(void)
{
    u8 res;
#ifdef OS_TICKS_PER_SEC     //���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
    OSIntEnter();
#endif
    if (USART3->SR & (1 << 5)) //���յ�����
    {
        res = USART3->DR;
        if ((USART3_RX_STA & 0x8000) == 0) //����δ���
        {
            if (USART3_RX_STA & 0x4000) //���յ���0x0d
            {
                if (res != 0x0a)USART3_RX_STA = 0; //���մ���,���¿�ʼ
                else USART3_RX_STA |= 0x8000; //���������
            }
            else  //��û�յ�0X0D
            {
                if (res == 0x0d)USART3_RX_STA |= 0x4000;
                else
                {
                    USART3_RX_BUF[USART3_RX_STA & 0X3FFF] = res;
                    USART3_RX_STA++;
                    if (USART3_RX_STA > (USART3_REC_LEN - 1))USART3_RX_STA = 0; //�������ݴ���,���¿�ʼ����
                }
            }
        }
    }
}
#endif

#if EN_USART3_
void uart3_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
#if EN_USART3_RX
    NVIC_InitTypeDef NVIC_InitStructure;
#endif
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //ʹ��USART3
#if AF_USART3_==1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE); //GPIOXʱ���Լ����ù���ʱ��
    GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);//������ӳ��
    //USART3_TX AF  PC.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.6
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //USART3_RX AF  PC.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#elif AF_USART3_==2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE); //GPIOXʱ���Լ����ù���ʱ��
    GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);//������ӳ��
    //USART3_TX AF  PD.8
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //PB.6
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    //USART3_RX AF  PD.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOD, &GPIO_InitStructure);
#elif AF_USART3_==0

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); //ʹ��GPIOAʱ���Լ����ù���ʱ��
    //USART3_TX   PB.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //USART3_RX   PB.11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#else
#error Error_AF_USART3_
#if EN_USART3_DMA_T
    USART_DMA_Config(USART3,(u32)TxBuffer[EN_USART_ + EN_USART2_ + EN_USART3_-1]);
#endif
#endif
    //USART ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
    USART_Init(USART3, &USART_InitStructure); //��ʼ������
    //USART3 NVIC ����
#if EN_USART3_RX         //���ʹ���˽���
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3 ; //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ���
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
#endif
    USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���
}
#endif



/*
 * ��������DMA_Config
 * ����  ��DMA ���ڵĳ�ʼ������
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */

void USART_DMA_Config(USART_TypeDef *USARTx, u32 SendBuff)
{
    DMA_Channel_TypeDef *DMAy_Channelx;
    //    uint8_t DMAy_Channelx_IRQn;
    DMA_InitTypeDef DMA_InitStructure;
    //NVIC_InitTypeDef NVIC_InitStructure;
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    if (USARTx == USART1)
    {
        DMAy_Channelx = DMA1_Channel4;
        //        DMAy_Channelx_IRQn = DMA1_Channel4_IRQn;
    }
    else if (USARTx == USART2)
    {
        DMAy_Channelx = DMA1_Channel7;
        //        DMAy_Channelx_IRQn = DMA1_Channel7_IRQn;
    }
    else if (USARTx == USART3)
    {
        DMAy_Channelx = DMA1_Channel2;
        //        DMAy_Channelx_IRQn = DMA1_Channel2_IRQn;
    }
    DMA_DeInit(DMAy_Channelx);

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  //����DMAʱ��
#if 0
    NVIC_Config();              //����DMA�ж�
    NVIC_InitStructure.NVIC_IRQChannel = DMAy_Channelx_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif
    /*����DMAԴ���ڴ��ַ&�������ݼĴ�����ַ*/
    //DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USARTx->DR;

    /*�ڴ��ַ(Ҫ����ı�����ָ��)*/
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;

    /*���򣺴��ڴ浽����*/
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;

    /*�����СDMA_BufferSize=SENDBUFF_SIZE*/
    DMA_InitStructure.DMA_BufferSize = sizeof(SendBuff);//SENDBUFF_SIZE;

    /*�����ַ����*/
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

    /*�ڴ��ַ����*/
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;

    /*�������ݵ�λ*/
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;

    /*�ڴ����ݵ�λ 8bit*/
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;

    /*DMAģʽ��һ�δ��䣬ѭ��*/
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;

    /*���ȼ�����*/
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;

    /*��ֹ�ڴ浽�ڴ�Ĵ���    */
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

    /*����DMA1��4ͨ��*/
    DMA_Init(DMAy_Channelx, &DMA_InitStructure);

    //DMA_Cmd (DMAy_Channelx, ENABLE);                //ʹ��DMA
    DMA_ITConfig(DMAy_Channelx, DMA_IT_TC, ENABLE); //����DMA������ɺ�����ж�
    USART_DMACmd(USARTx, USART_DMAReq_Tx, ENABLE); //ʹ�ܴ���1��DMA����
}

//����һ��DMA����
void USART_DMA_Enable(USART_TypeDef *USARTx, u16 size)
{
    DMA_Channel_TypeDef *DMAy_Channelx;
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    if (USARTx == USART1)
        DMAy_Channelx = DMA1_Channel4;
    else if (USARTx == USART2)
        DMAy_Channelx = DMA1_Channel7;
    else if (USARTx == USART3)
        DMAy_Channelx = DMA1_Channel2;
    while (DMAy_Channelx->CNDTR != 0); //�ȴ�ͨ��7�������
    DMA_Cmd(DMAy_Channelx, DISABLE );  //�ر�USART1 TX DMA1 ��ָʾ��ͨ��
    DMA_SetCurrDataCounter(DMAy_Channelx, size);//SENDBUFF_SIZE); //DMAͨ����DMA����Ĵ�С
    DMA_Cmd(DMAy_Channelx, ENABLE);    //ʹ��USART1 TX DMA1 ��ָʾ��ͨ��
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
