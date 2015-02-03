/***************************************************************/
//2013.8.27  Copyright@ rhyme������
/***************************************************************/
#include "stm32f10x.h"
#include "stdio.h"
#include "gpio.h"
#include "usart.h"
#include "delay.h"

/***************************************************************/
u8 USART_RX[60] = {""};
u8 USART_mark = 0;
u8 Press_mark = 0;
int USART_control = 0;
int USART_data = 0;
//��������õ�����
u8 config_4360_data[9] =
{
    0x30, 0x00, 0xC9 //R
    , 0x8F, 0xF1, 0xA8 //C
    , 0x40, 0x3E, 0x42 //N
};     //adf4360  ����50MHz�Ĳο����룬PDF=1MHz�ļ���Ƶ��


//u8 config_5687_data[32]={0x03,0x05,0x10,0x21,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0xd0,0x80,0x00,0x00,0x0c,0x00,0x14,0x24,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00};      //4���ڲ��ͨģʽ��PLLOUTӦ����4��Ƶ���

//u8 config_5687_data[32] = {0x03, 0x05, 0x10, 0x21, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//                          };    //�ź�Դ��DAC�ڲ�������4���ڲ��ͨģʽ��PLLOUTӦ����4��Ƶ���
u8 config_5687_data[32]={0x03,0x01,0x10,0x21,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00};      //2���ڲ��ͨģʽ��PLLOUTӦ����2��Ƶ���


/***************************************************************/

u8 config_addr = 0x00;
u8 config_addr1 = 0x80;
u8 rec_buf[32], config_addr_flag;

int main(void)
{
    u8 i, j, k;
    u8 addr, DATA_BUF;


    RCC_Configuration();
    delay_Configuration(72);
    USART3_Configuration(9600);


    LED_OUT
    Set_LED

    //�������ŷ���,�ӵ�Ƭ�����򿴹���
    //5687�����ŷ���
    SCLK_OUT
    SDENB_OUT
    SDIO5687_OUT
    SDO_IN
    RESETB_OUT
    //4360�����ŷ���
    CE4360_OUT
    Set_CE4360;    //оƬʹ����������
    delay_us(10);
    LE4360_OUT
    DATA4360_OUT
    CLK4360_OUT

    /**************************************************************/

    /***********************����DAC5687********************/
    //дDAC5687
    //��λDAC5687
    Clr_RESETB
    delay_us(10);
    Set_RESETB
    /*ָ���ֽ��������*/
    addr = 0x00;     //��ʼ��ַ0x00��I7='0',��ʾдģʽ��I6I5='00''����ʾÿ��дһ���ֽ�
    delay_us(10);
    /*����DAC5687�Ĵ�����32�ֽ����ݣ���32��д��*/
    for (i = 0; i < 32; i++)    //ѭ������32�Σ�ÿ��дһ���ֽ�
    {
        /*��ʼ��nCS��SCLK*/
        Set_SDENB
        delay_us(10);
        Clr_SDENB
        delay_us(10);
        Clr_SCLK
        delay_us(10);
        /*дָ���ֽڣ����õ�ַ*/
        DATA_BUF = addr;
        for (j = 0; j < 8; j++)    //ָ�����ڣ�8bits����
        {
            delay_us(10);
            if (DATA_BUF & 0x80)
                Set_SDIO5687
                else
                    Clr_SDIO5687
                    delay_us(10);
            Clr_SCLK
            delay_us(10);
            Set_SCLK           //ʱ��������,д������
            delay_us(10);
            DATA_BUF = DATA_BUF << 1;
        }
        DATA_BUF = config_5687_data[i]; //��config_5687_data������Ӧλ�ã�ȡҪд��һ�ֽ����ݣ��ŵ�DATA_BUF
        delay_us(10);
        /*д�Ĵ�������*/
        for (k = 0; k < 8; k++) //дһ���ֽ�
        {
            if (DATA_BUF & 0x80)
                Set_SDIO5687
                else
                    Clr_SDIO5687
                    //ʱ��������,д������
                    delay_us(10);
            Clr_SCLK
            delay_us(10);
            Set_SCLK
            delay_us(10);
            DATA_BUF = DATA_BUF << 1;
        }
        delay_us(10);
        /*����һ��д����*/
        Set_SDENB
        delay_us(10);
        addr = addr + 1;      //������һ���ֽڣ��Ĵ�����ַ��1
    }
    //��DAC5687
    for (i = 0; i < 32; i++) //��32�ֽ�,����rec_buf
    {

        DATA_BUF = 0x00;
        /*��ʼ��nCS��SCLK*/
        delay_us(10);
        Set_SDENB
        delay_us(10);
        Clr_SDENB
        delay_us(10);
        Clr_SCLK
        delay_us(10);
        /*дָ���ֽڣ����õ�ַ*/
        DATA_BUF = config_addr1;
        for (j = 0; j < 8; j++)    //ָ�����ڣ�8bits����
        {
            if (DATA_BUF & 0x80)
                Set_SDIO5687
                else
                    Clr_SDIO5687
                    delay_us(10);
            Clr_SCLK
            delay_us(10);
            Set_SCLK           //ʱ��������,д������
            delay_us(10);
            DATA_BUF = DATA_BUF << 1;
        }
        delay_us(10);
        config_addr1++;

        Set_SCLK
        delay_us(10);
        for (k = 0; k < 8; k++)
        {
            delay_us(10);
            DATA_BUF = DATA_BUF << 1;       //ʱ���½��ض������ݣ���λ��ǰ
            delay_us(10);
            Set_SCLK
            delay_us(10);
            Clr_SCLK
            delay_us(10);
            if (SDO == 1)
                DATA_BUF = DATA_BUF | 0x01;
            else
                DATA_BUF = DATA_BUF & 0xfe;
            delay_us(10);

        }
        delay_us(10);
        Set_SDENB
        delay_us(10);
        rec_buf[i] = DATA_BUF;


    }   


   /***********************����ADF4360********************/
    //����ADF4360
        Set_LE4360
        delay_ms(1);
        Clr_LE4360   //

        for (k = 1; k < 10; k++)
        {
            DATA_BUF = config_4360_data[k - 1];
            for (i = 0; i < 8; i++)
            {
                if (DATA_BUF & 0x80)
                    Set_DATA4360
                    else
                        Clr_DATA4360
                        Clr_CLK4360                   //������д������
                        Set_CLK4360

                        DATA_BUF = DATA_BUF << 1;
            }
            if (k == 3)
            {
                Set_LE4360
                          delay_ms(4);
                Clr_LE4360
                        delay_ms(20);
            }
            if (k == 6)
            {
                Set_LE4360
                         delay_ms(4);
                Clr_LE4360
                          delay_ms(20);
            }
            if (k == 9)
            {
                Set_LE4360
                          delay_ms(4);
                Clr_LE4360
                          delay_ms(20);
            }
        }
    for (i = 0; i < 32; i++)
        printf(" %x", rec_buf[i]);
				
}
/***************************************************************/

