#include "dac.h"

#define _DAC_Channel_1      //I/O PA.4
#define _DAC_Channel_2      //I/O PA.5
/*
//DAC的转换速度最快是250K左
8bit/12bit
端口要设置为模拟输入模式
一但使能DACx通道之后，相应的GPIO引脚（PA4或者PA5）会自动与DAC的模拟输出相连，设置为输入，是为了避免额外的干扰。
*/
//DAC 代码
//修改日期:2012/9/8
//版本：V1.0

//DAC通道1输出初始化
void Dac1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitType;
    /* Check the parameters */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );    //使能PORTA通道时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );      //使能DAC通道时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;            // 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;        //模拟输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_4)  ;                   //PX.x 输出高

    DAC_InitType.DAC_Trigger = DAC_Trigger_None;            //不使用触发功能 TEN1=0
    DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None; //不使用波形发生
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0; //屏蔽、幅值设置
    DAC_InitType.DAC_OutputBuffer = DAC_OutputBuffer_Enable ;        //DAC1输出缓存关闭 BOFF1=1
    DAC_Init(DAC_Channel_1, &DAC_InitType);                             //初始化DAC通道1

    DAC_Cmd(DAC_Channel_1, ENABLE);          //使能DAC1
    DAC_SetChannel1Data(DAC_Align_12b_R, 3000); //12位右对齐数据格式设置DAC值
}
//DAC通道1输出初始化
void Dac2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitType;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );    //使能PORTA通道时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );      //使能DAC通道时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;            // 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //模拟输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_5)  ;                       //PX.x 输出高

    DAC_InitType.DAC_Trigger = DAC_Trigger_None;                        //不使用触发功能 TEN1=0
    DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None;        //不使用波形发生
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0; //屏蔽、幅值设置
    DAC_InitType.DAC_OutputBuffer = DAC_OutputBuffer_Enable ;            //DAC1输出缓存关闭 BOFF1=1
    DAC_Init(DAC_Channel_2, &DAC_InitType);                                         //初始化DAC通道1

    DAC_Cmd(DAC_Channel_2, ENABLE);          //使能DAC1
    DAC_SetChannel2Data(DAC_Align_12b_R, 0); //12位右对齐数据格式设置DAC值
    DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);
}

//设置通道1输出电压
//vol:0~3300,代表0~3.3V
void Dac1_Set_Vol(u16 vol)
{
    float temp = vol;
    temp /= 1000;
    temp = temp * 4096 / 3.3;
    DAC_SetChannel1Data(DAC_Align_12b_R, temp); //12位右对齐数据格式设置DAC值
}
void Dac2_Set_Vol(u16 vol)
{
    float temp = vol;
    temp /= 1000;
    temp = temp * 4096 / 3.3;
    DAC_SetChannel2Data(DAC_Align_12b_R, temp); //12位右对齐数据格式设置DAC值
}

void DAC_voice(u8 *dac_temp)//低位在前
{
    u16 temp;
    u8 i;
    for (i = 0; i < 32; i += 2)
    {
        temp = dac_temp[i] + dac_temp[i + 1];
        DAC_SetChannel1Data(DAC_Align_12b_R, temp); //12位右对齐数据格式设置DAC值
    }
}

