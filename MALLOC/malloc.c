#include "malloc.h"
//////////////////////////////////////////////////////////////////////////////////
//int main(void)
//{
//  /***����***/
//  u8 key;
//  u8 i;
//  /***malloc***/
//  u8 *p=0;
//  u8 *tp=0;
//  u8 paddr[18];           //���P Addr:+p��ַ��ASCIIֵ
//  u8 sramx=0;             //Ĭ��Ϊ�ڲ�sram
//  /******/
////    u16 led0pwmval=100;
////    u8 datatemp[SIZE];
////    u32 FLASH_SIZE;
//  /***ϵͳ��ʼ��***/
//  Stm32_Clock_Init(9);    //ϵͳʱ������
//    delay_init(72);         //��ʱ��ʼ��
//  /***USMART���***/
//  uart2_init(72, 9600); //���ڳ�ʼ��Ϊ9600
//  usmart_dev.init(72);    //��ʼ��USMART
//    /***LED***/
//    LED_Init();             //��ʼ����LED���ӵ�Ӳ���ӿ�
//    delay_ms(100);
//  LED0=0;LED1 = 0; LED2 = 0;
//    /***LCD***/
//    FSMC_LCD_Init();         //FSMC��������
//    LCD_Init();
////  LCD_DrawCurve_Init();
//    /***����***/
//  KEY_Init();
////    WKUP_Init();
//    /***������***/
////  IIC_Init();
////  InitMPU6050();
////  TIM3_Int_Init(100 - 1, 7200 - 1); //200��7200 20ms   TIM3_Int_Init(4999,7199);//10Khz�ļ���Ƶ�ʣ�����5K��Ϊ500ms 2hz
//    /***�������***/
////  step_motor_Init();
////  TIM5_Int_Init(100 - 1, 720 - 1); //150,720,   1.5ms       30, 720 300um
//  /***RTC***/
//  //RTC_Init();
//    /***ADC***/
////    Adc_Init();
//  /***DAC***/
////    Dac1_Init();
//  /***DMA***/
////    MYDMA_Config(DMA1_Channel7,(u32)&USART2->DR,(u32)SendBuff,5168);//DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,����5168.
//  /***FLASH***/
////    SPI_Flash_Init();
//  /***PWM***/
////    TIM3_PWM_Init(899,0);   //����Ƶ��PWMƵ��=72000/(899+1)=80Khz
//  /***MALLOC***/
//  mem_init(SRAMIN);       //��ʼ���ڲ��ڴ��
//  /******/
//      POINT_COLOR=BLUE;//��������Ϊ��ɫ
//  LCD_ShowString(60,170,200,16,16,"SRAMIN");
//  LCD_ShowString(60,190,200,16,16,"SRAMIN USED:   %");
////    LCD_ShowString(60,210,200,16,16,"SRAMEX USED:   %");
//
//      while(1)
//  {
//      key=KEY_Scan(0);//��֧������
//      switch(key)
//      {
//          case 0://û�а�������
//              break;
//          case 1: //KEY0����
//              p=mymalloc(sramx,2048);//����2K�ֽ�
//              if(p!=NULL)sprintf((char*)p,"Memory Malloc Test%03d",i);//��pд��һЩ����
//              break;
//          case 2: //KEY1����
//              if(p!=NULL)
//              {
//                  sprintf((char*)p,"Memory Malloc Test%03d",i);//������ʾ����
//                  LCD_ShowString(60,250,200,16,16,p);          //��ʾP������
//              }
//              break;
//          case 3: //KEY2����
//              myfree(sramx,p);//�ͷ��ڴ�
//              p=0;            //ָ��յ�ַ
//              break;
////            case KEY_UP:    //KEY UP����
////                sramx=!sramx;//�л���ǰmalloc/free��������
////                if(sramx)LCD_ShowString(60,170,200,16,16,"SRAMEX");
////                else LCD_ShowString(60,170,200,16,16,"SRAMIN");
////                break;
//      }
//      if(tp!=p)
//      {
//          tp=p;
//          sprintf((char*)paddr,"P Addr:0X%08X",(u32)tp);
//          LCD_ShowString(60,230,200,16,16,paddr); //��ʾp�ĵ�ַ
//          if(p)LCD_ShowString(60,250,200,16,16,p);//��ʾP������
//          else LCD_Fill(60,250,239,266,WHITE);    //p=0,�����ʾ
//      }
//      delay_ms(10);
//      i++;
//      if((i%20)==0)//DS0��˸.
//      {
//          LCD_ShowNum(60+96,190,mem_perused(SRAMIN),3,16);//��ʾ�ڲ��ڴ�ʹ����
////            LCD_ShowNum(60+96,210,mem_perused(SRAMEX),3,16);//��ʾ�ⲿ�ڴ�ʹ����
//          LED0=!LED0;
//      }
//  }
//}
//////////////////////////////////////////////////////////////////////////////////

//�ڴ��(4�ֽڶ���)
__align(4) u8 mem1base[MEM1_MAX_SIZE];                                                  //�ڲ�SRAM�ڴ��
//__align(4) u8 mem2base[MEM2_MAX_SIZE] __attribute__((at(0X68000000)));                    //�ⲿSRAM�ڴ��
//�ڴ�����
u16 mem1mapbase[MEM1_ALLOC_TABLE_SIZE];                                                 //�ڲ�SRAM�ڴ��MAP
//u16 mem2mapbase[MEM2_ALLOC_TABLE_SIZE] __attribute__((at(0X68000000+MEM2_MAX_SIZE))); //�ⲿSRAM�ڴ��MAP
//�ڴ�������
const u32 memtblsize[1] = {MEM1_ALLOC_TABLE_SIZE}; //,MEM2_ALLOC_TABLE_SIZE};      //�ڴ���С
const u32 memblksize[1] = {MEM1_BLOCK_SIZE}; //,MEM2_BLOCK_SIZE};                  //�ڴ�ֿ��С
const u32 memsize[1] = {MEM1_MAX_SIZE}; //,MEM2_MAX_SIZE};                         //�ڴ��ܴ�С


//�ڴ���������
struct _m_mallco_dev mallco_dev =
{
    mem_init,               //�ڴ��ʼ��
    mem_perused,            //�ڴ�ʹ����
    mem1base,//mem2base,        //�ڴ��
    mem1mapbase,//mem2mapbase,//�ڴ����״̬��
    0,//0,                      //�ڴ����δ����
};

//�����ڴ�
//*des:Ŀ�ĵ�ַ
//*src:Դ��ַ
//n:��Ҫ���Ƶ��ڴ泤��(�ֽ�Ϊ��λ)
void mymemcpy(void* des, void* src, u32 n)
{
    u8* xdes = des;
    u8* xsrc = src;
    while (n--)*xdes++ = *xsrc++;
}
//�����ڴ�
//*s:�ڴ��׵�ַ
//c :Ҫ���õ�ֵ
//count:��Ҫ���õ��ڴ��С(�ֽ�Ϊ��λ)
void mymemset(void* s, u8 c, u32 count)
{
    u8* xs = s;
    while (count--)*xs++ = c;
}
//�ڴ�����ʼ��
//memx:�����ڴ��
void mem_init(u8 memx)
{
    mymemset(mallco_dev.memmap[memx], 0, memtblsize[memx] * 2); //�ڴ�״̬����������
    mymemset(mallco_dev.membase[memx], 0, memsize[memx]);   //�ڴ��������������
    mallco_dev.memrdy[memx] = 1;                            //�ڴ�����ʼ��OK
}
//��ȡ�ڴ�ʹ����
//memx:�����ڴ��
//����ֵ:ʹ����(0~100)
u8 mem_perused(u8 memx)
{
    u32 used = 0;
    u32 i;
    for (i = 0; i < memtblsize[memx]; i++)
    {
        if (mallco_dev.memmap[memx][i])used++;
    }
    return (used * 100) / (memtblsize[memx]);
}
//�ڴ����(�ڲ�����)
//memx:�����ڴ��
//size:Ҫ������ڴ��С(�ֽ�)
//����ֵ:0XFFFFFFFF,�������;����,�ڴ�ƫ�Ƶ�ַ
u32 mem_malloc(u8 memx, u32 size)
{
    signed long offset = 0;
    u16 nmemb;  //��Ҫ���ڴ����
    u16 cmemb = 0; //�������ڴ����
    u32 i;
    if (!mallco_dev.memrdy[memx])mallco_dev.init(memx); //δ��ʼ��,��ִ�г�ʼ��
    if (size == 0)return 0XFFFFFFFF; //����Ҫ����
    nmemb = size / memblksize[memx]; //��ȡ��Ҫ����������ڴ����
    if (size % memblksize[memx])nmemb++;
    for (offset = memtblsize[memx] - 1; offset >= 0; offset--) //���������ڴ������
    {
        if (!mallco_dev.memmap[memx][offset])cmemb++; //�������ڴ��������
        else cmemb = 0;                             //�����ڴ������
        if (cmemb == nmemb)                         //�ҵ�������nmemb�����ڴ��
        {
            for (i = 0; i < nmemb; i++)             //��ע�ڴ��ǿ�
            {
                mallco_dev.memmap[memx][offset + i] = nmemb;
            }
            return (offset * memblksize[memx]); //����ƫ�Ƶ�ַ
        }
    }
    return 0XFFFFFFFF;//δ�ҵ����Ϸ����������ڴ��
}
//�ͷ��ڴ�(�ڲ�����)
//memx:�����ڴ��
//offset:�ڴ��ַƫ��
//����ֵ:0,�ͷųɹ�;1,�ͷ�ʧ��;
u8 mem_free(u8 memx, u32 offset)
{
    int i;
    if (!mallco_dev.memrdy[memx]) //δ��ʼ��,��ִ�г�ʼ��
    {
        mallco_dev.init(memx);
        return 1;//δ��ʼ��
    }
    if (offset < memsize[memx]) //ƫ�����ڴ����.
    {
        int index = offset / memblksize[memx];      //ƫ�������ڴ�����
        int nmemb = mallco_dev.memmap[memx][index]; //�ڴ������
        for (i = 0; i < nmemb; i++)                 //�ڴ������
        {
            mallco_dev.memmap[memx][index + i] = 0;
        }
        return 0;
    }
    else return 2; //ƫ�Ƴ�����.
}
//�ͷ��ڴ�(�ⲿ����)
//memx:�����ڴ��
//ptr:�ڴ��׵�ַ
void myfree(u8 memx, void* ptr)
{
    u32 offset;
    if (ptr == NULL)return; //��ַΪ0.
    offset = (u32)ptr - (u32)mallco_dev.membase[memx];
    mem_free(memx, offset); //�ͷ��ڴ�
}
//�����ڴ�(�ⲿ����)
//memx:�����ڴ��
//size:�ڴ��С(�ֽ�)
//����ֵ:���䵽���ڴ��׵�ַ.
void* mymalloc(u8 memx, u32 size)
{
    u32 offset;
    offset = mem_malloc(memx, size);
    if (offset == 0XFFFFFFFF)return NULL;
    else return (void*)((u32)mallco_dev.membase[memx] + offset);
}
//���·����ڴ�(�ⲿ����)
//memx:�����ڴ��
//*ptr:���ڴ��׵�ַ
//size:Ҫ������ڴ��С(�ֽ�)
//����ֵ:�·��䵽���ڴ��׵�ַ.
void* myrealloc(u8 memx, void* ptr, u32 size)
{
    u32 offset;
    offset = mem_malloc(memx, size);
    if (offset == 0XFFFFFFFF)return NULL;
    else
    {
        mymemcpy((void*)((u32)mallco_dev.membase[memx] + offset), ptr, size); //�������ڴ����ݵ����ڴ�
        myfree(memx, ptr);                                                  //�ͷž��ڴ�
        return (void*)((u32)mallco_dev.membase[memx] + offset);             //�������ڴ��׵�ַ
    }
}












