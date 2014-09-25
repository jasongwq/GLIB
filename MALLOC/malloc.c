#include "malloc.h"
//////////////////////////////////////////////////////////////////////////////////
//int main(void)
//{
//  /***变量***/
//  u8 key;
//  u8 i;
//  /***malloc***/
//  u8 *p=0;
//  u8 *tp=0;
//  u8 paddr[18];           //存放P Addr:+p地址的ASCII值
//  u8 sramx=0;             //默认为内部sram
//  /******/
////    u16 led0pwmval=100;
////    u8 datatemp[SIZE];
////    u32 FLASH_SIZE;
//  /***系统初始化***/
//  Stm32_Clock_Init(9);    //系统时钟设置
//    delay_init(72);         //延时初始化
//  /***USMART组件***/
//  uart2_init(72, 9600); //串口初始化为9600
//  usmart_dev.init(72);    //初始化USMART
//    /***LED***/
//    LED_Init();             //初始化与LED连接的硬件接口
//    delay_ms(100);
//  LED0=0;LED1 = 0; LED2 = 0;
//    /***LCD***/
//    FSMC_LCD_Init();         //FSMC总线配置
//    LCD_Init();
////  LCD_DrawCurve_Init();
//    /***按键***/
//  KEY_Init();
////    WKUP_Init();
//    /***传感器***/
////  IIC_Init();
////  InitMPU6050();
////  TIM3_Int_Init(100 - 1, 7200 - 1); //200，7200 20ms   TIM3_Int_Init(4999,7199);//10Khz的计数频率，计数5K次为500ms 2hz
//    /***步进电机***/
////  step_motor_Init();
////  TIM5_Int_Init(100 - 1, 720 - 1); //150,720,   1.5ms       30, 720 300um
//  /***RTC***/
//  //RTC_Init();
//    /***ADC***/
////    Adc_Init();
//  /***DAC***/
////    Dac1_Init();
//  /***DMA***/
////    MYDMA_Config(DMA1_Channel7,(u32)&USART2->DR,(u32)SendBuff,5168);//DMA1通道4,外设为串口1,存储器为SendBuff,长度5168.
//  /***FLASH***/
////    SPI_Flash_Init();
//  /***PWM***/
////    TIM3_PWM_Init(899,0);   //不分频。PWM频率=72000/(899+1)=80Khz
//  /***MALLOC***/
//  mem_init(SRAMIN);       //初始化内部内存池
//  /******/
//      POINT_COLOR=BLUE;//设置字体为蓝色
//  LCD_ShowString(60,170,200,16,16,"SRAMIN");
//  LCD_ShowString(60,190,200,16,16,"SRAMIN USED:   %");
////    LCD_ShowString(60,210,200,16,16,"SRAMEX USED:   %");
//
//      while(1)
//  {
//      key=KEY_Scan(0);//不支持连按
//      switch(key)
//      {
//          case 0://没有按键按下
//              break;
//          case 1: //KEY0按下
//              p=mymalloc(sramx,2048);//申请2K字节
//              if(p!=NULL)sprintf((char*)p,"Memory Malloc Test%03d",i);//向p写入一些内容
//              break;
//          case 2: //KEY1按下
//              if(p!=NULL)
//              {
//                  sprintf((char*)p,"Memory Malloc Test%03d",i);//更新显示内容
//                  LCD_ShowString(60,250,200,16,16,p);          //显示P的内容
//              }
//              break;
//          case 3: //KEY2按下
//              myfree(sramx,p);//释放内存
//              p=0;            //指向空地址
//              break;
////            case KEY_UP:    //KEY UP按下
////                sramx=!sramx;//切换当前malloc/free操作对象
////                if(sramx)LCD_ShowString(60,170,200,16,16,"SRAMEX");
////                else LCD_ShowString(60,170,200,16,16,"SRAMIN");
////                break;
//      }
//      if(tp!=p)
//      {
//          tp=p;
//          sprintf((char*)paddr,"P Addr:0X%08X",(u32)tp);
//          LCD_ShowString(60,230,200,16,16,paddr); //显示p的地址
//          if(p)LCD_ShowString(60,250,200,16,16,p);//显示P的内容
//          else LCD_Fill(60,250,239,266,WHITE);    //p=0,清除显示
//      }
//      delay_ms(10);
//      i++;
//      if((i%20)==0)//DS0闪烁.
//      {
//          LCD_ShowNum(60+96,190,mem_perused(SRAMIN),3,16);//显示内部内存使用率
////            LCD_ShowNum(60+96,210,mem_perused(SRAMEX),3,16);//显示外部内存使用率
//          LED0=!LED0;
//      }
//  }
//}
//////////////////////////////////////////////////////////////////////////////////

//内存池(4字节对齐)
__align(4) u8 mem1base[MEM1_MAX_SIZE];                                                  //内部SRAM内存池
//__align(4) u8 mem2base[MEM2_MAX_SIZE] __attribute__((at(0X68000000)));                    //外部SRAM内存池
//内存管理表
u16 mem1mapbase[MEM1_ALLOC_TABLE_SIZE];                                                 //内部SRAM内存池MAP
//u16 mem2mapbase[MEM2_ALLOC_TABLE_SIZE] __attribute__((at(0X68000000+MEM2_MAX_SIZE))); //外部SRAM内存池MAP
//内存管理参数
const u32 memtblsize[1] = {MEM1_ALLOC_TABLE_SIZE}; //,MEM2_ALLOC_TABLE_SIZE};      //内存表大小
const u32 memblksize[1] = {MEM1_BLOCK_SIZE}; //,MEM2_BLOCK_SIZE};                  //内存分块大小
const u32 memsize[1] = {MEM1_MAX_SIZE}; //,MEM2_MAX_SIZE};                         //内存总大小


//内存管理控制器
struct _m_mallco_dev mallco_dev =
{
    mem_init,               //内存初始化
    mem_perused,            //内存使用率
    mem1base,//mem2base,        //内存池
    mem1mapbase,//mem2mapbase,//内存管理状态表
    0,//0,                      //内存管理未就绪
};

//复制内存
//*des:目的地址
//*src:源地址
//n:需要复制的内存长度(字节为单位)
void mymemcpy(void* des, void* src, u32 n)
{
    u8* xdes = des;
    u8* xsrc = src;
    while (n--)*xdes++ = *xsrc++;
}
//设置内存
//*s:内存首地址
//c :要设置的值
//count:需要设置的内存大小(字节为单位)
void mymemset(void* s, u8 c, u32 count)
{
    u8* xs = s;
    while (count--)*xs++ = c;
}
//内存管理初始化
//memx:所属内存块
void mem_init(u8 memx)
{
    mymemset(mallco_dev.memmap[memx], 0, memtblsize[memx] * 2); //内存状态表数据清零
    mymemset(mallco_dev.membase[memx], 0, memsize[memx]);   //内存池所有数据清零
    mallco_dev.memrdy[memx] = 1;                            //内存管理初始化OK
}
//获取内存使用率
//memx:所属内存块
//返回值:使用率(0~100)
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
//内存分配(内部调用)
//memx:所属内存块
//size:要分配的内存大小(字节)
//返回值:0XFFFFFFFF,代表错误;其他,内存偏移地址
u32 mem_malloc(u8 memx, u32 size)
{
    signed long offset = 0;
    u16 nmemb;  //需要的内存块数
    u16 cmemb = 0; //连续空内存块数
    u32 i;
    if (!mallco_dev.memrdy[memx])mallco_dev.init(memx); //未初始化,先执行初始化
    if (size == 0)return 0XFFFFFFFF; //不需要分配
    nmemb = size / memblksize[memx]; //获取需要分配的连续内存块数
    if (size % memblksize[memx])nmemb++;
    for (offset = memtblsize[memx] - 1; offset >= 0; offset--) //搜索整个内存控制区
    {
        if (!mallco_dev.memmap[memx][offset])cmemb++; //连续空内存块数增加
        else cmemb = 0;                             //连续内存块清零
        if (cmemb == nmemb)                         //找到了连续nmemb个空内存块
        {
            for (i = 0; i < nmemb; i++)             //标注内存块非空
            {
                mallco_dev.memmap[memx][offset + i] = nmemb;
            }
            return (offset * memblksize[memx]); //返回偏移地址
        }
    }
    return 0XFFFFFFFF;//未找到符合分配条件的内存块
}
//释放内存(内部调用)
//memx:所属内存块
//offset:内存地址偏移
//返回值:0,释放成功;1,释放失败;
u8 mem_free(u8 memx, u32 offset)
{
    int i;
    if (!mallco_dev.memrdy[memx]) //未初始化,先执行初始化
    {
        mallco_dev.init(memx);
        return 1;//未初始化
    }
    if (offset < memsize[memx]) //偏移在内存池内.
    {
        int index = offset / memblksize[memx];      //偏移所在内存块号码
        int nmemb = mallco_dev.memmap[memx][index]; //内存块数量
        for (i = 0; i < nmemb; i++)                 //内存块清零
        {
            mallco_dev.memmap[memx][index + i] = 0;
        }
        return 0;
    }
    else return 2; //偏移超区了.
}
//释放内存(外部调用)
//memx:所属内存块
//ptr:内存首地址
void myfree(u8 memx, void* ptr)
{
    u32 offset;
    if (ptr == NULL)return; //地址为0.
    offset = (u32)ptr - (u32)mallco_dev.membase[memx];
    mem_free(memx, offset); //释放内存
}
//分配内存(外部调用)
//memx:所属内存块
//size:内存大小(字节)
//返回值:分配到的内存首地址.
void* mymalloc(u8 memx, u32 size)
{
    u32 offset;
    offset = mem_malloc(memx, size);
    if (offset == 0XFFFFFFFF)return NULL;
    else return (void*)((u32)mallco_dev.membase[memx] + offset);
}
//重新分配内存(外部调用)
//memx:所属内存块
//*ptr:旧内存首地址
//size:要分配的内存大小(字节)
//返回值:新分配到的内存首地址.
void* myrealloc(u8 memx, void* ptr, u32 size)
{
    u32 offset;
    offset = mem_malloc(memx, size);
    if (offset == 0XFFFFFFFF)return NULL;
    else
    {
        mymemcpy((void*)((u32)mallco_dev.membase[memx] + offset), ptr, size); //拷贝旧内存内容到新内存
        myfree(memx, ptr);                                                  //释放旧内存
        return (void*)((u32)mallco_dev.membase[memx] + offset);             //返回新内存首地址
    }
}












