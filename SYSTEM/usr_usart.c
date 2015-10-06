#include "usr_usart.h"
#include <stdarg.h>
//用于GPS
void USR_UART_IQR(USART_TypeDef *USARTx)
{

}
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
u8 UsrtWifiENTMFlag = 0;

u8 UsrtWifiAtRxBuffer[50];
void ReceiveProtocolUsrtWifiAt(u8 com_data)//串口wifi AT协议接受函数
{
    static u8 RxState = 0;
    static u8 _data_cnt = 0;
    if (RxState == 0 && com_data == '+')
    {
        _data_cnt = 0;
        RxState = 2;
    }
    else if (com_data == 0x0d)
    {
        RxState = 1;
    }
    else if (RxState == 1)
    {
        if (com_data == 0x0a)
        {
            RxState = 0;
            UsrtWifiAtRxBuffer[++_data_cnt] = '\r';
            UsrtWifiAtRxBuffer[++_data_cnt] = '\n';
            UsrtWifiAtRxBuffer[++_data_cnt] = '\0';
            UsrtWifiAtRxBuffer[0] = _data_cnt;
        }
        else
        {
            RxState = 0;
        }
    }
    else if (RxState == 2)
    {
        UsrtWifiAtRxBuffer[++_data_cnt] = com_data;
    }
    else
    {
        RxState = 0;
    }
    return;
}
void ReceiveProtocolUsrtWifiAtENTM(u8 com_data)
{
    static u8 RxBuffer[50];
    static u8 RxState = 0;
    static u8 _data_len = 0, _data_cnt = 0;
    if (RxState == 0 && com_data == 0xAA)//双帧头
    {
        RxState = 1; RxBuffer[0] = com_data;
    }
    else if (RxState == 1 && com_data == 0xAF)//次帧头
    {
        RxState = 2; RxBuffer[1] = com_data;
    }
    else if (RxState == 2 && com_data > 0 && com_data < 0XF1)
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
void ReceiveProtocolReleaseTimeRelayTcp(u8 com_data)//TCP通信接收函数
{
    if (0 == UsrtWifiENTMFlag)
    {
        ReceiveProtocolUsrtWifiAtENTM(com_data);
    }
    else
    {
        ReceiveProtocolUsrtWifiAt(com_data);
    }
    return;
}
#define FRAMEHEADER1 0x5A//双帧头
#define FRAMEHEADER2 0xA5//次帧头
extern void UsrtScreenAnl(u8 *data_buf);
void ReceiveProtocolReleaseTimeRelayUsrtDisplay(u8 com_data)//串口屏接收函数
{
    static u8 RxBuffer[50];
    static u8 RxState = 0;
    static u8 _data_len = 0, _data_cnt = 0;
	Sys_Printf(USART2, "\r\n %d", com_data);
    if (RxState == 0 && com_data == FRAMEHEADER1)
    {
        RxState = 1; RxBuffer[0] = com_data;
    }
    else if (RxState == 1 && com_data == FRAMEHEADER2)
    {
        RxState = 2; RxBuffer[1] = com_data;
    }
    else if (RxState == 2 && com_data < 50)//帧长度
    {
        RxState = 3; RxBuffer[2] = com_data; _data_len = com_data; _data_cnt = 0;
    }
    else if (RxState == 3 && _data_len > 0)//数据
    {
        RxBuffer[3 + _data_cnt++] = com_data;
        if ((--_data_len) == 0)
        {
            RxState = 0;
            UsrtScreenAnl(RxBuffer);
        }
    }
    else
        RxState = 0;
    return;
}

void (*ReceiveProtocol1)(u8 com_data) = ReceiveProtocolReleaseTimeRelayUsrtDisplay;
void (*ReceiveProtocol2)(u8 com_data) = ReceiveProtocolReleaseTimeRelayUsrtDisplay;
void (*ReceiveProtocol3)(u8 com_data) = ReceiveProtocolReleaseTimeRelayTcp;
