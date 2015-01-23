#include"nrf905.h"
#include"delay.h"
/*
nRF905Init();			//NRF905 ��ʼ�� 
SetRxMode();			//���� ģʽ Ϊ ���� 
SetTxMode();			//���� ģʽ Ϊ ����
RxPacket();				//���� �������
TxPacket(TxRxBuf);//���� �������
����
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
//            TxPacket(TxRxBuf);  //������������
//            USART_OUT(USART2, "\r\nT OK DATA:");
//            USART_OUT(USART2, (char*)(&TxRxBuf[1]));
            }
        }
        key = GPS_KEY_Scan(0);
        if (key == KEY_UP)
        {
            while (key == 0);   //�ȴ��ͷŰ���
            sprintf((char*)(&TxRxBuf[1]), "��������");
            TxRxBuf[0] = 0x29;
            SetTxMode();
						USART_OUT(USART2, "\r\nT OK DATA:");
            USART_OUT(USART2, (char*)(&TxRxBuf[1]));
            TxPacket(TxRxBuf);  //������������
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
//�������ݻ�����
/************************************************************/
//#define TxRxBuf_Len 4

u8 TxRxBuf[TxRxBuf_Len]; //�⼸�����ݣ�
u8 TxAddress[4] = {0xcc, 0xcc, 0xcc, 0xcc};


/***********************************************************/
//nrf905����ָ��
/***********************************************************/
#define WC      0x00//д���üĴ��� �˲��ֳ�������Ӳ������  һ������ı�
#define RC      0x10//�����üĴ���
#define WTP     0x20//��TX��Payload�Ĵ���д�� ������Ч����
#define RTP     0x21//��TX��Played�Ĵ�����ȡ ������Ч����
#define WTA     0x22//��TX-ADDress�Ĵ���д�뷢�͵�ַ
#define RTA     0x23//��TX-ADDress�Ĵ�����ȡ���͵�ַ
#define RRP     0x24//��RX��Played�Ĵ�����ȡ ���յ�����Ч����


/***************************************************************/
// IO ��ʼ��
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
//  NRF905�Ĵ�������
/************************************************************/
u8 RFConf[] =
{
	//�ֽ�0 �ز�Ƶ��
    0x4c,                 	//CH_NO,����Ƶ����430MHZ
	//�ֽ�1
    0x0c,                 	//�������Ϊ10db,���ط����ڵ�Ϊ����ģʽ
	//�ֽ�2
    0x44,                 	//��ַ������ã�Ϊ4�ֽ�
	//�ֽ�3 4
    TxRxBuf_Len, TxRxBuf_Len,            	//���շ�����Ч���ݳ���Ϊ4�ֽ�
	//�ֽ�5 6 7 8
    0xCC, 0xCC, 0xCC, 0xCC, //���յ�ַ
	//�ֽ�9
    0xd8,                 //4mhz ,�ⲿʱ���źŲ�ʹ�ܣ�16M����,CRC����16λCRCУ�飬
};


/****************************************************************/
//  ��NRF905��һ���ֽ�
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
//  ��NRF905д��һ���ֽ�
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
//  NRF905��ʼ��
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
//  ���Ĵ�������ָ��д��NRF905
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
//NRF905��������
//**************************************************************************************************
void TxPacket(u8* TxRxBuf)
{
    u8 i;
    CSN = 0;
    SPI_Write(WTP);//��TX��Payload�Ĵ���д�� ������Ч����
    for (i = 0; i < TxRxBuf_Len; i++)
    {
        SPI_Write(TxRxBuf[i]);      // Write 32 bytes Tx data
    }
    CSN = 1;
    //delay_us(5);                 // Spi disable
    CSN = 0;                    // Spi enable for write a spi command
    SPI_Write(WTA);//��TX-ADDress�Ĵ���д�뷢�͵�ַ
    for (i = 0; i < 4; i++)     // д����Է���ַһ���ĵ�ַ
    {
        SPI_Write(TxAddress[i]);
    }
    CSN = 1;                    // Spi disable
    TRX_CE = 1;                 // Set TRX_CE high,start Tx data transmission
    while (DR != 1); //delay_ms(1);                    //
    TRX_CE = 0;                 // Set TRX_CE low
}


//**************************************************************************************************
//����NRF905Ϊ����ģʽ
//**************************************************************************************************
void SetTxMode(void)
{
    TXEN = 1;
    TRX_CE = 0;
    delay_ms(1);                    // delay for mode change(>=650us)
}


//**************************************************************************************************
//����NRF905Ϊ����ģʽ
//**************************************************************************************************
void SetRxMode(void)
{
    TXEN = 0;
    TRX_CE = 1;
    delay_ms(1);                    // delay for mode change(>=650us)
}


//**************************************************************************************************
//�ж����ݽ���״̬
//**************************************************************************************************
u8 CheckDR(void)        //����Ƿ��������ݴ��� Data Ready
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
//��NRF905��ȡ���յ�������
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
//��������
//**************************************************************************************************




