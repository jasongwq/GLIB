#include "G32_Nrf24l01.h"

uint8_t NRF24L01_RXDATA[RX_PLOAD_WIDTH];//nrf24l01接收到的数据
uint8_t NRF24L01_TXDATA[RX_PLOAD_WIDTH];//nrf24l01需要发送的数据
uint8_t NRF24L01_TXDATA_RC[RX_PLOAD_WIDTH];//nrf24l01需要发送的数据
u8  TX_ADDRESS[TX_ADR_WIDTH] = {0xE1, 0xE2, 0xE3, 0x44, 0xE5}; //本地地址
u8  RX_ADDRESS[RX_ADR_WIDTH] = {0xE1, 0xE2, 0xE3, 0x44, 0xE5}; //接收地址
//////////////////////////////////////////////////////////////////////////////////
//外部中断x服务程序
void EXTIX_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //使能复用功能时钟

    //GPIOX.x 中断线以及中断初始化配置   下降沿触发
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource7);

    EXTI_InitStructure.EXTI_Line = EXTI_Line7;  
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);     				//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;            //使能所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级2，
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;       //子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);
}

//extern void Nrf_Check_Event_IQR(void);
//void EXTI0_IRQHandler(void)
//{
//    Nrf_Check_Event_IQR();
//    EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位
//}

#ifdef NRF24L01_SPI1
#define Spi_RW SPI1_ReadWriteByte
void Nrf_Spi1_Init(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    /*配置 SPI_NRF_SPI的 SCK,MISO,MOSI引脚，GPIOA^5,GPIOA^6,GPIOA^7 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用功能
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*配置SPI_NRF_SPI的CE引脚*/
    RCC_APB2PeriphClockCmd(NRF24l01_CE_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = NRF24l01_CE_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(NRF24l01_CE_GPIO, &GPIO_InitStructure);
		/*配置SPI_NRF_SPI的 CSN 引脚*/
    RCC_APB2PeriphClockCmd(NRF24l01_CSN_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = NRF24l01_CSN_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(NRF24l01_CSN_GPIO, &GPIO_InitStructure);
    /*配置SPI_NRF_SPI的IRQ引脚*/
    RCC_APB2PeriphClockCmd(NRF24l01_IQR_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = NRF24l01_IQR_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; //上拉输入
    GPIO_Init(NRF24l01_IQR_GPIO, &GPIO_InitStructure);

    SPI_CSN_H();
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //双线全双工
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 		//主模式
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //数据大小8位
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; 			//时钟极性，空闲时为低
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	 	//第1个边沿有效，上升沿为采样时刻
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; 			//NSS信号由软件产生
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //8分频，9MHz
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 	//高位在前
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);
    /* Enable SPI1 */
    SPI_Cmd(SPI1, ENABLE);
}
#elif defined NRF24L01_SPI2
#define Spi_RW SPI2_ReadWriteByte
//#error 
void Nrf_Spi2_Init(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    /*配置 SPI_NRF_SPI的 SCK,MISO,MOSI引脚，GPIOB^13,GPIOB^14,GPIOB^15 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用功能
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*配置SPI_NRF_SPI的CE引脚*/
    RCC_APB2PeriphClockCmd(NRF24l01_CE_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = NRF24l01_CE_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(NRF24l01_CE_GPIO, &GPIO_InitStructure);
		/*配置SPI_NRF_SPI的 CSN 引脚:*/
    RCC_APB2PeriphClockCmd(NRF24l01_CSN_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = NRF24l01_CSN_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(NRF24l01_CSN_GPIO, &GPIO_InitStructure);
    /*配置SPI_NRF_SPI的IRQ引脚，*/
    RCC_APB2PeriphClockCmd(NRF24l01_IQR_RCC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = NRF24l01_IQR_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; //上拉输入
    GPIO_Init(NRF24l01_IQR_GPIO, &GPIO_InitStructure);

    SPI_CSN_H();

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //双线全双工
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//主模式
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	//数据大小8位
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;			//时钟极性，空闲时为低
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; 		//第1个边沿有效，上升沿为采样时刻
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; 			//NSS信号由软件产生
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //8分频，9MHz
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 	//高位在前
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStructure);
    /* Enable SPI2 */
    SPI_Cmd(SPI2, ENABLE);
}
#else

#define Set_SPI0_SCK NRF24l01_SPI_SCL_H
#define Clr_SPI0_SCK NRF24l01_SPI_SCL_L
#define Set_SPI0_MOSI NRF24l01_SPI_MOSI_H
#define Clr_SPI0_MOSI NRF24l01_SPI_MOSI_L
#define MISO_SPI0 NRF24l01_SPI_SIMO

u8 Spi_RW(u8 TxData)
{
    u8 i;
    for (i = 0; i < 8; i++)
    {
        if (TxData & 0x80)
        {
            Set_SPI0_MOSI
        }
        else
        {
            Clr_SPI0_MOSI
        }
        TxData <<= 1;
        Set_SPI0_SCK
        TxData |= MISO_SPI0;
        Clr_SPI0_SCK
    }
    return (TxData);
}
#endif
/*
*****************************************************************
* 写寄存器
*****************************************************************
*/
uint8_t NRF_Write_Reg(uint8_t reg, uint8_t value)
{
    uint8_t status;
    SPI_CSN_L();                /* 选通器件 */
    status = Spi_RW(reg);       /* 写寄存器地址 */
    Spi_RW(value);              /* 写数据 */
    SPI_CSN_H();                /* 禁止该器件 */
    return    status;
}
/*
*****************************************************************
* 读寄存器
*****************************************************************
*/
uint8_t NRF_Read_Reg(uint8_t reg)
{
    uint8_t reg_val;
    SPI_CSN_L();              /* 选通器件 */
    Spi_RW(reg);              /* 写寄存器地址 */
    reg_val = Spi_RW(0);      /* 读取该寄存器返回数据 */
    SPI_CSN_H();              /* 禁止该器件 */
    return  reg_val;
}
/*
*****************************************************************
* 写缓冲区
*****************************************************************
*/
uint8_t NRF_Write_Buf(uint8_t reg, uint8_t* pBuf, uint8_t uchars)
{
    uint8_t i;
    uint8_t status;
    SPI_CSN_L();            /* 选通器件 */
    status = Spi_RW(reg);   /* 写寄存器地址 */
    for (i = 0; i < uchars; i++)
    {
        Spi_RW(pBuf[i]);    /* 写数据 */
    }
    SPI_CSN_H();            /* 禁止该器件 */
    return  status;
}
/*
*****************************************************************
* 读缓冲区
*****************************************************************
*/
uint8_t NRF_Read_Buf(uint8_t reg, uint8_t* pBuf, uint8_t uchars)
{
    uint8_t i;
    uint8_t status;
    SPI_CSN_L();            /* 选通器件 */
    status = Spi_RW(reg);   /* 写寄存器地址 */
    for (i = 0; i < uchars; i++)
    {
        pBuf[i] = Spi_RW(0); /* 读取返回数据 */
    }
    SPI_CSN_H();             /* 禁止该器件 */
    return  status;
}
/*
*****************************************************************
* 写数据包
*****************************************************************
*/
void NRF_TxPacket(uint8_t* tx_buf, uint8_t len)
{
    SPI_CE_L();      //StandBy I模式
    NRF_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // 装载接收端地址
    NRF_Write_Buf(WR_TX_PLOAD, tx_buf, len);             // 装载数据
    SPI_CE_H();      //置高CE，激发数据发送
}
void NRF_TxPacket_AP(uint8_t* tx_buf, uint8_t len)
{
    SPI_CE_L();      //StandBy I模式
    NRF_Write_Buf(0xa8, tx_buf, len);            // 装载数据
    SPI_CE_H();      //置高CE
}
u8 Nrf24l01_Check(void)
{
    u8 buf1[5];
    u8 i;
    /*写入5个字节的地址. */
    NRF_Write_Buf(NRF_WRITE_REG + TX_ADDR, TX_ADDRESS, 5);
    /*读出写入的地址 */
    NRF_Read_Buf(TX_ADDR, buf1, 5);
    /*比较*/
    for (i = 0; i < 5; i++)
    {
        if (buf1[i] != TX_ADDRESS[i])
            break;
    }
    if (i == 5)
        return SUCCESS ; //MCU与NRF成功连接
    else
        return ERROR ; //MCU与NRF不正常连接
}
//MODEL_TX2,40
/*
24L01初始化
model：24L01 模式
ch：   通道
*/
void Nrf24l01_Init(u8 model, u8 ch)
{
#ifdef NRF24L01_SPI1
    Nrf_Spi1_Init();
#elif defined NRF24L01_SPI2
//  #error  
		Nrf_Spi2_Init();
#else
	#error 
#endif
		EXTIX_Init();
    SPI_CE_L();
    NRF_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);//写RX节点地址
    NRF_Write_Buf(NRF_WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);   //写TX节点地址
    NRF_Write_Reg(NRF_WRITE_REG + EN_AA, 0x01);     					//使能通道0的自动应答
    NRF_Write_Reg(NRF_WRITE_REG + EN_RXADDR, 0x01); 					//使能通道0的接收地址
    NRF_Write_Reg(NRF_WRITE_REG + SETUP_RETR, 0x1a);					//设置自动重发间隔时间:500us;最大自动重发次数:10次
    NRF_Write_Reg(NRF_WRITE_REG + RF_CH, ch);       					//设置RF通道为CHANAL
    NRF_Write_Reg(NRF_WRITE_REG + RF_SETUP, 0x0f);  					//设置TX发射参数,0db增益,2Mbps,低噪声增益开启
    //NRF_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x07);   					//设置TX发射参数,0db增益,1Mbps,低噪声增益开启
    /////////////////////////////////////////////////////////
    if (model == 1)             //RX
    {
        NRF_Write_Reg(NRF_WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);                            //选择通道0的有效数据宽度
        NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);         // IRQ收发完成中断开启,16位CRC,主接收
    }
    else if (model == 2)    //TX
    {
        NRF_Write_Reg(NRF_WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);                            //选择通道0的有效数据宽度
        NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0e);         // IRQ收发完成中断开启,16位CRC,主发送
    }
    else if (model == 3)    //RX2
    {
        NRF_Write_Reg(FLUSH_TX, 0xff);
        NRF_Write_Reg(FLUSH_RX, 0xff);
        NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0f);         // IRQ收发完成中断开启,16位CRC,主接收

        Spi_RW(0x50);
        Spi_RW(0x73);
        NRF_Write_Reg(NRF_WRITE_REG + 0x1c, 0x01);
        NRF_Write_Reg(NRF_WRITE_REG + 0x1d, 0x07);
    }
    else if (model == 4)    //TX2
    {
        NRF_Write_Reg(NRF_WRITE_REG + CONFIG, 0x0e);         // IRQ收发完成中断开启,16位CRC,主发送
        NRF_Write_Reg(FLUSH_TX, 0xff);
        NRF_Write_Reg(FLUSH_RX, 0xff);

        Spi_RW(0x50);
        Spi_RW(0x73);
        NRF_Write_Reg(NRF_WRITE_REG + 0x1c, 0x01);
        NRF_Write_Reg(NRF_WRITE_REG + 0x1d, 0x07);
    }
    SPI_CE_H();
}
////////////////////////////////////////////////////////////////////////////////
