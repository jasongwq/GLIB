#include "sys_usart.h"
#include <stdarg.h>
#include "stdio.h"
int Sys_Printf(USART_TypeDef *USARTx, char *Data, ...)
{
    char sprintf_buf[0xff];
    __va_list ap;//����һ��va_list���͵ı������������浥������
    va_start(ap, Data);//ʹargsָ��ɱ�����ĵ�һ������
    int num=0;
		num= vsprintf(sprintf_buf, Data, ap);
    va_end(ap);
    Sys_sPrintf(USARTx, (u8 *)sprintf_buf, num);
    return num;
}
#if 0
/******************************************************
        ��������ת�ַ�������
        char *itoa(int value, char *string, int radix)
        radix=10 ��ʾ��10����  ��ʮ���ƣ�ת�����Ϊ0;
        ����d=-379;
        ִ��  itoa(d, buf, 10); ��
        buf="-379"
**********************************************************/
char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;
    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }
    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }
    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';
        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;
        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }
    /* Null terminate the string. */
    *ptr = 0;
    return string;
} /* NCL_Itoa */
/****************************************************************************
* ��    �ƣ�void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...)
* ��    �ܣ���ʽ�������������
* ��ڲ�����USARTx:  ָ������
            Data��   ��������
            ...:     ��������
* ���ڲ�������
* ˵    ������ʽ�������������
      "\r"  �س���      USART_OUT(USARTx, "abcdefg\r")
            "\n"    ���з�      USART_OUT(USARTx, "abcdefg\r\n")
            "%s"    �ַ���      USART_OUT(USARTx, "�ַ����ǣ�%s","abcdefg")
            "%d"    ʮ����      USART_OUT(USARTx, "a=%d",10)
* ���÷�������
****************************************************************************/
void vSys_Printf(USART_TypeDef *USARTx, char *Data, ...)
{
    const char *s;
    int d;
    char buf[16];
    va_list ap;
    va_start(ap, Data);
    while (*Data != 0)                                        //�ж��Ƿ񵽴��ַ���������
    {
        if (*Data == 0x5c)                                    //'\'
            switch (*++Data)
            {
            case 'r':                                     //�س���
                Sys_Putchar(USARTx, 0x0d);
                Data++;
                break;
            case 'n':                                     //���з�
                Sys_Putchar(USARTx, 0x0a);
                Data++;
                break;
            default:
                Data++;
                break;
            }
        else if (*Data == '%')
            switch (*++Data)
            {
            case 's':                                         //�ַ���
                s = va_arg(ap, const char *);
                for ( ; *s; s++)
                {
                    Sys_Putchar(USARTx, *s);
                    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
                }
                Data++;
                break;
            case 'd':                                         //ʮ����
                d = va_arg(ap, int);
                itoa(d, buf, 10);
                for (s = buf; *s; s++)
                {
                    Sys_Putchar(USARTx, *s);
                    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
                }
                Data++;
                break;
            default:
                Data++;
                break;
            }
        else Sys_Putchar(USARTx, *Data++);
        //while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
    }
}
#endif
u8 TxBuffer[EN_USART_ + EN_USART2_ + EN_USART3_][0xff]; //���ͻ���
u8 TxCount [EN_USART_ + EN_USART2_ + EN_USART3_] = {0}; //����β

void SYS_UART_IQR(USART_TypeDef *USARTx)
{
    static u8 TxCounter[3] = {0};//��ǰ����
    static u8 RxBuffer[50];

    static u8 RxState = 0;
    if (USARTx->SR & USART_IT_ORE)
    {
        USARTx->SR;
    }
    //�����ж�
    if ((USARTx->SR & (1 << 7)) && (USARTx->CR1 & USART_CR1_TXEIE)) //if(USART_GetITStatus(USARTx,USART_IT_TXE)!=RESET)
    {
        int USARTn;
        if (USARTx == USART1)
        {
            USARTn = EN_USART_ - 1;
        }
        else if (USARTx == USART2)
        {
            USARTn = EN_USART_ + EN_USART2_ - 1;
        }
        else if (USARTx == USART3)
        {
            USARTn = EN_USART_ + EN_USART2_ + EN_USART3_ - 1;
        }
        USARTx->DR = TxBuffer[USARTn][TxCounter[USARTn]++]; //дDR����жϱ�־
        if (TxCounter[USARTn] == TxCount[USARTn])
            USARTx->CR1 &= ~USART_CR1_TXEIE;        //�ر�TXE�ж�//USART_ITConfig(USARTx,USART_IT_TXE,DISABLE);
    }
    //�����ж� (���ռĴ����ǿ�)
    if (USARTx->SR & (1 << 5)) //if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
    {
        u8 com_data = USARTx->DR;
        static u8 _data_len = 0, _data_cnt = 0;
        if (RxState == 0 && com_data == 0xAA)
        {
            RxState = 1;
            RxBuffer[0] = com_data;
        }
        else if (RxState == 1 && com_data == 0xAF)
        {
            RxState = 2;
            RxBuffer[1] = com_data;
        }
        else if (RxState == 2 && com_data > 0 && com_data < 0XF1)
        {
            RxState = 3;
            RxBuffer[2] = com_data;
        }
        else if (RxState == 3 && com_data < 50)
        {
            RxState = 4;
            RxBuffer[3] = com_data;
            _data_len = com_data;
            _data_cnt = 0;
        }
        else if (RxState == 4 && _data_len > 0)
        {
            _data_len--;
            RxBuffer[4 + _data_cnt++] = com_data;
            if (_data_len == 0)
                RxState = 5;
        }
        else if (RxState == 5)
        {
            extern void Data_Receive_Anl(u8 * data_buf, u8 num);
            RxState = 0;
            RxBuffer[4 + _data_cnt] = com_data;
            Data_Receive_Anl(RxBuffer, _data_cnt + 5);
        }
        else
            RxState = 0;
    }
}
/**************************ʵ�ֺ���********************************************
*******************************************************************************/
uint8_t Sys_Putchar(USART_TypeDef *USARTx, unsigned char DataToSend)
{
    int USARTn;
    if (USARTx == USART1)
    {
        USARTn = EN_USART_ - 1;
    }
    else if (USARTx == USART2)
    {
        USARTn = EN_USART_ + EN_USART2_ - 1;
    }
    else if (USARTx == USART3)
    {
        USARTn = EN_USART_ + EN_USART2_ + EN_USART3_ - 1;
    }
    TxBuffer[USARTn][TxCount[USARTn]++] = DataToSend;
    USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
    return DataToSend;
}
uint8_t *Sys_sPrintf(USART_TypeDef *USARTx, unsigned char *DataToSend, unsigned char num)
{
    int USARTn;
    if (USARTx == USART1)
    {
        USARTn = EN_USART_ - 1;
#if EN_USART1_DMA_T
        TxCount[USARTn] = 0;
#endif
        for (int i = 0; i < num; i++)
            TxBuffer[USARTn][TxCount[USARTn]++] = *(DataToSend + i);
#if EN_USART1_IQR_T
        USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
#endif
    }
    else if (USARTx == USART2)
    {
        USARTn = EN_USART_ + EN_USART2_ - 1;
#if EN_USART2_DMA_T
        TxCount[USARTn] = 0;
#endif
        for (int i = 0; i < num; i++)
            TxBuffer[USARTn][TxCount[USARTn]++] = *(DataToSend + i);
#if EN_USART2_IQR_T
        USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
#endif
    }
    else if (USARTx == USART3)
    {
        USARTn = EN_USART_ + EN_USART2_ + EN_USART3_ - 1;
#if EN_USART3_DMA_T
        TxCount[USARTn] = 0;
#endif
        for (int i = 0; i < num; i++)
            TxBuffer[USARTn][TxCount[USARTn]++] = *(DataToSend + i);
#if EN_USART3_IQR_T
        USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
#endif
    }
    return DataToSend;
}



