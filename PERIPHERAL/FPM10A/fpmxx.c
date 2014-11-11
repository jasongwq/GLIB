#include "MAIN.h"
//#include "USART.h"
#include "Driver_UART.h"                // ::Drivers:UART
/*
Stm32 F4
*/

volatile unsigned char FPMXX_RECEICE_BUFFER[64];

//FINGERPRINT通信协议定义
unsigned char FPMXX_Pack_Head[6] = {0xEF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF}; //协议包头
unsigned char FPMXX_Get_Img[6] =   {0x01, 0x00, 0x03, 0x01, 0x00, 0x05}; //获得指纹图像
unsigned char FPMXX_Get_Templete_Count[6] =   {0x01, 0x00, 0x03, 0x1D, 0x00, 0x21}; //获得模版总数
unsigned char FP_Search[11] =     {0x01, 0x00, 0x08, 0x04, 0x01, 0x00, 0x00, 0x03, 0xA1, 0x00, 0xB2}; //搜索指纹搜索范围0 - 929
unsigned char FP_Img_To_Buffer[7] =  {0x01, 0x00, 0x04, 0x02, 0x01, 0x00, 0x08}; //将图像放入到BUFFER
unsigned char FP_Reg_Model[6] =       {0x01, 0x00, 0x03, 0x05, 0x00, 0x09}; //将BUFFER1跟BUFFER2合成特征模版
unsigned char FP_Delet_All_Model[6] = {0x01, 0x00, 0x03, 0x0d, 0x00, 0x11}; //删除指纹模块里所有的模版
volatile unsigned char FP_Save_Finger[9] =   {0x01, 0x00, 0x06, 0x06, 0x01, 0x00, 0x0B, 0x00, 0x19}; //将BUFFER1中的特征码存放到指定的位置
volatile unsigned char FP_Delete_Model[10] = {0x01, 0x00, 0x07, 0x0C, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00}; //删除指定的模版
//volatile unsigned char FINGER_NUM;

#define Driver_UARTx Driver_UART2
extern ARM_DRIVER_UART Driver_UARTx;
//#define FPMXX_USART_Send_Byte(x) Send_Hex(FPMXX_USART,x)
#define FPMXX_USART_Send_Byte(x) Driver_UARTx.WriteData((uint8_t *)&x,1)
/*------------------ FINGERPRINT命令字 --------------------------*/
void FPMXX_Cmd_Send_Pack_Head(void) //发送包头
{
    Driver_UARTx.WriteData(FPMXX_Pack_Head, 6);
}

//FINGERPRINT_获得指纹图像命令
void FPMXX_Cmd_Get_Img(void)
{
    Driver_UARTx.WriteData(FPMXX_Pack_Head, 6);
    //delay_ms(1);
    Driver_UARTx.WriteData(FPMXX_Get_Img, 6);
}

//讲图像转换成特征码存放在Buffer1中
void FINGERPRINT_Cmd_Img_To_Buffer(int BufferID)
{
    Driver_UARTx.WriteData(FPMXX_Pack_Head, 6);
    //delay_ms(1);
	FP_Img_To_Buffer[4]=BufferID;
	FP_Img_To_Buffer[6]=BufferID+7;
    Driver_UARTx.WriteData(FP_Img_To_Buffer, 7);
}


//将BUFFER1 跟 BUFFER2 中的特征码合并成指纹模版
void FINGERPRINT_Cmd_Reg_Model(void)
{
    unsigned char i;
    for (i = 0; i < 6; i++) //包头
        FPMXX_USART_Send_Byte(FPMXX_Pack_Head[i]);
    for (i = 0; i < 6; i++) //命令合并指纹模版
        FPMXX_USART_Send_Byte(FP_Reg_Model[i]);
}

//删除指纹模块里的所有指纹模版
void FINGERPRINT_Cmd_Delete_All_Model(void)
{
    int i;
    for (i = 0; i < 6; i++) //包头
        FPMXX_USART_Send_Byte(FPMXX_Pack_Head[i]);
    for (i = 0; i < 6; i++) //命令合并指纹模版
        FPMXX_USART_Send_Byte(FP_Delet_All_Model[i]);
}

//删除指纹模块里的指定指纹模版
void FINGERPRINT_Cmd_Delete_Model(unsigned int uiID_temp)
{
    volatile unsigned int uiSum_temp = 0;
    unsigned char i;

    FP_Delete_Model[4] = (uiID_temp & 0xFF00) >> 8;
    FP_Delete_Model[5] = (uiID_temp & 0x00FF);

    for (i = 0; i < 8; i++)
        uiSum_temp = uiSum_temp + FP_Delete_Model[i];

    //UART0_Send_Byte(uiSum_temp);

    FP_Delete_Model[8] = (uiSum_temp & 0xFF00) >> 8;
    FP_Delete_Model[9] = uiSum_temp & 0x00FF;


    for (i = 0; i < 6; i++) //包头
        FPMXX_USART_Send_Byte(FPMXX_Pack_Head[i]);

    for (i = 0; i < 10; i++) //命令合并指纹模版
        FPMXX_USART_Send_Byte(FP_Delete_Model[i]);
}




//获得指纹模板数量
void FINGERPRINT_Cmd_Get_Templete_Num(void)
{

    Driver_UARTx.WriteData(FPMXX_Get_Templete_Count, 6);
}

void FINGERPRINT_Cmd_Search_Finger(int BufferID,int StartPage,int PageNum)
{
	int sum=0;
	Driver_UARTx.WriteData(FPMXX_Pack_Head, 6);
  //delay_ms(1);
	FP_Search[4]=BufferID;
	FP_Search[5]=StartPage>>8;
	FP_Search[6]=StartPage;
	FP_Search[7]=PageNum>>8;
	FP_Search[8]=PageNum;
	for (int i = 0; i < 9; i++) //计算校验和
        sum = sum + FP_Search[i];
	FP_Search[9]=sum>>8;
	FP_Search[10]=sum;
	Driver_UARTx.WriteData(FP_Search, 11);
}

void FINGERPRINT_Cmd_Save_Finger( unsigned char ucH_Char, unsigned char ucL_Char )
{
    unsigned long temp = 0;
    unsigned char i;

    //           SAVE_FINGER[9]={0x01,0x00,0x06,0x06,0x01,0x00,0x0B,0x00,0x19};//将BUFFER1中的特征码存放到指定的位置

    FP_Save_Finger[5] = ucH_Char;
    FP_Save_Finger[6] = ucL_Char;

    for (i = 0; i < 7; i++) //计算校验和
        temp = temp + FP_Save_Finger[i];

    FP_Save_Finger[7] = (temp & 0x00FF00) >> 8; //存放校验数据
    FP_Save_Finger[8] = temp & 0x0000FF;

    FPMXX_Cmd_Send_Pack_Head(); //发送通信协议包头

    for (i = 0; i < 9; i++)
        FPMXX_USART_Send_Byte(FP_Save_Finger[i]);      //发送命令 将图像转换成 特征码 存放在 CHAR_buffer1
}
//接收反馈数据缓冲
void FPMXX_Receive_Data(unsigned char ucLength)
{
    Driver_UARTx.ReadData ((uint8_t *)FPMXX_RECEICE_BUFFER, ucLength);
}
/*
//指纹添加新用户
unsigned char FP_add_new_user(unsigned char ucH_user,unsigned char ucL_user)
{

               do {
                    FINGERPRINT_Cmd_Get_Img(); //获得指纹图像
                    FINGERPRINT_Recevice_Data(12); //接收12个长度的反馈码
                  }
               while ( UART1_FINGERPRINT_RECEVICE_BUFFER[9]!=0x0 ); //检测是否成功的按了指纹


                 FINGERPRINT_Cmd_Img_To_Buffer1(); //将图像转换成特征码存放在Buffer1中
                 FINGERPRINT_Recevice_Data(12);   //接收12个长度的反馈码

                do{
                     FINGERPRINT_Cmd_Get_Img(); //获得指纹图像
                     FINGERPRINT_Recevice_Data(12); //接收12个长度的反馈码
                 }
                 while( UART1_FINGERPRINT_RECEVICE_BUFFER[9]!=0x0 );

                 FINGERPRINT_Cmd_Img_To_Buffer2(); //将图像转换成特征码存放在Buffer2中
                 FINGERPRINT_Recevice_Data(12);   //接收12个长度的反馈码


                 FP_Cmd_Reg_Model();//转换成特征码
                 FINGERPRINT_Recevice_Data(12);

                 FINGERPRINT_Cmd_Save_Finger(ucH_user,ucL_user);
                 FINGERPRINT_Recevice_Data(12);

                 return 0;
}
*/
