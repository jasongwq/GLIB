/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : mass_mal.c
* Author             : MCD Application Team
* Version            : V2.2.0
* Date               : 06/13/2008
* Description        : Medium Access Layer interface
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/*SD卡和USB接口的驱动函数及接口函数
//2013/7/31 U盘
*/
/* Includes ------------------------------------------------------------------*/
#include "platform_config.h"
#include "sdio_sdcard.h"
#include "mass_mal.h"
#include "USART.h"
#include "LED.h"
#define BlockSize            512 /* Block Size in Bytes */
#define BufferWordsSize      (BlockSize >> 2)
uint32_t Buffer_Block_Tx[BufferWordsSize], Buffer_Block_Rx[BufferWordsSize];

long long Mass_Memory_Size[MAX_LUN + 1];

u32 Mass_Block_Size[MAX_LUN + 1];
u32 Mass_Block_Count[MAX_LUN + 1];

__IO uint32_t Status = 0;

extern SD_CardInfo SDCardInfo;
unsigned char dis_mem = 0;


/*******************************************************************************
* Function Name  : MAL_Init
* Description    : Initializes the Media on the STM32
* 功能           : 储存介质初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Init(uint8_t lun)
{
    uint16_t status = MAL_OK;
    switch (lun)
    {
    case 0:

        Status = SD_Init();
        Status = SD_GetCardInfo(&SDCardInfo);
        Status = SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));
        Status = SD_EnableWideBusOperation(SDIO_BusWide_4b);
        Status = SD_SetDeviceMode(SD_DMA_MODE);
        if (Status == SD_OK)
        {
            // 从地址0开始读取512字节
            Status = SD_ReadBlock(Buffer_Block_Rx, 0x00,  BlockSize);
        }
        if (Status == SD_OK)
        {
            // 返回成功的话，串口输出SD卡测试成功信息
						DbgPrintf(" \n SD SDIO-4bit模式 TF OK");
        }
        break;
    default:
        return MAL_FAIL;
    }
    return status;
}

/****************************************************************************
* 名    称：MAL_Write
* 功    能：USB存储介质写驱动
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无
****************************************************************************/
extern u8 SD_WriteDisk(u8* buf, u32 sector, u8 cnt);
extern u8 SD_ReadDisk(u8* buf, u32 sector, u8 cnt);


uint16_t MAL_Write(uint8_t lun, uint32_t Memory_Offset, uint32_t* Writebuff, uint16_t Transfer_Length)
{
    switch (lun)
    {
    case 0:
        //在指定地址连续写入指定长度的数据
        Status = SD_WriteDisk((u8*)Writebuff, Memory_Offset >> 9,  Transfer_Length >> 9);
        if ( Status != SD_OK )
            return MAL_FAIL;
        break;
    default:
        return MAL_FAIL;
    }
    return MAL_OK;
}

/****************************************************************************
* 名    称：uint16_t MAL_Read(uint8_t lun, uint32_t Memory_Offset, uint32_t *Readbuff, uint16_t Transfer_Length)
* 功    能：USB存储介质读驱动
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无
****************************************************************************/
uint16_t MAL_Read(uint8_t lun, uint32_t Memory_Offset, uint32_t* Readbuff, uint16_t Transfer_Length)
{
    switch (lun)
    {
    case 0:
        //从指定地址连续读出指定长度的数据
        Status = SD_ReadDisk((u8*)Readbuff, Memory_Offset >> 9,  Transfer_Length >> 9);
        if ( Status != SD_OK )
            return MAL_FAIL;
        break;
    default:
        return MAL_FAIL;
    }
    return MAL_OK;
}

/*******************************************************************************
* 名    称：uint16_t MAL_GetStatus (uint8_t lun)
* 功    能：获得存储介质信息
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无
****************************************************************************/
//uint16_t MAL_GetStatus (uint8_t lun)
//{
//    uint32_t DeviceSizeMul = 0, NumberOfBlocks = 0;
//    if (lun == 0)
//    {
//        if (SD_Init() == SD_OK)
//        {
//            SD_GetCardInfo(&SDCardInfo);
//            SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));
//            DeviceSizeMul = (SDCardInfo.SD_csd.DeviceSizeMul + 2);

//            if (SDCardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)
//            {
//                Mass_Block_Count[0] = (SDCardInfo.SD_csd.DeviceSize + 1) * 1024;
//            }
//            else
//            {
//                NumberOfBlocks  = ((1 << (SDCardInfo.SD_csd.RdBlockLen)) / 512);
//                Mass_Block_Count[0] = ((SDCardInfo.SD_csd.DeviceSize + 1) * (1 << DeviceSizeMul) << (NumberOfBlocks / 2));
//            }
//            Mass_Block_Size[0]  = 512;

//            Status = SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));
//            Status = SD_EnableWideBusOperation(SDIO_BusWide_4b);
//            if ( Status != SD_OK )
//                return MAL_FAIL;
//            Status = SD_SetDeviceMode(SD_DMA_MODE);
//            if ( Status != SD_OK )
//                return MAL_FAIL;
//            Mass_Memory_Size[0] = Mass_Block_Count[0] * Mass_Block_Size[0];
//            LED1 = 0;
//            if (dis_mem == 0)   //显示TF卡的容量  由于是周期性更新状态，所以，加了条件，只显示一次容量值
//            {
//                printf("\r\n Micro SD卡的容量是 %d MBytes\n" ,SDCardInfo.CardCapacity);
//                dis_mem = 1;
//            }
//            return MAL_OK;
//        }
//    }
//    LED1 = 0;
//    return MAL_FAIL;
//}
u16 MAL_GetStatus (u8 lun)
{
    uint32_t DeviceSizeMul = 0, NumberOfBlocks = 0;
    switch (lun)
    {
    case 0:
        if (dis_mem == 0)   //显示TF卡的容量  由于是周期性更新状态，所以，加了条件，只显示一次容量值
        {
            if (SD_Init() == SD_OK)
            {
                SD_GetCardInfo(&SDCardInfo);
                SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));
                DeviceSizeMul = (SDCardInfo.SD_csd.DeviceSizeMul + 2);

                if (SDCardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)
                {
                    Mass_Block_Count[0] = (SDCardInfo.SD_csd.DeviceSize + 1) * 1024;
                }
                else
                {
                    NumberOfBlocks  = ((1 << (SDCardInfo.SD_csd.RdBlockLen)) / 512);
                    Mass_Block_Count[0] = ((SDCardInfo.SD_csd.DeviceSize + 1) * (1 << DeviceSizeMul) << (NumberOfBlocks / 2));
                }
                Mass_Block_Size[0]  = 512;

                Status = SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));
                Status = SD_EnableWideBusOperation(SDIO_BusWide_4b);
                if ( Status != SD_OK )
                    return MAL_FAIL;
                Status = SD_SetDeviceMode(SD_DMA_MODE);
                if ( Status != SD_OK )
                    return MAL_FAIL;
                Mass_Memory_Size[0] = Mass_Block_Count[0] * Mass_Block_Size[0];
                LED1 = 0;
                //                    if (dis_mem == 0)   //显示TF卡的容量  由于是周期性更新状态，所以，加了条件，只显示一次容量值
                //                    {
                printf("\r\n Micro SD卡的容量是 %lld MBytes\n" , SDCardInfo.CardCapacity >> 20);
                dis_mem = 1;
                //                    }
                return MAL_OK;
            }
            dis_mem = 1;
        }
        return MAL_OK;
    case 1:
        return MAL_OK;
    case 2:
        return MAL_FAIL;
    default:
        return MAL_FAIL;
    }
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
