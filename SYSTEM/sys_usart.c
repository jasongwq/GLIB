#include "sys_usart.h"
#include "usr_usart.h"
#include <stdarg.h>
#include "stdio.h"
#include "gpio.h"

int Sys_Printf(USART_TypeDef *USARTx, const char *Data, ...)
{
    char sprintf_buf[0xff];
    __va_list ap;//����һ��va_list���͵ı������������浥������
    va_start(ap, Data);//ʹargsָ��ɱ�����ĵ�һ������
    int num = 0;
    num = vsprintf(sprintf_buf, Data, ap);
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
        ReceiveProtocol1(USARTx->DR);
    }
}
void SysUartTxIqr(USART_TypeDef *USARTx)
{
    static u8 TxCounter[3] = {0};//��ǰ����
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
}
void SysUart1RxIqr(void)
{
    //�����ж� (���ռĴ����ǿ�)
    if (USART1->SR & (1 << 5)) //if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
    {
        ReceiveProtocol1(USART1->DR);
    }
}
void SysUart2RxIqr(void)
{
    //�����ж� (���ռĴ����ǿ�)
    if (USART2->SR & (1 << 5)) //if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
    {
        ReceiveProtocol2(USART2->DR);
    }
}
void SysUart3RxIqr(void)
{
    //�����ж� (���ռĴ����ǿ�)
    if (USART3->SR & (1 << 5)) //if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
    {
        ReceiveProtocol3(USART3->DR);
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
		else
		{
			return 0;
		}
    return DataToSend;
}



