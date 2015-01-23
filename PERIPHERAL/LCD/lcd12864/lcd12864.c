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

/*LCD ģ���ʼ��*/
void initial_lcd()
{
    CS_CLR;//cs1=0;
    RST_CLR;//  reset=0;        /*�͵�ƽ��λ*/
    delay(100);
    RST_SET;// reset=1;        /*��λ���*/
    delay(20);
    transfer_command(0xe2);   /*��λ*/
    delay(5);
    transfer_command(0x2c);  /*��ѹ���� 1*/
    delay(5);
    transfer_command(0x2e);  /*��ѹ���� 2*/
    delay(5);
    transfer_command(0x2f);  /*��ѹ���� 3*/
    delay(5);
    transfer_command(0x23);  /*�ֵ��Աȶȣ������÷�Χ 0x20��0x27*/
    transfer_command(0x81);  /*΢���Աȶ�*/
    transfer_command(0x28);  /*0x1a,΢���Աȶȵ�ֵ�������÷�Χ 0x00��0x3f*/
    transfer_command(0xa2);  /*1/9 ƫѹ�ȣ�bias��*/
    transfer_command(0xc8);  /*��ɨ��˳�򣺴��ϵ���*/
    transfer_command(0xa0);  /*��ɨ��˳�򣺴�����*/
    transfer_command(0x40);  /*��ʼ�У���һ�п�ʼ*/
    transfer_command(0xaf);  /*����ʾ*/
    CS_SET;//cs1=1;
}

void lcd_address(unsigned char page, unsigned char column)
{
    CS_CLR;//cs1=0;
    column = column - 1;       //����ƽ����˵�ĵ� 1 �У��� LCD ���� IC ���ǵ� 0 �С������������ȥ 1.
    page = page - 1;
    transfer_command(0xb0 + page);      //����ҳ��ַ��ÿҳ�� 8 �С�һ������� 64 �б��ֳ� 8 ��ҳ ������ƽ����˵�ĵ� 1 ҳ���� LCD ���� IC ���ǵ� 0 ҳ�������������ȥ 1*/
    transfer_command(((column >> 4) & 0x0f) + 0x10); //�����е�ַ�ĸ� 4 λ
    transfer_command(column & 0x0f);      //�����е�ַ�ĵ� 4 λ
}

/*ȫ������*/
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
                transfer_data(ascii_table_5x7[j][k]);/*��ʾ 5x7 �� ASCII �ֵ� LCD �ϣ�y Ϊҳ��ַ��x Ϊ�е�ַ�����Ϊ����*/
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
