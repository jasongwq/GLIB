#include "lcd12864.h"
#include "lcdCode.h"
#include "sys.h"

void transfer_command(int data1)
{
    char i;
    CS_CLR;//cs1=0;
    RS_CLR;//rs=0;
    for (i = 0; i < 8; i++)
    {
        SCL_CLR;//sclk=0;
        if (data1 & 0x80) SDA_SET; //sid=1;
        else SDA_CLR;//sid=0;
        SCL_SET;//sclk=1;
        data1 = data1 <<= 1;
    }
}

void transfer_data(int data1)
{
    char i;
    CS_CLR;//cs1=0;
    RS_SET;//rs=1;
    for (i = 0; i < 8; i++)
    {
        SCL_CLR;//sclk=0;
        if (data1 & 0x80) SDA_SET; //sid=1;
        else SDA_CLR;//sid=0;
        SCL_SET;//sclk=1;
        data1 = data1 <<= 1;
    }
}

void delay(int i)
{
    int j, k;
    for (j = 0; j < i; j++)
        for (k = 0; k < 110; k++);
}

void waitkey()
{

}

/*LCD 模块初始化*/
void initial_lcd()
{
    CS_CLR;//cs1=0;
    RST_CLR;//  reset=0;        /*低电平复位*/
    delay(100);
    RST_SET;// reset=1;        /*复位完毕*/
    delay(20);
    transfer_command(0xe2);   /*软复位*/
    delay(5);
    transfer_command(0x2c);  /*升压步聚 1*/
    delay(5);
    transfer_command(0x2e);  /*升压步聚 2*/
    delay(5);
    transfer_command(0x2f);  /*升压步聚 3*/
    delay(5);
    transfer_command(0x23);  /*粗调对比度，可设置范围 0x20～0x27*/
    transfer_command(0x81);  /*微调对比度*/
    transfer_command(0x28);  /*0x1a,微调对比度的值，可设置范围 0x00～0x3f*/
    transfer_command(0xa2);  /*1/9 偏压比（bias）*/
    transfer_command(0xc8);  /*行扫描顺序：从上到下*/
    transfer_command(0xa0);  /*列扫描顺序：从左到右*/
    transfer_command(0x40);  /*起始行：第一行开始*/
    transfer_command(0xaf);  /*开显示*/
    CS_SET;//cs1=1;
}

void lcd_address(unsigned char page, unsigned char column)
{
    CS_CLR;//cs1=0;
    column = column - 1;       //我们平常所说的第 1 列，在 LCD 驱动 IC 里是第 0 列。所以在这里减去 1.
    page = page - 1;
    transfer_command(0xb0 + page);      //设置页地址。每页是 8 行。一个画面的 64 行被分成 8 个页 。我们平常所说的第 1 页，在 LCD 驱动 IC 里是第 0 页，所以在这里减去 1*/
    transfer_command(((column >> 4) & 0x0f) + 0x10); //设置列地址的高 4 位
    transfer_command(column & 0x0f);      //设置列地址的低 4 位
}

/*全屏清屏*/
void clear_screen()
{
    unsigned char i, j;
    CS_CLR;// cs1=0;
    for (i = 0; i < 9; i++)
    {
        lcd_address(1 + i, 1);
        for (j = 0; j < 132; j++)
        {
            transfer_data(0x00);
        }
    }
    CS_SET;//cs1=1;
}

//==================display a piture of 128*64 dots============ ====
void full_display()
{
    int i, j;
    for (i = 0; i < 8; i++)
    {
        CS_CLR;//cs1=0;
        lcd_address(i + 1, 0);
        for (j = 0; j < 128; j++)
        {
            transfer_data(0xff);
        }
    }
}

void display_string_5x7(unsigned int page, unsigned int column, unsigned char *text)
{
    unsigned int i = 0, j, k;
    CS_CLR;//cs1=0;
    while (text[i] > 0x00)
    {
        if ((text[i] >= 0x20) && (text[i] < 0x7e))
        {
            j = text[i] - 0x20;
            lcd_address(page, column);
            for (k = 0; k < 5; k++)
            {
                transfer_data(ascii_table_5x7[j][k]);/*显示 5x7 的 ASCII 字到 LCD 上，y 为页地址，x 为列地址，最后为数据*/
            }
            i++;
            column += 6;
        }
        else
            i++;
    }
}
/*
void textmain()
{
    initial_lcd();
    clear_screen();
    display_string_5x7(5,1,(unsigned char*)" ! #$%&'()*+,-./01234"); 
    display_string_5x7(6,1,(unsigned char*)"56789:;<=>?@ABCDEFGHI"); 
    display_string_5x7(7,1,(unsigned char*)"JKLMNOPQRSTUVWXYZ[]^"); 
    display_string_5x7(8,1,(unsigned char*)"_`abcdefghijklmnopqrs"); 
}
*/
