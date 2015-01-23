#include "dac.h"

#define _DAC_Channel_1      //I/O PA.4
#define _DAC_Channel_2      //I/O PA.5
/*
//DAC��ת���ٶ������250K��
8bit/12bit
�˿�Ҫ����Ϊģ������ģʽ
һ��ʹ��DACxͨ��֮����Ӧ��GPIO���ţ�PA4����PA5�����Զ���DAC��ģ���������������Ϊ���룬��Ϊ�˱������ĸ��š�
*/
//DAC ����
//�޸�����:2012/9/8
//�汾��V1.0

//DACͨ��1�����ʼ��
void Dac1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitType;
    /* Check the parameters */
    assert_param(IS_DAC_CHANNEL(DAC_Channel));

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );    //ʹ��PORTAͨ��ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );      //ʹ��DACͨ��ʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;            // �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;        //ģ������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_4)  ;                   //PX.x �����

    DAC_InitType.DAC_Trigger = DAC_Trigger_None;            //��ʹ�ô������� TEN1=0
    DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None; //��ʹ�ò��η���
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0; //���Ρ���ֵ����
    DAC_InitType.DAC_OutputBuffer = DAC_OutputBuffer_Disable ;        //DAC1�������ر� BOFF1=1
    DAC_Init(DAC_Channel_1, &DAC_InitType);                             //��ʼ��DACͨ��1

    DAC_Cmd(DAC_Channel_1, ENABLE);          //ʹ��DAC1
    DAC_SetChannel1Data(DAC_Align_12b_R, 3000); //12λ�Ҷ������ݸ�ʽ����DACֵ
}
//DACͨ��1�����ʼ��
void Dac2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    DAC_InitTypeDef DAC_InitType;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );    //ʹ��PORTAͨ��ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );      //ʹ��DACͨ��ʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;            // �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  //ģ������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_5)  ;                       //PX.x �����

    DAC_InitType.DAC_Trigger = DAC_Trigger_Software;                        //��ʹ�ô������� TEN1=0
    DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None;        //��ʹ�ò��η���
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0; //���Ρ���ֵ����
    DAC_InitType.DAC_OutputBuffer = DAC_OutputBuffer_Disable ;            //DAC1�������ر� BOFF1=1
    DAC_Init(DAC_Channel_2, &DAC_InitType);                                         //��ʼ��DACͨ��1

    DAC_Cmd(DAC_Channel_2, ENABLE);          //ʹ��DAC1
    DAC_SetChannel2Data(DAC_Align_12b_R, 0); //12λ�Ҷ������ݸ�ʽ����DACֵ
    DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);
}

//����ͨ��1�����ѹ
//vol:0~3300,����0~3.3V
void Dac1_Set_Vol(u16 vol)
{
    float temp = vol;
    temp /= 1000;
    temp = temp * 4096 / 3.3;
    DAC_SetChannel1Data(DAC_Align_12b_R, temp); //12λ�Ҷ������ݸ�ʽ����DACֵ
}
void Dac2_Set_Vol(u16 vol)
{
    float temp = vol;
    temp /= 1000;
    temp = temp * 4096 / 3.3;
    DAC_SetChannel2Data(DAC_Align_12b_R, temp); //12λ�Ҷ������ݸ�ʽ����DACֵ
}

void DAC_voice(u8 *dac_temp)//��λ��ǰ
{
    u16 temp;
    u8 i;
    for (i = 0; i < 32; i += 2)
    {
        temp = dac_temp[i] + dac_temp[i + 1];
        DAC_SetChannel1Data(DAC_Align_12b_R, temp); //12λ�Ҷ������ݸ�ʽ����DACֵ
    }
}

