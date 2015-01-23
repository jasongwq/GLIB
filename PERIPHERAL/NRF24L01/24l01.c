#include "24l01.h"
#include "lcd.h"
#include "delay.h"
#include "spi.h"
#include "gpio.h"
#include "key.h"
#include "led.h"
#include "usart.h"
/*
SPI2
DND     VCC
CE      Chip Enable Activates RX or TX mode             PC6
CSN     SPI Chip Select                                 PB0
SCK     SPI Clock                                       PB13
MOSI    SPI Slave Data Input                            PB15
MISO    SPI Slave Data Output, with tri-state option    PB14
IQR     Maskable interrupt pin. Active low              PA0
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//NRF24L01�Ĵ�����������
//#define READ_REG        0x00  //�����üĴ���,��5λΪ�Ĵ�����ַ
#define NRF24L01_WRITE_REG       0x20  //д���üĴ���,��5λΪ�Ĵ�����ַ
#define RD_RX_PLOAD     0x61  //��RX��Ч����,1~32�ֽ�
#define WR_TX_PLOAD     0xA0  //дTX��Ч����,1~32�ֽ�
#define FLUSH_TX        0xE1  //���TX FIFO�Ĵ���.����ģʽ����
#define FLUSH_RX        0xE2  //���RX FIFO�Ĵ���.����ģʽ����
#define REUSE_TX_PL     0xE3  //����ʹ����һ������,CEΪ��,���ݰ������Ϸ���.
#define NOP             0xFF  //�ղ���,����������״̬�Ĵ���
//SPI(NRF24L01)�Ĵ�����ַ
#define CONFIG          0x00  //���üĴ�����ַ;bit0:1����ģʽ,0����ģʽ;bit1:��ѡ��;bit2:CRCģʽ;bit3:CRCʹ��;
//bit4:�ж�MAX_RT(�ﵽ����ط������ж�)ʹ��;bit5:�ж�TX_DSʹ��;bit6:�ж�RX_DRʹ��
#define EN_AA           0x01  //ʹ���Զ�Ӧ����  bit0~5,��Ӧͨ��0~5
#define EN_RXADDR       0x02  //���յ�ַ����,bit0~5,��Ӧͨ��0~5
#define SETUP_AW        0x03  //���õ�ַ���(��������ͨ��):bit1,0:00,3�ֽ�;01,4�ֽ�;02,5�ֽ�;
#define SETUP_RETR      0x04  //�����Զ��ط�;bit3:0,�Զ��ط�������;bit7:4,�Զ��ط���ʱ 250*x+86us
#define RF_CH           0x05  //RFͨ��,bit6:0,����ͨ��Ƶ��;
#define RF_SETUP        0x06  //RF�Ĵ���;bit3:��������(0:1Mbps,1:2Mbps);bit2:1,���书��;bit0:�������Ŵ�������
#define STATUS          0x07  //״̬�Ĵ���;bit0:TX FIFO����־;bit3:1,��������ͨ����(���:6);bit4,�ﵽ�����ط�
//bit5:���ݷ�������ж�;bit6:���������ж�;
#define MAX_TX          0x10  //�ﵽ����ʹ����ж�
#define TX_OK           0x20  //TX��������ж�
#define RX_OK           0x40  //���յ������ж�

#define OBSERVE_TX      0x08  //���ͼ��Ĵ���,bit7:4,���ݰ���ʧ������;bit3:0,�ط�������
#define CD              0x09  //�ز����Ĵ���,bit0,�ز����;
#define RX_ADDR_P0      0x0A  //����ͨ��0���յ�ַ,��󳤶�5���ֽ�,���ֽ���ǰ
#define RX_ADDR_P1      0x0B  //����ͨ��1���յ�ַ,��󳤶�5���ֽ�,���ֽ���ǰ
#define RX_ADDR_P2      0x0C  //����ͨ��2���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define RX_ADDR_P3      0x0D  //����ͨ��3���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define RX_ADDR_P4      0x0E  //����ͨ��4���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define RX_ADDR_P5      0x0F  //����ͨ��5���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define TX_ADDR         0x10  //���͵�ַ(���ֽ���ǰ),ShockBurstTMģʽ��,RX_ADDR_P0��˵�ַ���
#define RX_PW_P0        0x11  //��������ͨ��0��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P1        0x12  //��������ͨ��1��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P2        0x13  //��������ͨ��2��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P3        0x14  //��������ͨ��3��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P4        0x15  //��������ͨ��4��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P5        0x16  //��������ͨ��5��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define NRF_FIFO_STATUS 0x17  //FIFO״̬�Ĵ���;bit0,RX FIFO�Ĵ����ձ�־;bit1,RX FIFO����־;bit2,3,����
//bit4,TX FIFO�ձ�־;bit5,TX FIFO����־;bit6,1,ѭ��������һ���ݰ�.0,��ѭ��;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//24L01������
#define NRF24L01_CE   PCout(6) //24L01Ƭѡ�ź�
#define NRF24L01_CSN  PBout(0) //SPIƬѡ�ź�
#define NRF24L01_IRQ  PAin(0)  //IRQ������������
//24L01���ͽ������ݿ�ȶ���
#define TX_ADR_WIDTH    5       //5�ֽڵĵ�ַ���
#define RX_ADR_WIDTH    5       //5�ֽڵĵ�ַ���
#define TX_PLOAD_WIDTH  32      //32�ֽڵ��û����ݿ��
#define RX_PLOAD_WIDTH  32      //32�ֽڵ��û����ݿ��



//////////////////////////////////////////////////////////////////////////////////
const u8 TX_ADDRESS[TX_ADR_WIDTH] = {0x34, 0x43, 0x10, 0x10, 0x01}; //���͵�ַ
const u8 RX_ADDRESS[RX_ADR_WIDTH] = {0x34, 0x43, 0x10, 0x10, 0x01}; //���ܵ�ַ

//��ʼ��24L01
void NRF24L01_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIOB_Init(0, 3, PU);
    GPIOB_Init(12, 3, PU);
    GPIOC_Init(6, 3, PU);
    GPIOA_Init(0, 8, PU);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;  //��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    PBout(12) = 1;

    SPI2_Init();            //��ʼ��SPI
    //���NRF���ص��޸�SPI������
    SPI2->CR1 &= ~(1 << 6); //SPI�豸ʧ��
    SPI2->CR1 &= ~(1 << 1); //����ģʽ��SCKΪ0 CPOL=0
    SPI2->CR1 &= ~(1 << 0); //���ݲ����ӵ�1��ʱ����ؿ�ʼ,CPHA=0
    SPI2->CR1 |= 1 << 6;    //SPI�豸ʹ��

    NRF24L01_CE = 0;        //ʹ��24L01
    NRF24L01_CSN = 1;       //SPIƬѡȡ��
    while (NRF24L01_Check())//���NRF24L01�Ƿ���λ.
    {
        USART_OUT(DEBUG_USART, "\r\n NRF24L01 Error \r\n");
        delay_ms(200);
    }
    USART_OUT(DEBUG_USART, "\r\n NRF24L01 OK \r\n");

    NRF24L01_CE = 0;
    /**********���ճ�ʼ��*****************/
    NRF24L01_Write_Buf(NRF24L01_WRITE_REG + RX_ADDR_P0, (u8*)RX_ADDRESS, RX_ADR_WIDTH); //дRX�ڵ��ַ

    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + EN_AA, 0x01); //ʹ��ͨ��0���Զ�Ӧ��
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + EN_RXADDR, 0x01); //ʹ��ͨ��0�Ľ��յ�ַ
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + RF_CH, 40);      //����RFͨ��Ƶ��
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //ѡ��ͨ��0����Ч���ݿ��
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + RF_SETUP, 0x0f); //����TX�������,0db����,2Mbps,���������濪��
    /***********�����ʼ��****************/

    NRF24L01_Write_Buf(NRF24L01_WRITE_REG + TX_ADDR, (u8*)TX_ADDRESS, TX_ADR_WIDTH); //дTX�ڵ��ַ
    NRF24L01_Write_Buf(NRF24L01_WRITE_REG + RX_ADDR_P0, (u8*)RX_ADDRESS, RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK

    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + EN_AA, 0x01);       //ʹ��ͨ��0���Զ�Ӧ��
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + EN_RXADDR, 0x01);   //ʹ��ͨ��0�Ľ��յ�ַ
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + SETUP_RETR, 0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + RF_CH, 40);         //����RFͨ��Ϊ40
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + RF_SETUP, 0x0f);    //����TX�������,0db����,2Mbps,���������濪��
    NRF24L01_CE = 1;
}
//���24L01�Ƿ����
//����ֵ:0���ɹ�;1��ʧ��
static u8 NRF24L01_Check(void)
{
    u8 buf[5] = {0XA5, 0XA5, 0XA5, 0XA5, 0XA5};
    u8 i;
    SPI2_SetSpeed(SPI_BaudRatePrescaler_8); //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��
    NRF24L01_Write_Buf(NRF24L01_WRITE_REG + TX_ADDR, buf, 5); //д��5���ֽڵĵ�ַ.
    NRF24L01_Read_Buf(TX_ADDR, buf, 5); //����д��ĵ�ַ
    for (i = 0; i < 5; i++)if (buf[i] != 0XA5)break;
    if (i != 5)return 1; //���24L01����
    return 0;        //��⵽24L01
}
//SPIд�Ĵ���
//reg:ָ���Ĵ�����ַ
//value:д���ֵ
u8 NRF24L01_Write_Reg(u8 reg, u8 value)
{
    u8 status;
    PCout(6) = 1;
    NRF24L01_CSN = 0;                //ʹ��SPI����
    status = SPI2_ReadWriteByte(reg);//���ͼĴ�����
    SPI2_ReadWriteByte(value);       //д��Ĵ�����ֵ
    NRF24L01_CSN = 1;                //��ֹSPI����
    return (status);                 //����״ֵ̬
}
//��ȡSPI�Ĵ���ֵ
//reg:Ҫ���ļĴ���
u8 NRF24L01_Read_Reg(u8 reg)
{
    u8 reg_val;
    PCout(6) = 1;
    NRF24L01_CSN = 0;          //ʹ��SPI����
    SPI2_ReadWriteByte(reg);   //���ͼĴ�����
    reg_val = SPI2_ReadWriteByte(0XFF); //��ȡ�Ĵ�������
    NRF24L01_CSN = 1;          //��ֹSPI����
    return (reg_val);          //����״ֵ̬
}
//��ָ��λ�ö���ָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
static u8 NRF24L01_Read_Buf(u8 reg, u8* pBuf, u8 len)
{
    u8 status, u8_ctr;
    PCout(6) = 1;
    NRF24L01_CSN = 0;           //ʹ��SPI����
    status = SPI2_ReadWriteByte(reg); //���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
    for (u8_ctr = 0; u8_ctr < len; u8_ctr++)pBuf[u8_ctr] = SPI2_ReadWriteByte(0XFF); //��������
    NRF24L01_CSN = 1;     //�ر�SPI����
    return status;        //���ض�����״ֵ̬
}
//��ָ��λ��дָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
static u8 NRF24L01_Write_Buf(u8 reg, u8* pBuf, u8 len)
{
    u8 status, u8_ctr;
    PCout(6) = 1;
    NRF24L01_CSN = 0;          //ʹ��SPI����
    status = SPI2_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
    for (u8_ctr = 0; u8_ctr < len; u8_ctr++)SPI2_ReadWriteByte(*pBuf++); //д������
    NRF24L01_CSN = 1;       //�ر�SPI����
    return status;          //���ض�����״ֵ̬
}
//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:�������״��
static u8 NRF24L01_TxPacket(u8* txbuf)
{
    u8 sta;
    SPI2_SetSpeed(SPI_BaudRatePrescaler_8);//spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��
    NRF24L01_CE = 0;
    NRF24L01_Write_Buf(WR_TX_PLOAD, txbuf, TX_PLOAD_WIDTH); //д���ݵ�TX BUF  32���ֽ�
    NRF24L01_CE = 1; //��������
    while (NRF24L01_IRQ != 0); //�ȴ��������
    sta = NRF24L01_Read_Reg(STATUS);//��ȡ״̬�Ĵ�����ֵ
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + STATUS, sta); //���TX_DS��MAX_RT�жϱ�־
    NRF24L01_Write_Reg(FLUSH_TX, 0xff); //���TX FIFO�Ĵ���
    if (sta & MAX_TX) //�ﵽ����ط�����
    {
        // NRF24L01_Write_Reg(FLUSH_TX, 0xff); //���TX FIFO�Ĵ���
        return MAX_TX;
    }
    if (sta & TX_OK) //�������
    {
        return TX_OK;
    }
    return 0xff;//����ԭ����ʧ��
}
//����NRF24L01����һ������
//txbuf:���ݽ��ܻ���
//����ֵ:0��������ɣ��������������
static u8 NRF24L01_RxPacket(u8* rxbuf)
{
    u8 sta = 0;
    NRF24L01_CE = 1;
    SPI2_SetSpeed(SPI_BaudRatePrescaler_8); //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��
    while (NRF24L01_IRQ != 0) {}; //�ȴ��������

    sta = NRF24L01_Read_Reg(STATUS); //��ȡ״̬�Ĵ�����ֵ
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + STATUS, sta); //���TX_DS��MAX_RT�жϱ�־
    if (sta & RX_OK) //���յ�����
    {
        NRF24L01_Read_Buf(RD_RX_PLOAD, rxbuf, RX_PLOAD_WIDTH);//��ȡ����
        NRF24L01_Write_Reg(FLUSH_RX, 0xff); //���RX FIFO�Ĵ���
        NRF24L01_CE = 0;
        return 0;
    }
    return 1;//û�յ��κ�����
}
//�ú�����ʼ��NRF24L01��RXģʽ
//����RX��ַ,дRX���ݿ��,ѡ��RFƵ��,�����ʺ�LNA HCURR
//��CE��ߺ�,������RXģʽ,�����Խ���������
void NRF24L01_RX_Mode(void)
{
    NRF24L01_CE = 0;
    // NRF24L01_Write_Buf(NRF24L01_WRITE_REG + RX_ADDR_P0, (u8*)RX_ADDRESS, RX_ADR_WIDTH); //дRX�ڵ��ַ

    // NRF24L01_Write_Reg(NRF24L01_WRITE_REG + EN_AA, 0x01); //ʹ��ͨ��0���Զ�Ӧ��
    // NRF24L01_Write_Reg(NRF24L01_WRITE_REG + EN_RXADDR, 0x01); //ʹ��ͨ��0�Ľ��յ�ַ
    // NRF24L01_Write_Reg(NRF24L01_WRITE_REG + RF_CH, 40);      //����RFͨ��Ƶ��
    // NRF24L01_Write_Reg(NRF24L01_WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH); //ѡ��ͨ��0����Ч���ݿ��
    // NRF24L01_Write_Reg(NRF24L01_WRITE_REG + RF_SETUP, 0x0f); //����TX�������,0db����,2Mbps,���������濪��
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + CONFIG, 0x0f); //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ
    NRF24L01_CE = 1; //CEΪ��,�������ģʽ
    //delay_us(10);
}
//�ú�����ʼ��NRF24L01��TXģʽ
//����TX��ַ,дTX���ݿ��,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
//PWR_UP,CRCʹ��
//��CE��ߺ�,������RXģʽ,�����Խ���������
//CEΪ�ߴ���10us,����������.
void NRF24L01_TX_Mode(void)
{
    NRF24L01_CE = 0;
    // NRF24L01_Write_Buf(NRF24L01_WRITE_REG + TX_ADDR, (u8*)TX_ADDRESS, TX_ADR_WIDTH); //дTX�ڵ��ַ
    // NRF24L01_Write_Buf(NRF24L01_WRITE_REG + RX_ADDR_P0, (u8*)RX_ADDRESS, RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK

    // NRF24L01_Write_Reg(NRF24L01_WRITE_REG + EN_AA, 0x01);         //ʹ��ͨ��0���Զ�Ӧ��
    // NRF24L01_Write_Reg(NRF24L01_WRITE_REG + EN_RXADDR, 0x01); //ʹ��ͨ��0�Ľ��յ�ַ
    // NRF24L01_Write_Reg(NRF24L01_WRITE_REG + SETUP_RETR, 0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
    // NRF24L01_Write_Reg(NRF24L01_WRITE_REG + RF_CH, 40);           //����RFͨ��Ϊ40
    // NRF24L01_Write_Reg(NRF24L01_WRITE_REG + RF_SETUP, 0x0f);  //����TX�������,0db����,2Mbps,���������濪��
    NRF24L01_Write_Reg(NRF24L01_WRITE_REG + CONFIG, 0x0e);      //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
    NRF24L01_CE = 1; //CEΪ��,10us����������
    delay_us(10);
}



//void NRF24L01_Test_0(void)
//{
//    u8 sta;
//    u8 key, mode;
//    u32 t = 0;
//    u8 tmp_buf[33];
//    while (1) //�ڸò���ȷ�������ĸ�ģʽ!
//    {
//        key = KEY_Scan(0);
//        if (key == 1)
//        {
//            mode = 0;
//            break;
//        }
//        else if (key == 2)
//        {
//            mode = 1;
//            break;
//        }
//        t++;
//        if (t == 100)LCD_ShowString(10, 150, 230, 16, 16, "KEY0:RX_Mode  KEY1:TX_Mode"); //��˸��ʾ��ʾ��Ϣ
//        if (t == 200)
//        {
//            LCD_Fill(10, 150, 230, 150 + 16, WHITE);
//            t = 0;
//        }
//        delay_ms(5);
//    }
//    LCD_Fill(10, 150, 240, 166, WHITE); //����������ʾ
//    POINT_COLOR = BLUE; //��������Ϊ��ɫ
//    if (mode == 0) //RXģʽ
//    {
//        LCD_ShowString(60, 150, 200, 16, 16, "NRF24L01 RX_Mode");
//        LCD_ShowString(60, 170, 200, 16, 16, "Received DATA:");
//        NRF24L01_RX_Mode();
//        while (1)
//        {
//            if (NRF24L01_RxPacket(tmp_buf) == RX_OK) //һ�����յ���Ϣ,����ʾ����.
//            {
//                tmp_buf[32] = 0; //�����ַ���������
//                LCD_ShowString(0, 190, 239, 32, 16, (char*)tmp_buf);
//                USART_OUT(USART2, "\r\n DATA:%s \r\n", (char*)tmp_buf);
//            }
//            else delay_us(10);
//            t++;
//            if (t == 10000) //��Լ1s�Ӹı�һ��״̬
//            {
//                t = 0;
//                LED1 = !LED1;
//            }
//        };
//    }
//    else //TXģʽ
//    {
//        LCD_ShowString(60, 150, 200, 16, 16, "NRF24L01 TX_Mode");
//        NRF24L01_TX_Mode();
//        mode = ' '; //�ӿո����ʼ
//        while (1)
//        {
//            sta = NRF24L01_TxPacket(tmp_buf);
//            if (sta == TX_OK)
//            {
//                LCD_ShowString(60, 170, 239, 32, 16, "Sended DATA:");
//                LCD_ShowString(0, 190, 239, 32, 16, (char*)tmp_buf);
//                key = mode;
//                for (t = 0; t < 32; t++)
//                {
//                    key++;
//                    if (key > ('~'))key = ' ';
//                    tmp_buf[t] = key;
//                }
//                mode++;
//                if (mode > '~')mode = ' ';
//                tmp_buf[32] = 0; //���������
//            }
//            else
//            {
//                if (sta == MAX_TX)
//                    //USART_OUT(USART2, "\r\n MAX_TX \r\n");
//                    LCD_ShowString(60, 170, 239, 32, 16, "MAX_TX ");
//                else
//                    //USART_OUT(USART2, "\r\n Send Failed \r\n");
//                    LCD_ShowString(60, 170, 239, 32, 16, "Send Failed ");
//                LCD_Fill(0, 188, 240, 218, WHITE); //����������ʾ
//            };
//            LED1 = !LED1;
//            delay_ms(5);
//        };
//    }
//}

u8 NRF24L01_OUT(u8* temp)
{
    if (NRF24L01_TxPacket(temp) == TX_OK)return 0;
    else return 1;
}

u8 tmp_buf[128];
u8* NRF24L01_IN(u8* temp)
{
    u8 i;
    NRF24L01_RX_Mode();
    while (1)
    {
        if (NRF24L01_RxPacket(temp) == 0) //һ�����յ���Ϣ,����ʾ����.
        {
            break;
        }
        else
            for (i = 0; i < 32; i++)
            {
                *(temp + 1) = 128;
                delay_us(10);
            }
    }
    return temp;
}


u8* NRF24L01_TRANS_0(u8* temp)
{
    NRF24L01_RX_Mode();
    while (1)
    {
        USART_OUT(DEBUG_USART, "r");
        if (NRF24L01_RxPacket(tmp_buf) == RX_OK) //һ�����յ���Ϣ,����ʾ����.
        {
            USART_OUT(USART2, "R");
            break;
        }
        else
            delay_us(10);
    }
    return tmp_buf;
}

void NRF24L01_TRANS_1(void)
{
    while (1)
    {
        NRF24L01_RX_Mode();
        delay_us(50);
        USART_OUT(DEBUG_USART, "r");
        if (NRF24L01_RxPacket(tmp_buf) == RX_OK) //һ�����յ���Ϣ,����ʾ����.
        {
        }
        else
            delay_us(10);
        NRF24L01_TX_Mode();
        delay_us(50);
        USART_OUT(USART2, "t");
        if (NRF24L01_TxPacket(tmp_buf) == TX_OK)
        {
        }
        else
            delay_us(10);
    }
}

