#include "adc.h"
#include "delay.h"
#include "G32_timer.h"
#include "stm32_config.h"
/***ADC***/
/***************************************************|
| Channel   |    ADC1     |  ADC2      |  ADC3      |
|***********|*************|************|************|
| Channel0  | A0          |  A0        |  A0        |
| Channel1  | A1          |  A1        |  A1        |
| Channel2  | A2          |  A2        |  A2        |
| Channel3  | A3          |  A3        |  A3        |
| Channel4  | A4          |  A4        |  F6        |
| Channel5  | A5          |  A5        |  F7        |
| Channel6  | A6          |  A6        |  F8        |
| Channel7  | A7          |  A7        |  F9        |
| Channel8  | B0          |  B0        |  F10       |
| Channel9  | B1          |  B1        |            |
| Channel10 | C0          |  C0        |  C0        |
| Channel11 | C1          |  C1        |  C1        |
| Channel12 | C2          |  C2        |  C2        |
| Channel13 | C3          |  C3        |  C3        |
| Channel14 | C4          |  C4        |            |
| Channel15 | C5          |  C5        |            |
| Channel16 | �¶ȴ�����  |            |            |
| Channel17 | �ڲ��ο���ѹ|            |            |
|***************************************************/
/*ADC ����*/
/********************************************************************************
ADCʹ��DMA ����������
����ADת����AD ÿ��ת����ɺ���DMA ��������ת��ֵ��ADC���ݼĴ�����ADC_DR��
��ת�Ƶ�����ADC_ConvertedValue����DMA��ɺ���main��ʹ�õģ�����ADC ת���Ľ����
********************************************************************************/

#define ADC1_DR_Address    ((u32)0x40012400+0x4c)   //�궨��   ADC1 ת���󱣴����ݵĵ�ַ
//0x4c        ADC1_DR �ľ����ַ      STM32�ο��ֲ� P178
//0x40012400  ADC �ļĴ����׵�ַ      STM32�ο��ֲ� P28
__IO uint16_t ADC_ConvertedValue[(\
                                  (ADC1_Channel00ON >> 5) + \
                                  (ADC1_Channel01ON >> 5) + \
                                  (ADC1_Channel02ON >> 5) + \
                                  (ADC1_Channel03ON >> 5) + \
                                  (ADC1_Channel04ON >> 5) + \
                                  (ADC1_Channel05ON >> 5) + \
                                  (ADC1_Channel06ON >> 5) + \
                                  (ADC1_Channel07ON >> 5) + \
                                  (ADC1_Channel08ON >> 5) + \
                                  (ADC1_Channel09ON >> 5) + \
                                  (ADC1_Channel10ON >> 5) + \
                                  (ADC1_Channel11ON >> 5) + \
                                  (ADC1_Channel12ON >> 5) + \
                                  (ADC1_Channel13ON >> 5) + \
                                  (ADC1_Channel14ON >> 5) + \
                                  (ADC1_Channel15ON >> 5) + \
                                  (ADC1_Channel16ON >> 5) + \
                                  (ADC1_Channel17ON >> 5)   \
                                 )];  //����һ������

/********************************************************************************************
������������������ݵ���˼��
core_cm3.h ������ __IO��
#defines __IO volatile     !< defines 'read / write' permissions
volatile ��Ϊָ��ؼ���,ȷ������ָ�������������Ż���ʡ��,��Ҫ��ÿ��ֱ�Ӷ�ֵ.
stdint.h   ������ uint16_t��
typedef  unsigned short int  uint16_t;
ADC_ConvertedValue   ������
********************************************************************************************/
/*
* ��������ADC1_GPIO_Config
* ����  ��ʹ��ADC1��DMA1��ʱ�ӣ���ʼ��PC.01
* ����  : ��
* ���  ����
* ����  ���ڲ�����
*/
static void ADC1_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; //����ṹ��
#if \
    ADC1_Channel00ON||\
    ADC1_Channel01ON||\
    ADC1_Channel02ON||\
    ADC1_Channel03ON||\
    ADC1_Channel04ON||\
    ADC1_Channel05ON||\
    ADC1_Channel06ON||\
    ADC1_Channel07ON
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = 0;
#if ADC1_Channel00ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_0;
#endif
#if ADC1_Channel01ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_1;
#endif
#if ADC1_Channel02ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_2;
#endif
#if ADC1_Channel03ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_3;
#endif
#if ADC1_Channel04ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_4;
#endif
#if ADC1_Channel05ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_5;
#endif
#if ADC1_Channel06ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_6;
#endif
#if ADC1_Channel07ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_7;
#endif

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
#if \
    ADC1_Channel08ON||\
    ADC1_Channel09ON
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = 0;
#if ADC1_Channel08ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_0;
#endif
#if ADC1_Channel09ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_1;
#endif

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
#if \
    ADC1_Channel01ON||\
    ADC1_Channel02ON||\
    ADC1_Channel03ON||\
    ADC1_Channel04ON||\
    ADC1_Channel05ON
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = 0;
#if ADC1_Channel10ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_0;
#endif
#if ADC1_Channel11ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_1;
#endif
#if ADC1_Channel12ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_2;
#endif
#if ADC1_Channel13ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_3;
#endif
#if ADC1_Channel14ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_4;
#endif
#if ADC1_Channel15ON
    GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_5;
#endif

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
}

/* ��������ADC1_Mode_Config
* ����  ������ADC1�Ĺ���ģʽΪMDAģʽ
* ����  : ��
* ���  ����
* ����  ���ڲ�����
*/
static void ADC1_Mode_Config(void)
{
    ADC_InitTypeDef ADC_InitStructure;
#if ADC1_DMAIRQ_ENABLE
    NVIC_InitTypeDef NVIC_InitStructure;
#endif
#if ADC1_DMA
    DMA_InitTypeDef DMA_InitStructure;        //���� DMA �ṹ��
    /***********************DMA*********************************/
    /* Enable DMA clock */                            //��DMA ʱ��
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//ע������ʱ����

    /* DMA channel1 configuration */
    DMA_DeInit(DMA1_Channel1); //��DMA ͨ��1�Ĵ��� ��λ          ADC DMA ��Ӧ ͨ��1

    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;        //DMA�������ַ  ��ADC��ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_ConvertedValue;    //DMA�ڴ����ַ  ��Ҫ������ݵĵ�ַ
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //������Ϊ���ݴ������Դ
    DMA_InitStructure.DMA_BufferSize = (\
                                        (ADC1_Channel00ON >> 5) + \
                                        (ADC1_Channel01ON >> 5) + \
                                        (ADC1_Channel02ON >> 5) + \
                                        (ADC1_Channel03ON >> 5) + \
                                        (ADC1_Channel04ON >> 5) + \
                                        (ADC1_Channel05ON >> 5) + \
                                        (ADC1_Channel06ON >> 5) + \
                                        (ADC1_Channel07ON >> 5) + \
                                        (ADC1_Channel08ON >> 5) + \
                                        (ADC1_Channel09ON >> 5) + \
                                        (ADC1_Channel10ON >> 5) + \
                                        (ADC1_Channel11ON >> 5) + \
                                        (ADC1_Channel12ON >> 5) + \
                                        (ADC1_Channel13ON >> 5) + \
                                        (ADC1_Channel14ON >> 5) + \
                                        (ADC1_Channel15ON >> 5) + \
                                        (ADC1_Channel16ON >> 5) + \
                                        (ADC1_Channel17ON >> 5)   \
                                       );              //DMA �����С
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ����
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;         //DMA_MemoryInc_Disable�ڴ��ַ���� DMA_MemoryInc_Enable�ڴ��ַ�ı�
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //�������ݿ��16λ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         //�ڴ����ݿ��
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;         //DMA_Mode_Circular;//������ѭ������ģ      DMA_Mode_Normal
    DMA_InitStructure.DMA_Priority = DMA_Priority_High; //�趨DMAͨ��X �����ȼ�
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;        //DMA ͨ��X û������ �ڴ浽�ڴ洫��
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);        //����DMA ͨ��1 ����
#endif
#if ADC1_DMAIRQ_ENABLE
    /* Enable DMA channel1 IRQ Channel */
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    DMA_ClearFlag(DMA1_FLAG_TC1);
    DMA_ClearITPendingBit(DMA1_IT_GL1);

    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);        //DMA
#endif
#if ADC1_DMA
    /* Enable DMA channel1 */
    DMA_Cmd(DMA1_Channel1, ENABLE);
#endif
    /***********************DMA***********************************/

    /***********************ADC***********************************/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );  //ʹ��ADC1ͨ��ʱ��
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);//����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

    ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC����ģʽ ����ADCģʽ
    /*���ж��ͨ����Ҫ�ɼ��ź�ʱ�����԰�ADC����Ϊ��һ����˳�����Ը���ͨ������ɨ��ת�����������ɼ���ͨ����ֵ�����ɼ����ͨ�������뿪����ģʽ��*/
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;      //ɨ��ģʽ��ɨ��ģʽ���ڶ�ͨ���ɼ�
    /*����ת��ģʽ����ģʽ�뵥��ת��ģʽ�෴������ת��ģʽADCֻ�ɼ�һ�����ݾ�ֹͣת����������ת��ģʽ������һ��ADCת����ɺ�����������һ��ת��*/
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//��������ת��ģʽ������ͣ�ؽ���ADCת��
    /*ADC��Ҫ�ڽ��յ������źŲſ�ʼ����ģ��ת������Щ�����źſ������ⲿ�жϴ���(EXTI��)����ʱ��������������Ϊ�ⲿ�����źţ������ʹ���ⲿ�����źſ���ʹ��������ƴ���*/
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    /*
    ADC_ExternalTrigConv_T2_CC2;
    ADC_ExternalTrigConv_T3_TRGO;
    ADC_ExternalTrigConv_None����ʹ���ⲿ������ת��������������ⲿ��������
    */
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;    //ADC�����Ҷ���
    /*����ADC����ת����ͨ����������Ϊ1~16����*/
    ADC_InitStructure.ADC_NbrOfChannel = (\
                                          (ADC1_Channel00ON >> 5) + \
                                          (ADC1_Channel01ON >> 5) + \
                                          (ADC1_Channel02ON >> 5) + \
                                          (ADC1_Channel03ON >> 5) + \
                                          (ADC1_Channel04ON >> 5) + \
                                          (ADC1_Channel05ON >> 5) + \
                                          (ADC1_Channel06ON >> 5) + \
                                          (ADC1_Channel07ON >> 5) + \
                                          (ADC1_Channel08ON >> 5) + \
                                          (ADC1_Channel09ON >> 5) + \
                                          (ADC1_Channel10ON >> 5) + \
                                          (ADC1_Channel11ON >> 5) + \
                                          (ADC1_Channel12ON >> 5) + \
                                          (ADC1_Channel13ON >> 5) + \
                                          (ADC1_Channel14ON >> 5) + \
                                          (ADC1_Channel15ON >> 5) + \
                                          (ADC1_Channel16ON >> 5) + \
                                          (ADC1_Channel17ON >> 5)   \
                                         );                   //˳����й���ת����ADCͨ������Ŀ
    ADC_Init(ADC1, &ADC_InitStructure);                       //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���

    /*TCONV = (55.5+12.5)*1/9 ��7.56us */
    /**************************************ɨ��˳��************************************************/
#if ADC1_Channel00ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, (u8)(ADC1_Channel00ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel01ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, (u8)(ADC1_Channel01ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel02ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, (u8)(ADC1_Channel02ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel03ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, (u8)(ADC1_Channel03ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel04ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, (u8)(ADC1_Channel04ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel05ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, (u8)(ADC1_Channel05ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel06ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, (u8)(ADC1_Channel06ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel07ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, (u8)(ADC1_Channel07ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel08ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_8, (u8)(ADC1_Channel08ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel09ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_9, (u8)(ADC1_Channel09ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel10ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_10, (u8)(ADC1_Channel10ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel11ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_11, (u8)(ADC1_Channel11ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel12ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_12, (u8)(ADC1_Channel12ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel13ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_13, (u8)(ADC1_Channel13ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel14ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_14, (u8)(ADC1_Channel14ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel15ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_15, (u8)(ADC1_Channel15ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel16ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_16, (u8)(ADC1_Channel16ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
#if ADC1_Channel17ON
    ADC_RegularChannelConfig(ADC1, ADC_Channel_17, (u8)(ADC1_Channel17ON - 0x20), ADC_SampleTime_55Cycles5);
#endif
    /**************************************ɨ��˳��************************************************/
    /********************************** Enable ADC1 DMA *******************************************/
#if ADC1_DMA
    ADC_DMACmd(ADC1, ENABLE);           //ʹ��ADC1 ��DMA ����
#endif
    ADC_Cmd(ADC1, ENABLE);              //ʹ��ָ����ADC1 ע�⣺����ADC_Cmd ֻ��������ADC�������ú󱻵���

    //�ڿ���AD ת��ǰ  ����AD ��У׼
    ADC_ResetCalibration(ADC1); //ʹ�ܸ�λУ׼ /*��λУ׼�Ĵ��� */
    while (ADC_GetResetCalibrationStatus(ADC1)); ///*�ȴ�У׼�Ĵ�����λ��� */

    ADC_StartCalibration(ADC1);  //����ADУ׼
    while (ADC_GetCalibrationStatus(ADC1));  //�ȴ�У׼����

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);     //ʹ��ָ����ADC1�����ת����������

    /*
    ADC_ExternalTrigConvCmd(ADC1, ENABLE);
    */
    /**************************ADC***************************************/
}
/*
 * ��������ADC1_Init
 * ����  ����
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void ADC1_Init(void)
{
    ADC1_GPIO_Config(); //ADC1 GPIO ����
    //TIM2_ADC_Init(5000,0);
    //TIM3_Irgo_Init(VOICE_HZ1,VOICE_HZ2);
    ADC1_Mode_Config(); //ADC1 ������ʽ����
}

//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch)
{
    //����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );  //ADC1,ADCͨ��,����ʱ��Ϊ239.5����

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);     //ʹ��ָ����ADC1�����ת����������

    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC )); //�ȴ�ת������

    return ADC_GetConversionValue(ADC1);    //�������һ��ADC1�������ת�����
}
