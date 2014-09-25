#include"nrf905.h"
#include"delay.h"
/*
nRF905Init();			//NRF905 初始化 
SetRxMode();			//设置 模式 为 接受 
SetTxMode();			//设置 模式 为 发送
RxPacket();				//接收 命令，数据
TxPacket(TxRxBuf);//发送 命令，数据
例：
    while (1)
    {
        SetRxMode();
        if (CheckDR() == 1)
        {
            for (i = 0; i < TxRxBuf_Len; i++)
            {
                TxRxBuf[i] = 0;
            }
            RxPacket();
            if (TxRxBuf[0] == 0x29)
            {
              USART_OUT(USART2, "\r\nR OK DATA:");
              USART_OUT(USART2, (char*)(&TxRxBuf[1]));
//							for(i=0;i<23;i++)
//							{
//								RxBuf[i]=TxRxBuf[i+1];
//								if(TxRxBuf[i]==0x0d&&TxRxBuf[i+1]==0x0a)
//									break;
//							}
//						sprintf((char*)(&TxRxBuf[1]), "01,DATA:%s",RxBuf);
//            TxRxBuf[0] = 0x29;
//            SetTxMode();
//            TxPacket(TxRxBuf);  //发送命令数据
//            USART_OUT(USART2, "\r\nT OK DATA:");
//            USART_OUT(USART2, (char*)(&TxRxBuf[1]));
            }
        }
        key = GPS_KEY_Scan(0);
        if (key == KEY_UP)
        {
            while (key == 0);   //等待释放按键
            sprintf((char*)(&TxRxBuf[1]), "测试数据");
            TxRxBuf[0] = 0x29;
            SetTxMode();
						USART_OUT(USART2, "\r\nT OK DATA:");
            USART_OUT(USART2, (char*)(&TxRxBuf[1]));
            TxPacket(TxRxBuf);  //发送命令数据
        }
    }
*/




//---------------------------------
#define BYTE_BIT0   0x01
#define BYTE_BIT7   0x80

//---------------------------------
u8 DATA_BUF;

#define DATA7   ((DATA_BUF&BYTE_BIT7)!= 0)
#define DATA0   ((DATA_BUF&BYTE_BIT0)!= 0)
//#define flag    (DATA_BUF&0x08)//?1:0
//#define flag1   (DATA_BUF&0x01)//?1:0

/************************************************************/
//发送数据缓冲区
/************************************************************/
//#define TxRxBuf_Len 4

u8 TxRxBuf[TxRxBuf_Len]; //这几个数据？
u8 TxAddress[4] = {0xcc, 0xcc, 0xcc, 0xcc};


/***********************************************************/
//nrf905控制指令
/***********************************************************/
#define WC      0x00//写配置寄存器 此部分程序属于硬性设置  一般无需改变
#define RC      0x10//读配置寄存器
#define WTP     0x20//向TX—Payload寄存器写入 发送有效数据
#define RTP     0x21//从TX—Played寄存器读取 发送有效数据
#define WTA     0x22//向TX-ADDress寄存器写入发送地址
#define RTA     0x23//从TX-ADDress寄存器读取发送地址
#define RRP     0x24//从RX—Played寄存器读取 接收道德有效数据


/***************************************************************/
// IO 初始化
/***************************************************************/
void GPIO_NRF905_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
		
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
		
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
		
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/************************************************************/
//  NRF905寄存器配置
/************************************************************/
u8 RFConf[] =
{
	//字节0 载波频率
    0x4c,                 	//CH_NO,配置频段在430MHZ
	//字节1
    0x0c,                 	//输出功率为10db,不重发，节电为正常模式
	//字节2
    0x44,                 	//地址宽度设置，为4字节
	//字节3 4
    TxRxBuf_Len, TxRxBuf_Len,            	//接收发送有效数据长度为4字节
	//字节5 6 7 8
    0xCC, 0xCC, 0xCC, 0xCC, //接收地址
	//字节9
    0xd8,                 //4mhz ,外部时钟信号不使能，16M晶振,CRC允许，16位CRC校验，
};


/****************************************************************/
//  从NRF905读一个字节
/****************************************************************/
u8 SPI_Read(void)
{
    u8 j;
    for (j = 0; j < 8; j++)
    {
        DATA_BUF = DATA_BUF << 1;
        SCK = 1;
        if (MISO)
            DATA_BUF |= BYTE_BIT0;
        else
            DATA_BUF &= ~BYTE_BIT0;
        SCK = 0;
    }
    return DATA_BUF;

}

/*******************************************************************/
//  向NRF905写入一个字节
/********************************************************************/
static void SPI_Write(u8 send)
{
    u8 i;
    DATA_BUF = send;
    for (i = 0; i < 8; i++)
    {
        if (DATA7)
        {
            MOSI = 1;
        }
        else
            MOSI = 0;
        SCK = 1;
        DATA_BUF = DATA_BUF << 1;
        SCK = 0;
    }

}


//*************************************************************
//  NRF905初始化
//****************************************************************
void nRF905Init(void)
{
    GPIO_NRF905_Init();
    CSN = 1;                      // Spi  disable
    SCK = 0;                    // Spi clock line init low
    DR = 1;                     // Init DR for input
    AM = 1;                     // Init AM for input
    CD = 1;                     // Init CD for input
    PWR_UP = 1;                 // nRF905 power on
    TRX_CE = 0;                 // Set nRF905 in standby mode
    TXEN = 0;               // set radio in Rx mode
    Config_Nrf905();
}

/**************************************************************/
//  将寄存器配置指令写入NRF905
/*************************************************************/
void Config_Nrf905(void)
{
    u8 i;
    CSN = 0;
    SPI_Write(WC);
    for (i = 0; i < 10; i++)
    {
        SPI_Write(RFConf[i]);
    }
    CSN = 1;
}


//**************************************************************************************************
//NRF905发送数据
//**************************************************************************************************
void TxPacket(u8* TxRxBuf)
{
    u8 i;
    CSN = 0;
    SPI_Write(WTP);//向TX—Payload寄存器写入 发送有效数据
    for (i = 0; i < TxRxBuf_Len; i++)
    {
        SPI_Write(TxRxBuf[i]);      // Write 32 bytes Tx data
    }
    CSN = 1;
    //delay_us(5);                 // Spi disable
    CSN = 0;                    // Spi enable for write a spi command
    SPI_Write(WTA);//向TX-ADDress寄存器写入发送地址
    for (i = 0; i < 4; i++)     // 写入与对方地址一样的地址
    {
        SPI_Write(TxAddress[i]);
    }
    CSN = 1;                    // Spi disable
    TRX_CE = 1;                 // Set TRX_CE high,start Tx data transmission
    while (DR != 1); //delay_ms(1);                    //
    TRX_CE = 0;                 // Set TRX_CE low
}


//**************************************************************************************************
//设置NRF905为发送模式
//**************************************************************************************************
void SetTxMode(void)
{
    TXEN = 1;
    TRX_CE = 0;
    delay_ms(1);                    // delay for mode change(>=650us)
}


//**************************************************************************************************
//设置NRF905为接收模式
//**************************************************************************************************
void SetRxMode(void)
{
    TXEN = 0;
    TRX_CE = 1;
    delay_ms(1);                    // delay for mode change(>=650us)
}


//**************************************************************************************************
//判断数据接收状态
//**************************************************************************************************
u8 CheckDR(void)        //检查是否有新数据传入 Data Ready
{
    if (DR == 1)
    {
        DR = 0;
        return 1;
    }
    else
    {
        return 0;
    }
}


//**************************************************************************************************
//从NRF905提取接收到的数据
//**************************************************************************************************
void RxPacket(void)
{
    u8 i;
    while (DR == 0);
    TRX_CE = 0;
    CSN = 0;                    // Spi enable for write a spi command
    SPI_Write(RRP);
    for (i = 0 ; i < TxRxBuf_Len ; i++)
    {
        TxRxBuf[i] = SPI_Read();// Read data and save to buffer
    }
    CSN = 1;
    while (DR || AM);
    TRX_CE = 1;
}


//**************************************************************************************************
//接收数据
//**************************************************************************************************




