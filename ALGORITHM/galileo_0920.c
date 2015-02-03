/***************************************************************/
//2013.8.27  Copyright@ rhyme呆瓜云
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
//定义待配置的数据
u8 config_4360_data[9] =
{
    0x30, 0x00, 0xC9 //R
    , 0x8F, 0xF1, 0xA8 //C
    , 0x40, 0x3E, 0x42 //N
};     //adf4360  按照50MHz的参考输入，PDF=1MHz的鉴相频率


//u8 config_5687_data[32]={0x03,0x05,0x10,0x21,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0xd0,0x80,0x00,0x00,0x0c,0x00,0x14,0x24,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00};      //4倍内插低通模式，PLLOUT应该是4分频输出

//u8 config_5687_data[32] = {0x03, 0x05, 0x10, 0x21, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
//                          };    //信号源由DAC内部产生；4倍内插低通模式，PLLOUT应该是4分频输出
u8 config_5687_data[32]={0x03,0x01,0x10,0x21,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00};      //2倍内插低通模式，PLLOUT应该是2分频输出


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

    //设置引脚方向,从单片机方向看过来
    //5687的引脚方向
    SCLK_OUT
    SDENB_OUT
    SDIO5687_OUT
    SDO_IN
    RESETB_OUT
    //4360的引脚方向
    CE4360_OUT
    Set_CE4360;    //芯片使能引脚拉高
    delay_us(10);
    LE4360_OUT
    DATA4360_OUT
    CLK4360_OUT

    /**************************************************************/

    /***********************配置DAC5687********************/
    //写DAC5687
    //复位DAC5687
    Clr_RESETB
    delay_us(10);
    Set_RESETB
    /*指令字节数据组合*/
    addr = 0x00;     //起始地址0x00，I7='0',表示写模式；I6I5='00''，表示每次写一个字节
    delay_us(10);
    /*配置DAC5687寄存器，32字节数据，分32次写入*/
    for (i = 0; i < 32; i++)    //循环配置32次，每次写一个字节
    {
        /*初始化nCS和SCLK*/
        Set_SDENB
        delay_us(10);
        Clr_SDENB
        delay_us(10);
        Clr_SCLK
        delay_us(10);
        /*写指令字节，配置地址*/
        DATA_BUF = addr;
        for (j = 0; j < 8; j++)    //指令周期，8bits数据
        {
            delay_us(10);
            if (DATA_BUF & 0x80)
                Set_SDIO5687
                else
                    Clr_SDIO5687
                    delay_us(10);
            Clr_SCLK
            delay_us(10);
            Set_SCLK           //时钟上升沿,写入数据
            delay_us(10);
            DATA_BUF = DATA_BUF << 1;
        }
        DATA_BUF = config_5687_data[i]; //从config_5687_data数组相应位置，取要写的一字节数据，放到DATA_BUF
        delay_us(10);
        /*写寄存器数据*/
        for (k = 0; k < 8; k++) //写一个字节
        {
            if (DATA_BUF & 0x80)
                Set_SDIO5687
                else
                    Clr_SDIO5687
                    //时钟上升沿,写入数据
                    delay_us(10);
            Clr_SCLK
            delay_us(10);
            Set_SCLK
            delay_us(10);
            DATA_BUF = DATA_BUF << 1;
        }
        delay_us(10);
        /*结束一次写操作*/
        Set_SDENB
        delay_us(10);
        addr = addr + 1;      //配置完一个字节，寄存器地址加1
    }
    //读DAC5687
    for (i = 0; i < 32; i++) //读32字节,存入rec_buf
    {

        DATA_BUF = 0x00;
        /*初始化nCS和SCLK*/
        delay_us(10);
        Set_SDENB
        delay_us(10);
        Clr_SDENB
        delay_us(10);
        Clr_SCLK
        delay_us(10);
        /*写指令字节，配置地址*/
        DATA_BUF = config_addr1;
        for (j = 0; j < 8; j++)    //指令周期，8bits数据
        {
            if (DATA_BUF & 0x80)
                Set_SDIO5687
                else
                    Clr_SDIO5687
                    delay_us(10);
            Clr_SCLK
            delay_us(10);
            Set_SCLK           //时钟上升沿,写入数据
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
            DATA_BUF = DATA_BUF << 1;       //时钟下降沿读出数据，高位在前
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


   /***********************配置ADF4360********************/
    //配置ADF4360
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
                        Clr_CLK4360                   //上升沿写入数据
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

