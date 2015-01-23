#include "can.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
/////////////////////////////////////////////////
/************************************************
REMAP   |  00   | 01(1) | 11(2) |               |
********************************|               |
CAN1_RX | PA11  | (PB8) | (PD0) |               |
CAN1_TX | PA12  | (PB9) | (PD1) |               |
*********************************               |
CAN2_RX | PB12  |  PB5  |       |               |
CAN2_TX | PB13  |  PB6  |       |               |
************************************************|
(1)��ӳ�䲻������36�ŵķ�װ                     |
(2)��PD0 ��PD1 û�б���ӳ�䵽OSC_IN��OSC_OUT ʱ,|
    ��ӳ�书��ֻ������100 �ź�144 �ŵķ�װ��    |
************************************************/
//////////////////////////////////////////////////////////////////////////////////
//CAN��ʼ��
//tsjw:����ͬ����Ծʱ�䵥Ԫ.��Χ:1~3; CAN_SJW_1tq    CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
//tbs2:ʱ���2��ʱ�䵥Ԫ.��Χ:1~8;
//tbs1:ʱ���1��ʱ�䵥Ԫ.��Χ:1~16;     CAN_BS1_1tq ~CAN_BS1_16tq
//brp :�����ʷ�Ƶ��.��Χ:1~1024;(ʵ��Ҫ��1,Ҳ����1~1024) tq=(brp)*tpclk1
//ע�����ϲ����κ�һ����������Ϊ0,�������.
//������=Fpclk1/((tsjw+tbs1+tbs2)*brp);
//mode:0,��ͨģʽ;1,�ػ�ģʽ;
//Fpclk1��ʱ���ڳ�ʼ����ʱ������Ϊ36M,�������CAN_Normal_Init(1,8,7,5,1);
//������Ϊ:36M/((1+8+7)*5)=450Kbps
//����ֵ:0,��ʼ��OK;
//    ����,��ʼ��ʧ��;

u8 CAN_Mode_Init(u8 tsjw, u8 tbs2, u8 tbs1, u16 brp, u8 mode)
{
    GPIO_InitTypeDef            GPIO_InitStructure;
    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;

#if CAN_RX0_INT_ENABLE
    NVIC_InitTypeDef  NVIC_InitStructure;
#endif

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//ʹ��CAN1ʱ��

#if CAN_REMAP_ == 0
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��PORTAʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);      //��ʼ��IO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��IO

#elif CAN_REMAP_ == 1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); //ʹ��PORTAʱ��
    GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);//������ӳ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);      //��ʼ��IO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��IO

#elif CAN_REMAP_ == 2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE); //ʹ��PORTAʱ��
    GPIO_PinRemapConfig(GPIO_Remap2_CAN1, ENABLE);//������ӳ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //��������
    GPIO_Init(GPIOD, &GPIO_InitStructure);      //��ʼ��IO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��IO
#endif

    //CAN��Ԫ����
    CAN_InitStructure.CAN_TTCM = DISABLE;                    //��ʱ�䴥��ͨ��ģʽ  //
    CAN_InitStructure.CAN_ABOM = DISABLE;                    //����Զ����߹���  //
    CAN_InitStructure.CAN_AWUM = DISABLE;                    //˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)//
    CAN_InitStructure.CAN_NART = ENABLE;                     //��ֹ�����Զ����� //
    CAN_InitStructure.CAN_RFLM = DISABLE;                    //���Ĳ�����,�µĸ��Ǿɵ� //
    CAN_InitStructure.CAN_TXFP = DISABLE;                    //���ȼ��ɱ��ı�ʶ������ //
    CAN_InitStructure.CAN_Mode = mode;           //ģʽ���ã� mode:0,��ͨģʽ;1,�ػ�ģʽ; //
    //���ò�����
    CAN_InitStructure.CAN_SJW = tsjw; //����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ  CAN_SJW_1tq    CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
    CAN_InitStructure.CAN_BS1 = tbs1; //Tbs1=tbs1+1��ʱ�䵥λCAN_BS1_1tq ~CAN_BS1_16tq
    CAN_InitStructure.CAN_BS2 = tbs2; //Tbs2=tbs2+1��ʱ�䵥λCAN_BS2_1tq ~    CAN_BS2_8tq
    CAN_InitStructure.CAN_Prescaler = brp;          //��Ƶϵ��(Fdiv)Ϊbrp+1    //
    CAN_Init(CAN1, &CAN_InitStructure);            // ��ʼ��CAN1

    CAN_FilterInitStructure.CAN_FilterNumber = 0; //������0
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; //32λ
    CAN_FilterInitStructure.CAN_FilterIdHigh = ((0x12 << 21) >> 16); //32λID
    CAN_FilterInitStructure.CAN_FilterIdLow = (CAN_ID_STD | CAN_RTR_Data);
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = ((0x12 << 21) >> 16); //32λMASK
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = (CAN_ID_STD | CAN_RTR_Data);
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0; //������0������FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE; //���������0
    CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��

#if CAN_RX0_INT_ENABLE
    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE); //FIFO0��Ϣ�Һ��ж�����.

    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // �����ȼ�Ϊ1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // �����ȼ�Ϊ0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif

    return 0;
}

#if CAN_RX0_INT_ENABLE  //ʹ��RX0�ж�
//�жϷ�����
void ATK_USB_LP_CAN1_RX0_IQR(void)
{
    CanRxMsg RxMessage;
    int i = 0;
    CAN_Receive(CAN1, 0, &RxMessage);
    for (i = 0; i < 8; i++)
        ;
    //printf("rxbuf[%d]:%d\r\n", i, RxMessage.Data[i]);
}
#endif

//can����һ������(�̶���ʽ:IDΪ0X12,��׼֡,����֡)
//len:���ݳ���(���Ϊ8)
//msg:����ָ��,���Ϊ8���ֽ�.
//����ֵ:0,�ɹ�;
//       ����,ʧ��;
u8 Can_Send_Msg(u8 *msg, u8 len)
{
    u8 mbox;
    u16 i = 0;
    CanTxMsg TxMessage;
    TxMessage.StdId = 0x12;    // ��׼��ʶ��Ϊ0
    //    TxMessage.ExtId = 0x12;    // ������չ��ʾ����29λ��
    //IDEλΪ��ʶ��ѡ��λ��0��ʹ�ñ�׼��ʶ����1��ʹ����չ��ʶ����
    TxMessage.IDE = 0;         // ʹ����չ��ʶ��
    //RTRλ���ڱ�ʶ�Ƿ���Զ��֡��0������֡��1��Զ��֡��
    TxMessage.RTR = 0;         // ��Ϣ����Ϊ����֡��һ֡8λ
    //DLC��Ϊ���ݳ��ȱ�ʾ�Σ���λ��ǰ,DLC����ЧֵΪ0~8�����ǽ��շ����յ�9~15��ʱ�򲢲���Ϊ�Ǵ���
    TxMessage.DLC = len;       // ������֡��Ϣ
    for (i = 0; i < len; i++)
        TxMessage.Data[i] = msg[i];// ��һ֡��Ϣ
    mbox = CAN_Transmit(CAN1, &TxMessage);
    i = 0;
    while ((CAN_TransmitStatus(CAN1, mbox) == CAN_TxStatus_Failed) && (i < 0XFFF))i++; //�ȴ����ͽ���
    if (i >= 0XFFF)return 1;
    return 0;

}
//can�ڽ������ݲ�ѯ
//buf:���ݻ�����;
//����ֵ:0,�����ݱ��յ�;
//       ����,���յ����ݳ���;
u8 Can_Receive_Msg(u8 *buf)
{
    u32 i;
    CanRxMsg RxMessage;
    if ( CAN_MessagePending(CAN1, CAN_FIFO0) == 0)return 0; //û�н��յ�����,ֱ���˳�
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//��ȡ����
    for (i = 0; i < 8; i++)
        buf[i] = RxMessage.Data[i];
    return RxMessage.DLC;
}














