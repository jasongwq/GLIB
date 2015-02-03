#include "touch.h"
#include "lcd.h"
#include "delay.h"
#include "stdlib.h"
#include "math.h"
#include "exfuns.h"
#include "ff.h"
#include "usart.h"
#include "stdio.h"
#include "Display_Config.h"
//#include "24cxx.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������֧��ADS7843/7846/UH7843/7846/XPT2046/TSC2046�ȣ� ����
/*
��Դ��
SPI
*/
//////////////////////////////////////////////////////////////////////////////////

//_m_tp_dev tp_dev =
//{
//    TP_Init,
//    TP_Scan,
//    TP_Adjust,
//    0,
//    0,
//    0,
//    0,
//    0,
//    0,//0.066844,
//    0,//0.109823,
//    0,//-12,
//    0,//-22,
//    0,//1,
//};
//_m_tp_dev tp_dev =//�ܶ� 3����
//{
//    TP_Init,
//    TP_Scan,
//    TP_Adjust,
//    0,
//    0,
//    0,
//    0,
//    0,
//    0.066844,
//    0.109823,
//    -12+4,
//    -22-4,
//    1,
//};
#ifdef LCD_TP_CONGIG
_m_tp_dev tp_dev =
{
    TP_Init,
    TP_Scan,
    TP_Adjust,
    0,
    0,
    0,
    0,
    0,
    LCD_TP_xfac,
    LCD_TP_yfac,
    LCD_TP_xoff,
    LCD_TP_yoff,
    LCD_TP_TOUCHTYPE,
};
//Ĭ��Ϊtouchtype=0������.
u8 CMD_RDX = LCD_TP_DEFCMD_RDX;
u8 CMD_RDY = LCD_TP_DEFCMD_RDY;
#else
_m_tp_dev tp_dev =
{
    TP_Init,
    TP_Scan,
    TP_Adjust,
    0,
    0,
    0,
    0,
    0,
    0.071098,
    0.089543,
    -33,
    -12,
    0,//1,
};
//Ĭ��Ϊtouchtype=0������.
//u8 CMD_RDX = 0X90;
//u8 CMD_RDY = 0XD0;
u8 CMD_RDX = 0XD0;
u8 CMD_RDY = 0X90;
#endif

#if LCD_TOUCH_SPI_SOFT
static void TP_Write_Byte(u8 num)
{
    u8 count = 0;
    for (count = 0; count < 8; count++)
    {
        if (num & 0x80)TDIN = 1;
        else TDIN = 0;
        num <<= 1;
        TCLK = 0;
        TCLK = 1;   //��������Ч
    }
}
#else
//SPIд����
//������ICд��1byte����
//num:Ҫд�������
static unsigned char SPI_WriteByte(unsigned char data)
{
    unsigned char Data = 0;
    //�ȴ����ͻ�������
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    // ����һ���ֽ�
    SPI_I2S_SendData(SPI1, data);
    //�ȴ��Ƿ���յ�һ���ֽ�
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    // ��ø��ֽ�
    Data = SPI_I2S_ReceiveData(SPI1);
    // �����յ����ֽ�
    return Data;
}
#endif
#if LCD_TOUCH_SPI_SOFT
static u16 TP_Read_AD(u8 CMD)
{
    u8 count = 0;
    u16 Num = 0;
    TCLK = 0;   //������ʱ��
    TDIN = 0;   //����������
    TCS = 0;    //ѡ�д�����IC
    TP_Write_Byte(CMD);//����������
    delay_us(6);//ADS7846��ת��ʱ���Ϊ6us
    TCLK = 0;
    delay_us(1);
    TCLK = 1;   //��1��ʱ�ӣ����BUSY
    TCLK = 0;
    for (count = 0; count < 16; count++) //����16λ����,ֻ�и�12λ��Ч
    {
        Num <<= 1;
        TCLK = 0; //�½�����Ч
        TCLK = 1;
        if (DOUT)Num++;
    }
    Num >>= 4;  //ֻ�и�12λ��Ч.
    TCS = 1;    //�ͷ�Ƭѡ
    return (Num);
}
#else
//SPI������
//�Ӵ�����IC��ȡadcֵ
//CMD:ָ��
//����ֵ:����������
static u16 TP_Read_AD(u8 CMD)
{
    u16 x = 0;
    TCS = 0;                         //ѡ��XPT2046
    delay_us(6);
    SPI_WriteByte(CMD);              //����X���ȡ��־
    delay_us(6);
    x = SPI_WriteByte(0x00);         //������ȡ16λ������
    x <<= 8;
    x += SPI_WriteByte(0x00);
    delay_us(6);
    TCS = 1;
    x = x >> 3;                      //��λ�����12λ����Ч����0-4095
    return (x);
}
#endif
//��ȡһ������ֵ(x����y)
//������ȡREAD_TIMES������,����Щ������������,
//Ȼ��ȥ����ͺ����LOST_VAL����,ȡƽ��ֵ
//xy:ָ�CMD_RDX/CMD_RDY��
//����ֵ:����������
#define READ_TIMES 5    //��ȡ����
#define LOST_VAL 1      //����ֵ
u16 TP_Read_XOY(u8 xy)
{
    u16 i, j;
    u16 buf[READ_TIMES];
    u16 sum = 0;
    u16 temp;
    for (i = 0; i < READ_TIMES; i++)buf[i] = TP_Read_AD(xy);
    for (i = 0; i < READ_TIMES - 1; i++) //����
    {
        for (j = i + 1; j < READ_TIMES; j++)
        {
            if (buf[i] > buf[j]) //��������
            {
                temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }
    }
    sum = 0;
    for (i = LOST_VAL; i < READ_TIMES - LOST_VAL; i++)sum += buf[i];
    temp = sum / (READ_TIMES - 2 * LOST_VAL);
    return temp;
}
//��ȡx,y����
//��Сֵ��������100.
//x,y:��ȡ��������ֵ
//����ֵ:0,ʧ��;1,�ɹ���
u8 TP_Read_XY(u16 *x, u16 *y)
{
    u16 xtemp, ytemp;
    xtemp = TP_Read_XOY(CMD_RDX);
    ytemp = TP_Read_XOY(CMD_RDY);
    //if(xtemp<100||ytemp<100)return 0;//����ʧ��
    *x = xtemp;
    *y = ytemp;
    return 1;//�����ɹ�
}
//����2�ζ�ȡ������IC,�������ε�ƫ��ܳ���
//ERR_RANGE,��������,����Ϊ������ȷ,�����������.
//�ú����ܴ�����׼ȷ��
//x,y:��ȡ��������ֵ
//����ֵ:0,ʧ��;1,�ɹ���
#define ERR_RANGE 50 //��Χ 
u8 TP_Read_XY2(u16 *x, u16 *y)
{
    u16 x1, y1;
    u16 x2, y2;
    u8 flag;
    flag = TP_Read_XY(&x1, &y1);
    if (flag == 0)return (0);
    flag = TP_Read_XY(&x2, &y2);
    if (flag == 0)return (0);
    if (((x2 <= x1 && x1 < x2 + ERR_RANGE) || (x1 <= x2 && x2 < x1 + ERR_RANGE)) //ǰ�����β�����+-50��
            && ((y2 <= y1 && y1 < y2 + ERR_RANGE) || (y1 <= y2 && y2 < y1 + ERR_RANGE)))
    {
        *x = (x1 + x2) / 2;
        *y = (y1 + y2) / 2;
        return 1;
    }
    else return 0;
}
//////////////////////////////////////////////////////////////////////////////////
//��LCD�����йصĺ���
//��һ��������
//����У׼�õ�
//x,y:����
//color:��ɫ
//static 
void TP_Drow_Touch_Point(u16 x, u16 y, u16 color)
{
	  u16  colortemp=POINT_COLOR;
    POINT_COLOR = color;
    LCD_DrawLine(x - 12, y, x + 13, y); //����
    LCD_DrawLine(x, y - 12, x, y + 13); //����
    LCD_DrawPoint(x + 1, y + 1);
    LCD_DrawPoint(x - 1, y + 1);
    LCD_DrawPoint(x + 1, y - 1);
    LCD_DrawPoint(x - 1, y - 1);
    Draw_Circle(x, y, 6); //������Ȧ
	POINT_COLOR=colortemp;
}
//��һ�����(2*2�ĵ�)
//x,y:����
//color:��ɫ
void TP_Draw_Big_Point(u16 x, u16 y, u16 color)
{
	u16  colortemp=POINT_COLOR;
    POINT_COLOR = color;
    LCD_DrawPoint(x, y); //���ĵ�
    LCD_DrawPoint(x + 1, y);
    LCD_DrawPoint(x, y + 1);
    LCD_DrawPoint(x + 1, y + 1);
	POINT_COLOR=colortemp;
}
//////////////////////////////////////////////////////////////////////////////////
//��������ɨ��
//tp:0,��Ļ����;1,��������(У׼�����ⳡ����)
//����ֵ:��ǰ����״̬.
//0,�����޴���;1,�����д���
u8 TP_Scan(u8 tp)
{
    if (PEN == 0) //�а�������
    {
        if (tp)TP_Read_XY2(&tp_dev.x, &tp_dev.y); //��ȡ��������
        else if (TP_Read_XY2(&tp_dev.x, &tp_dev.y)) //��ȡ��Ļ����
        {
            tp_dev.x = tp_dev.xfac * tp_dev.x + tp_dev.xoff; //�����ת��Ϊ��Ļ����
            tp_dev.y = tp_dev.yfac * tp_dev.y + tp_dev.yoff;
        }
        if ((tp_dev.sta & TP_PRES_DOWN) == 0) //֮ǰû�б�����
        {
            tp_dev.sta = TP_PRES_DOWN | TP_CATH_PRES; //��������
            tp_dev.x0 = tp_dev.x; //��¼��һ�ΰ���ʱ������
            tp_dev.y0 = tp_dev.y;
        }
    }
    else
    {
        if (tp_dev.sta & TP_PRES_DOWN) //֮ǰ�Ǳ����µ�
        {
            tp_dev.sta &= ~(1 << 7); //��ǰ����ɿ�
        }
        else //֮ǰ��û�б�����
        {
            tp_dev.x0 = 0;
            tp_dev.y0 = 0;
            tp_dev.x = 0xffff;
            tp_dev.y = 0xffff;
        }
    }
    return tp_dev.sta & TP_PRES_DOWN; //���ص�ǰ�Ĵ���״̬
}
//��ʾ�ַ���
const char *TP_REMIND_MSG_TBL = "Please use the stylus click the cross on the screen.\
The cross will always move until the screen adjustment is completed.";

//��ʾУ׼���(��������)
void TP_Adj_Info_Show(u16 x0, u16 y0, u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3, u16 fac)
{
    POINT_COLOR = RED;
    LCD_ShowString(40, 160, lcddev.width, lcddev.height, 16, "x1:");
    LCD_ShowString(40 + 80, 160, lcddev.width, lcddev.height, 16, "y1:");
    LCD_ShowString(40, 180, lcddev.width, lcddev.height, 16, "x2:");
    LCD_ShowString(40 + 80, 180, lcddev.width, lcddev.height, 16, "y2:");
    LCD_ShowString(40, 200, lcddev.width, lcddev.height, 16, "x3:");
    LCD_ShowString(40 + 80, 200, lcddev.width, lcddev.height, 16, "y3:");
    LCD_ShowString(40, 220, lcddev.width, lcddev.height, 16, "x4:");
    LCD_ShowString(40 + 80, 220, lcddev.width, lcddev.height, 16, "y4:");
    LCD_ShowString(40, 240, lcddev.width, lcddev.height, 16, "fac is:");
    LCD_ShowNum(40 + 24, 160, x0, 4, 16); //��ʾ��ֵ
    LCD_ShowNum(40 + 24 + 80, 160, y0, 4, 16); //��ʾ��ֵ
    LCD_ShowNum(40 + 24, 180, x1, 4, 16); //��ʾ��ֵ
    LCD_ShowNum(40 + 24 + 80, 180, y1, 4, 16); //��ʾ��ֵ
    LCD_ShowNum(40 + 24, 200, x2, 4, 16); //��ʾ��ֵ
    LCD_ShowNum(40 + 24 + 80, 200, y2, 4, 16); //��ʾ��ֵ
    LCD_ShowNum(40 + 24, 220, x3, 4, 16); //��ʾ��ֵ
    LCD_ShowNum(40 + 24 + 80, 220, y3, 4, 16); //��ʾ��ֵ
    LCD_ShowNum(40 + 56, lcddev.width, fac, 3, 16); //��ʾ��ֵ,����ֵ������95~105��Χ֮��.

}

//������У׼����
//�õ��ĸ�У׼����
void TP_Adjust(void)
{
    u16 pos_temp[4][2];//���껺��ֵ
    u8  cnt = 0;
    u16 d1, d2;
    u32 tem1, tem2;
    float fac;
    u16 outtime = 0;
    cnt = 0;
    POINT_COLOR = BLUE;
    BACK_COLOR = WHITE;
    LCD_Clear(WHITE);//����
    POINT_COLOR = RED; //��ɫ
    LCD_Clear(WHITE);//����
    POINT_COLOR = BLACK;
    LCD_ShowString(40, 40, 160, 100, 16, (char *)TP_REMIND_MSG_TBL); //��ʾ��ʾ��Ϣ
    TP_Drow_Touch_Point(20, 20, RED); //����1
    tp_dev.sta = 0; //���������ź�
    tp_dev.xfac = 0; //xfac��������Ƿ�У׼��,����У׼֮ǰ�������!�������
    while (1) //�������10����û�а���,���Զ��˳�
    {
        tp_dev.scan(1);//ɨ����������
        if ((tp_dev.sta & 0xc0) == TP_CATH_PRES) //����������һ��(��ʱ�����ɿ���.)
        {
            outtime = 0;
            tp_dev.sta &= ~(1 << 6); //��ǰ����Ѿ����������.

            pos_temp[cnt][0] = tp_dev.x;
            pos_temp[cnt][1] = tp_dev.y;
            // LCD_ShowNum(40, 40, tp_dev.x, 10, 16);               //��ʾһ������
            // LCD_ShowNum(40, 60, tp_dev.y, 10, 16);               //��ʾһ������

            cnt++;
            switch (cnt)
            {
            case 1:
                TP_Drow_Touch_Point(20, 20, WHITE);             //�����1
                TP_Drow_Touch_Point(lcddev.width - 20, 20, RED); //����2
                break;
            case 2:
                TP_Drow_Touch_Point(lcddev.width - 20, 20, WHITE); //�����2
                TP_Drow_Touch_Point(20, lcddev.height - 20, RED); //����3
                break;
            case 3:
                TP_Drow_Touch_Point(20, lcddev.height - 20, WHITE);     //�����3
                TP_Drow_Touch_Point(lcddev.width - 20, lcddev.height - 20, RED); //����4
                break;
            case 4:  //ȫ���ĸ����Ѿ��õ�
                //�Ա����
                tem1 = abs(pos_temp[0][0] - pos_temp[1][0]); //x1-x2
                tem2 = abs(pos_temp[0][1] - pos_temp[1][1]); //y1-y2
                tem1 *= tem1;
                tem2 *= tem2;
                d1 = sqrt(tem1 + tem2); //�õ�1,2�ľ���

                tem1 = abs(pos_temp[2][0] - pos_temp[3][0]); //x3-x4
                tem2 = abs(pos_temp[2][1] - pos_temp[3][1]); //y3-y4
                tem1 *= tem1;
                tem2 *= tem2;
                d2 = sqrt(tem1 + tem2); //�õ�3,4�ľ���
                fac = (float)d1 / d2;
                if (fac < 0.95 || fac > 1.05 || d1 == 0 || d2 == 0) //���ϸ�
                {
                    cnt = 0;
                    TP_Drow_Touch_Point(lcddev.width - 20, lcddev.height - 20, WHITE); //�����4
                    TP_Drow_Touch_Point(20, 20, RED);                           //����1
                    TP_Adj_Info_Show(pos_temp[0][0], pos_temp[0][1], pos_temp[1][0], pos_temp[1][1], pos_temp[2][0], pos_temp[2][1], pos_temp[3][0], pos_temp[3][1], fac * 100); //��ʾ����
                    continue;
                }
                tem1 = abs(pos_temp[0][0] - pos_temp[2][0]); //x1-x3
                tem2 = abs(pos_temp[0][1] - pos_temp[2][1]); //y1-y3
                tem1 *= tem1;
                tem2 *= tem2;
                d1 = sqrt(tem1 + tem2); //�õ�1,3�ľ���

                tem1 = abs(pos_temp[1][0] - pos_temp[3][0]); //x2-x4
                tem2 = abs(pos_temp[1][1] - pos_temp[3][1]); //y2-y4
                tem1 *= tem1;
                tem2 *= tem2;
                d2 = sqrt(tem1 + tem2); //�õ�2,4�ľ���
                fac = (float)d1 / d2;
                if (fac < 0.95 || fac > 1.05) //���ϸ�
                {
                    cnt = 0;
                    TP_Drow_Touch_Point(lcddev.width - 20, lcddev.height - 20, WHITE); //�����4
                    TP_Drow_Touch_Point(20, 20, RED);                           //����1
                    TP_Adj_Info_Show(pos_temp[0][0], pos_temp[0][1], pos_temp[1][0], pos_temp[1][1], pos_temp[2][0], pos_temp[2][1], pos_temp[3][0], pos_temp[3][1], fac * 100); //��ʾ����
                    continue;
                }//��ȷ��

                //�Խ������
                tem1 = abs(pos_temp[1][0] - pos_temp[2][0]); //x1-x3
                tem2 = abs(pos_temp[1][1] - pos_temp[2][1]); //y1-y3
                tem1 *= tem1;
                tem2 *= tem2;
                d1 = sqrt(tem1 + tem2); //�õ�1,4�ľ���

                tem1 = abs(pos_temp[0][0] - pos_temp[3][0]); //x2-x4
                tem2 = abs(pos_temp[0][1] - pos_temp[3][1]); //y2-y4
                tem1 *= tem1;
                tem2 *= tem2;
                d2 = sqrt(tem1 + tem2); //�õ�2,3�ľ���
                fac = (float)d1 / d2;
                if (fac < 0.95 || fac > 1.05) //���ϸ�
                {
                    cnt = 0;
                    TP_Drow_Touch_Point(lcddev.width - 20, lcddev.height - 20, WHITE); //�����4
                    TP_Drow_Touch_Point(20, 20, RED);                           //����1
                    TP_Adj_Info_Show(pos_temp[0][0], pos_temp[0][1], pos_temp[1][0], pos_temp[1][1], pos_temp[2][0], pos_temp[2][1], pos_temp[3][0], pos_temp[3][1], fac * 100); //��ʾ����
                    continue;
                }//��ȷ��
                //������
                tp_dev.xfac = (float)(lcddev.width - 40) / (pos_temp[1][0] - pos_temp[0][0]); //�õ�xfac
                //                printf("%f ", tp_dev.xfac);
                tp_dev.xoff = (lcddev.width - tp_dev.xfac * (pos_temp[1][0] + pos_temp[0][0])) / 2; //�õ�xoff

                tp_dev.yfac = (float)(lcddev.height - 40) / (pos_temp[2][1] - pos_temp[0][1]); //�õ�yfac
                //                printf("%f ", tp_dev.yfac);

                tp_dev.yoff = (lcddev.height - tp_dev.yfac * (pos_temp[2][1] + pos_temp[0][1])) / 2; //�õ�yoff
                if (abs(tp_dev.xfac) > 2 || abs(tp_dev.yfac) > 2) //������Ԥ����෴��.
                {
                    cnt = 0;
                    TP_Drow_Touch_Point(lcddev.width - 20, lcddev.height - 20, WHITE); //�����4
                    TP_Drow_Touch_Point(20, 20, RED);                           //����1
                    LCD_ShowString(40, 26, lcddev.width, lcddev.height, 16, "TP Need readjust!");
                    tp_dev.touchtype = !tp_dev.touchtype; //�޸Ĵ�������.
                    if (tp_dev.touchtype) //X,Y��������Ļ�෴
                    {
                        CMD_RDX = 0X90;
                        CMD_RDY = 0XD0;
                    }
                    else                   //X,Y��������Ļ��ͬ
                    {
                        CMD_RDX = 0XD0;
                        CMD_RDY = 0X90;
                    }
                    continue;
                }
                POINT_COLOR = BLUE;
                LCD_Clear(WHITE);//����
                LCD_ShowString(35, 110, lcddev.width, lcddev.height, 16, "Touch Screen Adjust OK!"); //У�����
                delay_ms(500);
                //TP_Save_Adjdata();
                LCD_Clear(WHITE);//����
                return;//У�����
            }
        }
        delay_ms(10);
        outtime++;
        if (outtime > 1000)
        {
            //TP_Get_Adjdata();
            LCD_Clear(WHITE);//����
            break;
        }
    }
}
//��������ʼ��
//����ֵ:0,û�н���У׼
//       1,���й�У׼
//��������ʼ��
//����ֵ:0,û�н���У׼
//       1,���й�У׼
u8 TP_Init(void)
{
    char ubuf[256];
    //ע��,ʱ��ʹ��֮��,��GPIO�Ĳ�������Ч
    //��������֮ǰ,����ʹ��ʱ��.����ʵ���������������
    GPIO_InitTypeDef  GPIO_InitStructure;

#if LCD_TOUCH_SPI_SOFT
    GPIO_InitTypeDef LCD_TOUCH_SPI_GPIO;

    RCC_APB2PeriphClockCmd(RCC_LCD_TOUCH_MISO, ENABLE);
    LCD_TOUCH_SPI_GPIO.GPIO_Pin = LCD_TOUCH_MISO_Pin;
    LCD_TOUCH_SPI_GPIO.GPIO_Speed = GPIO_Speed_50MHz;
    LCD_TOUCH_SPI_GPIO.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(LCD_TOUCH_MISO_GPIO, &LCD_TOUCH_SPI_GPIO);

    RCC_APB2PeriphClockCmd(RCC_LCD_TOUCH_MOSI, ENABLE);
    LCD_TOUCH_SPI_GPIO.GPIO_Pin = LCD_TOUCH_MOSI_Pin;
    LCD_TOUCH_SPI_GPIO.GPIO_Speed = GPIO_Speed_50MHz;
    LCD_TOUCH_SPI_GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LCD_TOUCH_MOSI_GPIO, &LCD_TOUCH_SPI_GPIO);

    RCC_APB2PeriphClockCmd(RCC_LCD_TOUCH_SCK, ENABLE);
    LCD_TOUCH_SPI_GPIO.GPIO_Pin = LCD_TOUCH_SCK_Pin;
    LCD_TOUCH_SPI_GPIO.GPIO_Speed = GPIO_Speed_50MHz;
    LCD_TOUCH_SPI_GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LCD_TOUCH_SCK_GPIO, &LCD_TOUCH_SPI_GPIO);

    GPIO_SetBits(LCD_TOUCH_MOSI_GPIO, LCD_TOUCH_MOSI_Pin);
    GPIO_SetBits(LCD_TOUCH_SCK_GPIO, LCD_TOUCH_SCK_Pin);
#elif LCD_TOUCH_SPI_1
    SPI_InitTypeDef   SPI_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��PB,PF�˿�ʱ��
    /* SPI1 ʱ��ʹ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    /* SPI1 SCK(PA5)��MISO(PA6)��MOSI(PA7) ���� */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         //�����ٶ�50MHZ
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;           //����ģʽ
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* SPI1���� ���� */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   //ȫ˫��
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                        //��ģʽ
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                    //8λ
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                           //ʱ�Ӽ��� ����״̬ʱ��SCK���ֵ͵�ƽ
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                         //ʱ����λ ���ݲ����ӵ�һ��ʱ�ӱ��ؿ�ʼ
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                            //�������NSS
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;  //�����ʿ��� SYSCLK/64
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                   //���ݸ�λ��ǰ
    SPI_InitStructure.SPI_CRCPolynomial = 7;                             //CRC����ʽ�Ĵ�����ʼֵΪ7
    SPI_Init(SPI1, &SPI_InitStructure);

    /* SPI1 ʹ�� */
    SPI_Cmd(SPI1, ENABLE);
#elif LCD_TOUCH_SPI_2
    SPI_InitTypeDef   SPI_InitStructure;
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );//PORTBʱ��ʹ��
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2,  ENABLE );//SPI2ʱ��ʹ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB
    //PB13/14/15����
    GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

    /* SPI2���� ���� */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   //ȫ˫��
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                        //��ģʽ
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                    //8λ
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                           //ʱ�Ӽ��� ����״̬ʱ��SCK���ֵ͵�ƽ
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                         //ʱ����λ ���ݲ����ӵ�һ��ʱ�ӱ��ؿ�ʼ
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                            //�������NSS
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;  //�����ʿ��� SYSCLK/64
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                   //���ݸ�λ��ǰ
    SPI_InitStructure.SPI_CRCPolynomial = 7;                             //CRC����ʽ�Ĵ�����ʼֵΪ7
    SPI_Init(SPI2, &SPI_InitStructure);

    /* SPI2 ʹ�� */
    SPI_Cmd(SPI2, ENABLE);

#endif
    /* SPI ����оƬ��Ƭѡ�������� */
    RCC_APB2PeriphClockCmd(RCC_LCD_TOUCH_TCS, ENABLE); //ʹ��PB,PF�˿�ʱ��
    GPIO_InitStructure.GPIO_Pin = LCD_TOUCH_TCS_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;         //�����ٶ�50MHZ
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;          //�������ģʽ
    GPIO_Init(LCD_TOUCH_TCS_GPIO, &GPIO_InitStructure);

    TP_Read_XY(&tp_dev.x, &tp_dev.y); //��һ�ζ�ȡ��ʼ��

    if (1)
    {
        return 0; //�Ѿ�У׼
    }
    else               //δУ׼
    {
        LCD_Clear(WHITE);//����
        TP_Adjust();  //��ĻУ׼

        sprintf(ubuf, "%8f %8f %4d %4d %d",
                tp_dev.xfac,
                tp_dev.yfac,
                tp_dev.xoff,
                tp_dev.yoff,
                tp_dev.touchtype); //��LCD ID��ӡ��lcd_id���顣
        LCD_ShowString(16, 16, 12, 16 * 10, 10, ubuf);
        //USART_OUT(DEBUG_USART, ubuf);
        //SYS_USART_SendBuf(DEBUG_USART, (unsigned char *)ubuf,255);
        //TP_Save_Adjdata();
    }
    //    TP_Get_Adjdata();
    return 1;
}
void TP_TestAdjust(void)
{
    char ubuf[256];
    LCD_Clear(WHITE);//����
    TP_Adjust();  //��ĻУ׼

    sprintf(ubuf, "%8f %8f %8d %8d %d",
            tp_dev.xfac,
            tp_dev.yfac,
            tp_dev.xoff,
            tp_dev.yoff,
            tp_dev.touchtype); //��LCD ID��ӡ��lcd_id���顣
    LCD_ShowString(0, 0, 16*9, 16 * 5, 16, ubuf);
}
