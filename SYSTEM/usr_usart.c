#include "usr_usart.h"
#include <stdarg.h>
//用于GPS
void USR_UART_IQR(USART_TypeDef *USARTx)
{

}
void ReceiveProtocolAno(u8 com_data);
void ReceiveProtocolReleaseTimeRelay(u8 com_data);

void (*ReceiveProtocol)(u8 com_data) = ReceiveProtocolReleaseTimeRelay;

void ReceiveProtocolAno(u8 com_data)
{
    static u8 RxBuffer[50];
    static u8 RxState = 0;
    static u8 _data_len = 0, _data_cnt = 0;
    if (RxState == 0 && com_data == 0xAA)
    {
        RxState = 1; RxBuffer[0] = com_data;
    }
    else if (RxState == 1 && com_data == 0xAF)//双帧头
    {
        RxState = 2; RxBuffer[1] = com_data;
    }
    else if (RxState == 2 && com_data > 0 && com_data < 0XF1)//次帧头
    {
        RxState = 3; RxBuffer[2] = com_data;
    }
    else if (RxState == 3 && com_data < 50)//帧长度
    {
        RxState = 4; RxBuffer[3] = com_data; _data_len = com_data; _data_cnt = 0;
    }
    else if (RxState == 4 && _data_len > 0)//数据
    {
        _data_len--; RxBuffer[4 + _data_cnt++] = com_data; if (_data_len == 0)RxState = 5;
    }
    else if (RxState == 5)//帧尾
    {
        extern void Data_Receive_Anl(u8 * data_buf, u8 num);
        RxState = 0; RxBuffer[4 + _data_cnt] = com_data;
        Data_Receive_Anl(RxBuffer, _data_cnt + 5);
    }
    else
        RxState = 0;
}
void ReceiveProtocolReleaseTimeRelay(u8 com_data)
{
    static u8 RxBuffer[50];
    static u8 RxState = 0;
    static u8 _data_len = 0, _data_cnt = 0;
    if (RxState == 0 && com_data == 0xAA)
    {
        RxState = 1; RxBuffer[0] = com_data;
    }
    else if (RxState == 1 && com_data == 0xAF)//双帧头
    {
        RxState = 2; RxBuffer[1] = com_data;
    }
    else if (RxState == 2 && com_data > 0 && com_data < 0XF1)//次帧头
    {
        RxState = 3; RxBuffer[2] = com_data;
    }
    else if (RxState == 3 && com_data < 50)//帧长度
    {
        RxState = 4; RxBuffer[3] = com_data; _data_len = com_data; _data_cnt = 0;
    }
    else if (RxState == 4 && _data_len > 0)//数据
    {
        _data_len--; RxBuffer[4 + _data_cnt++] = com_data; if (_data_len == 0)RxState = 5;
    }
    else if (RxState == 5)//帧尾
    {
        extern void Data_Receive_Anl(u8 * data_buf, u8 num);
        RxState = 0; RxBuffer[4 + _data_cnt] = com_data;
        Data_Receive_Anl(RxBuffer, _data_cnt + 5);
    }
    else
        RxState = 0;
}

