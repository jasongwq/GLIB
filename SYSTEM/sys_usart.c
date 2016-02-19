#include "sys_usart.h"
#include "usr_usart.h"
#include <stdarg.h>
#include "stdio.h"
#include "gpio.h"

int Sys_Printf(USART_TypeDef *USARTx, const char *Data, ...)
{
    char sprintf_buf[0xff];
    __va_list ap;//定义一个va_list类型的变量，用来储存单个参数
    va_start(ap, Data);//使args指向可变参数的第一个参数
    int num = 0;
    num = vsprintf(sprintf_buf, Data, ap);
    va_end(ap);
    Sys_sPrintf(USARTx, (u8 *)sprintf_buf, num);
    return num;
}
#if 0
/******************************************************
        整形数据转字符串函数
        char *itoa(int value, char *string, int radix)
        radix=10 标示是10进制  非十进制，转换结果为0;
        例：d=-379;
        执行  itoa(d, buf, 10); 后
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
* 名    称：void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...)
* 功    能：格式化串口输出函数
* 入口参数：USARTx:  指定串口
            Data：   发送数组
            ...:     不定参数
* 出口参数：无
* 说    明：格式化串口输出函数
      "\r"  回车符      USART_OUT(USARTx, "abcdefg\r")
            "\n"    换行符      USART_OUT(USARTx, "abcdefg\r\n")
            "%s"    字符串      USART_OUT(USARTx, "字符串是：%s","abcdefg")
            "%d"    十进制      USART_OUT(USARTx, "a=%d",10)
* 调用方法：无
****************************************************************************/
void vSys_Printf(USART_TypeDef *USARTx, char *Data, ...)
{
    const char *s;
    int d;
    char buf[16];
    va_list ap;
    va_start(ap, Data);
    while (*Data != 0)                                        //判断是否到达字符串结束符
    {
        if (*Data == 0x5c)                                    //'\'
            switch (*++Data)
            {
            case 'r':                                     //回车符
                Sys_Putchar(USARTx, 0x0d);
                Data++;
                break;
            case 'n':                                     //换行符
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
            case 's':                                         //字符串
                s = va_arg(ap, const char *);
                for ( ; *s; s++)
                {
                    Sys_Putchar(USARTx, *s);
                    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
                }
                Data++;
                break;
            case 'd':                                         //十进制
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
u8 TxBuffer[EN_USART_ + EN_USART2_ + EN_USART3_][0xff]; //发送缓存
u8 TxCount [EN_USART_ + EN_USART2_ + EN_USART3_] = {0}; //发送尾

void SYS_UART_IQR(USART_TypeDef *USARTx)
{
    static u8 TxCounter[3] = {0};//当前发送
    if (USARTx->SR & USART_IT_ORE)
    {
        USARTx->SR;
    }
    //发送中断
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
        USARTx->DR = TxBuffer[USARTn][TxCounter[USARTn]++]; //写DR清除中断标志
        if (TxCounter[USARTn] == TxCount[USARTn])
            USARTx->CR1 &= ~USART_CR1_TXEIE;        //关闭TXE中断//USART_ITConfig(USARTx,USART_IT_TXE,DISABLE);
    }
    //接收中断 (接收寄存器非空)
    if (USARTx->SR & (1 << 5)) //if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
    {
        ReceiveProtocol1(USARTx->DR);
    }
}
void SysUartTxIqr(USART_TypeDef *USARTx)
{
    static u8 TxCounter[3] = {0};//当前发送
    if (USARTx->SR & USART_IT_ORE)
    {
        USARTx->SR;
    }
    //发送中断
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
        USARTx->DR = TxBuffer[USARTn][TxCounter[USARTn]++]; //写DR清除中断标志
        if (TxCounter[USARTn] == TxCount[USARTn])
            USARTx->CR1 &= ~USART_CR1_TXEIE;        //关闭TXE中断//USART_ITConfig(USARTx,USART_IT_TXE,DISABLE);
    }
}
void SysUart1RxIqr(void)
{
    //接收中断 (接收寄存器非空)
    if (USART1->SR & (1 << 5)) //if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
    {
        ReceiveProtocol1(USART1->DR);
    }
}
void SysUart2RxIqr(void)
{
    //接收中断 (接收寄存器非空)
    if (USART2->SR & (1 << 5)) //if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
    {
        ReceiveProtocol2(USART2->DR);
    }
}
void SysUart3RxIqr(void)
{
    //接收中断 (接收寄存器非空)
    if (USART3->SR & (1 << 5)) //if(USART_GetITStatus(USARTx, USART_IT_RXNE) != RESET)
    {
        ReceiveProtocol3(USART3->DR);
    }
}



/**************************实现函数********************************************
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



