#include "G32_HI2c.h"
/*****************************************************
REMAP        |   00    |   01    |   10    |   11    |
*****************************************************|
I2C2_SCL     |   PB10  |                             |
I2C2_SDA     |   PB11  |                             |
*****************************************************|
I2C1_SMBAI   |   PB5                                 |
I2C1_SCL     |   PB6   |  PB8                        |
I2C1_SDA     |   PB7   |  PB9                        |
*****************************************************/
void HI2c1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    I2C_InitTypeDef I2C_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    I2C_DeInit(I2C1);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0x0002;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 400000;

    I2C_Cmd(I2C1, ENABLE); I2C_Init(I2C1, &I2C_InitStructure);
    //研究库代码发现I2C_Init函数执行后I2C就已经使能了，所以无需I2C_Cmd(I2C1, ENABLE)

    NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3 ;  //抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;          //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                             //根据指定的参数初始化VIC寄存器

    I2C_ITConfig(I2C1, I2C_IT_EVT | I2C_IT_ERR, ENABLE);
}
u8 HI2c_data_w[14];
u8 *HI2c_data_r;
u8 HI2c_direction;
u8 HI2c_plan;
u8 HI2c_REG_Address;
u8 HI2c_SlaveAddress;
u8 HI2c_ReadLen;
u8 HI2c_write = 1;
u8 HI2c_read = 0;
void HI2c_Write(u8 SlaveAddress, u8 REG_Address, u8 data)
{
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

    HI2c_direction = HI2c_write;
    HI2c_REG_Address = REG_Address;
    HI2c_data_w[0] = data;
    HI2c_SlaveAddress = SlaveAddress;
    HI2c_plan = 0;
    I2C_GenerateSTART(I2C1, ENABLE);

    while (HI2c_plan != 20);
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
    //delay_ms(5);
}

void HI2c_Read(u8 SlaveAddress, u8 REG_Address, u8 data)
{
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
    HI2c_REG_Address = SlaveAddress;
    HI2c_direction = HI2c_read;
    HI2c_REG_Address = REG_Address;
    HI2c_plan = 0;
    I2C_GenerateSTART(I2C1, ENABLE);
}
void HI2c_ReadBuffer(u8 SlaveAddress, u8 REG_Address, u8 len , u8 *data)
{
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
    HI2c_REG_Address = SlaveAddress;
    HI2c_direction = HI2c_read;
    HI2c_REG_Address = REG_Address;
    HI2c_ReadLen = len;
    HI2c_data_r = data;
    HI2c_plan = 0;
    I2C_GenerateSTART(I2C1, ENABLE);
}
//bool I2c_ReadBuffer(u8 addr, u8 reg, u8 len , u8 *data)
// {
//     if (!I2c_Start())
//         return false;
//     I2c_SendBety(addr);
//     if (!I2c_WaitAck())
//     {
//         I2c_Stop();
//         return false;
//     }
//     I2c_SendBety(reg);
//     I2c_WaitAck();
//     if (!I2c_Start())return false;
//     I2c_SendBety(addr + 1);
//     if (!I2c_WaitAck())
//     {
//         I2c_Stop();
//         return false;
//     }
//     while (len--)
//     {
//         *data++ = I2c_ReceiveBety();
//         if (len < 1)
//             I2c_NoAck();
//         else
//             I2c_Ack();
//     }
//     I2c_Stop();
//     return true;
// }

void I2C1_EV_IRQHandler(void)
{
    switch (HI2c_plan)
    {
    case  0:
        if (I2C_GetFlagStatus(I2C1, I2C_FLAG_SB)) //ev5
        {
            I2C_Send7bitAddress(I2C1, HI2c_SlaveAddress, I2C_Direction_Transmitter);
            HI2c_plan = 1; //REG_Address+w
        }
        break;
    case  1:
        if (I2C_GetFlagStatus(I2C1, I2C_FLAG_ADDR)) //ev6
        {
            if (I2C_GetFlagStatus(I2C1, I2C_FLAG_TRA))
            {
                I2C_SendData(I2C1, HI2c_REG_Address);
                HI2c_plan = 2;
            }
        }
        break;
    case  2:
        if (I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF)) //ev8
        {
            if (HI2c_direction == HI2c_write)
            {
                I2C_SendData(I2C1, HI2c_data_w[0]);    //write data0
                HI2c_plan = 10;
            }
            else
            {
                I2C_GenerateSTART(I2C1, ENABLE);
                HI2c_plan = 11;
            }
        }
        break;
    /******************************************************************************/
    case 10:
        if (I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF)) //ev8_2
        {
            I2C_GenerateSTOP(I2C1, ENABLE);
            HI2c_plan = 20;
        }
        break;
    /******************************************************************************/
    case 11:
        if (I2C_GetFlagStatus(I2C1, I2C_FLAG_SB)) //ev5
        {
            I2C_Send7bitAddress(I2C1, HI2c_SlaveAddress, I2C_Direction_Receiver); HI2c_plan = 12; //REG_Address+r
        }
        break;
    case 12:
        if (I2C_GetFlagStatus(I2C1, I2C_FLAG_ADDR)) //ev6
        {
            if (!I2C_GetFlagStatus(I2C1, I2C_FLAG_TRA)) HI2c_plan = 13;
        }
        break;
    case 13:
        if (I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF)) //ev7
        {
            static char i = 0;
            HI2c_data_r[i] = I2C_ReceiveData(I2C1);
            i++;
            if (i >= (HI2c_ReadLen - 3))
            {
                i = 0;
                HI2c_plan = 18;
            }//read data0
        }
        break;
    case 18: if (I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF)) //ev7
        {
            I2C_AcknowledgeConfig(I2C1, DISABLE);

            HI2c_data_r[HI2c_ReadLen - 3] = I2C_ReceiveData(I2C1); HI2c_plan = 19; //read data5
        }
        break;
    case 19:
        if (I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF)) //ev7
        {
            I2C_AcknowledgeConfig(I2C1, ENABLE);
            I2C_GenerateSTOP(I2C1, ENABLE);
            HI2c_data_r[HI2c_ReadLen - 2] = I2C_ReceiveData(I2C1); //read data6
            while (!I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE));
            HI2c_data_r[HI2c_ReadLen - 1] = I2C_ReceiveData(I2C1); //read data7
            HI2c_plan = 21;
        }
        break;
    }
}

//当然main函数里面会调用24HI2c读或写函数去发送start信号
