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
(1)重映射不适用于36脚的封装                     |
(2)当PD0 和PD1 没有被重映射到OSC_IN和OSC_OUT 时,|
    重映射功能只适用于100 脚和144 脚的封装上    |
************************************************/
//////////////////////////////////////////////////////////////////////////////////
//CAN初始化
//tsjw:重新同步跳跃时间单元.范围:1~3; CAN_SJW_1tq    CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
//tbs2:时间段2的时间单元.范围:1~8;
//tbs1:时间段1的时间单元.范围:1~16;     CAN_BS1_1tq ~CAN_BS1_16tq
//brp :波特率分频器.范围:1~1024;(实际要加1,也就是1~1024) tq=(brp)*tpclk1
//注意以上参数任何一个都不能设为0,否则会乱.
//波特率=Fpclk1/((tsjw+tbs1+tbs2)*brp);
//mode:0,普通模式;1,回环模式;
//Fpclk1的时钟在初始化的时候设置为36M,如果设置CAN_Normal_Init(1,8,7,5,1);
//则波特率为:36M/((1+8+7)*5)=450Kbps
//返回值:0,初始化OK;
//    其他,初始化失败;

u8 CAN_Mode_Init(u8 tsjw, u8 tbs2, u8 tbs1, u16 brp, u8 mode)
{
    GPIO_InitTypeDef            GPIO_InitStructure;
    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;

#if CAN_RX0_INT_ENABLE
    NVIC_InitTypeDef  NVIC_InitStructure;
#endif

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//使能CAN1时钟

#if CAN_REMAP_ == 0
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能PORTA时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽
    GPIO_Init(GPIOA, &GPIO_InitStructure);      //初始化IO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化IO

#elif CAN_REMAP_ == 1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); //使能PORTA时钟
    GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);//开启重映射
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽
    GPIO_Init(GPIOB, &GPIO_InitStructure);      //初始化IO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化IO

#elif CAN_REMAP_ == 2
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE); //使能PORTA时钟
    GPIO_PinRemapConfig(GPIO_Remap2_CAN1, ENABLE);//开启重映射
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽
    GPIO_Init(GPIOD, &GPIO_InitStructure);      //初始化IO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
    GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化IO
#endif

    //CAN单元设置
    CAN_InitStructure.CAN_TTCM = DISABLE;                    //非时间触发通信模式  //
    CAN_InitStructure.CAN_ABOM = DISABLE;                    //软件自动离线管理  //
    CAN_InitStructure.CAN_AWUM = DISABLE;                    //睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位)//
    CAN_InitStructure.CAN_NART = ENABLE;                     //禁止报文自动传送 //
    CAN_InitStructure.CAN_RFLM = DISABLE;                    //报文不锁定,新的覆盖旧的 //
    CAN_InitStructure.CAN_TXFP = DISABLE;                    //优先级由报文标识符决定 //
    CAN_InitStructure.CAN_Mode = mode;           //模式设置： mode:0,普通模式;1,回环模式; //
    //设置波特率
    CAN_InitStructure.CAN_SJW = tsjw; //重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位  CAN_SJW_1tq    CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
    CAN_InitStructure.CAN_BS1 = tbs1; //Tbs1=tbs1+1个时间单位CAN_BS1_1tq ~CAN_BS1_16tq
    CAN_InitStructure.CAN_BS2 = tbs2; //Tbs2=tbs2+1个时间单位CAN_BS2_1tq ~    CAN_BS2_8tq
    CAN_InitStructure.CAN_Prescaler = brp;          //分频系数(Fdiv)为brp+1    //
    CAN_Init(CAN1, &CAN_InitStructure);            // 初始化CAN1

    CAN_FilterInitStructure.CAN_FilterNumber = 0; //过滤器0
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; //32位
    CAN_FilterInitStructure.CAN_FilterIdHigh = ((0x12 << 21) >> 16); //32位ID
    CAN_FilterInitStructure.CAN_FilterIdLow = (CAN_ID_STD | CAN_RTR_Data);
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = ((0x12 << 21) >> 16); //32位MASK
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = (CAN_ID_STD | CAN_RTR_Data);
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0; //过滤器0关联到FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE; //激活过滤器0
    CAN_FilterInit(&CAN_FilterInitStructure);//滤波器初始化

#if CAN_RX0_INT_ENABLE
    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE); //FIFO0消息挂号中断允许.

    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // 主优先级为1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // 次优先级为0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif

    return 0;
}

#if CAN_RX0_INT_ENABLE  //使能RX0中断
//中断服务函数
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

//can发送一组数据(固定格式:ID为0X12,标准帧,数据帧)
//len:数据长度(最大为8)
//msg:数据指针,最大为8个字节.
//返回值:0,成功;
//       其他,失败;
u8 Can_Send_Msg(u8 *msg, u8 len)
{
    u8 mbox;
    u16 i = 0;
    CanTxMsg TxMessage;
    TxMessage.StdId = 0x12;    // 标准标识符为0
    //    TxMessage.ExtId = 0x12;    // 设置扩展标示符（29位）
    //IDE位为标识符选择位（0，使用标准标识符；1，使用扩展标识符）
    TxMessage.IDE = 0;         // 使用扩展标识符
    //RTR位用于标识是否是远程帧（0，数据帧；1，远程帧）
    TxMessage.RTR = 0;         // 消息类型为数据帧，一帧8位
    //DLC段为数据长度表示段，高位在前,DLC段有效值为0~8，但是接收方接收到9~15的时候并不认为是错误
    TxMessage.DLC = len;       // 发送两帧信息
    for (i = 0; i < len; i++)
        TxMessage.Data[i] = msg[i];// 第一帧信息
    mbox = CAN_Transmit(CAN1, &TxMessage);
    i = 0;
    while ((CAN_TransmitStatus(CAN1, mbox) == CAN_TxStatus_Failed) && (i < 0XFFF))i++; //等待发送结束
    if (i >= 0XFFF)return 1;
    return 0;

}
//can口接收数据查询
//buf:数据缓存区;
//返回值:0,无数据被收到;
//       其他,接收的数据长度;
u8 Can_Receive_Msg(u8 *buf)
{
    u32 i;
    CanRxMsg RxMessage;
    if ( CAN_MessagePending(CAN1, CAN_FIFO0) == 0)return 0; //没有接收到数据,直接退出
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//读取数据
    for (i = 0; i < 8; i++)
        buf[i] = RxMessage.Data[i];
    return RxMessage.DLC;
}














