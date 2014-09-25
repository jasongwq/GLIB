/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2013        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/

#include "diskio.h"     /* FatFs lower layer API */

#include "sdio_sdcard.h"
     /* Example: MMC/SDC contorl */
#ifdef SYS_MEMMALLOC_ENABLE_
#include "malloc.h"
#endif
/* Definitions of physical drive number for each media */
#define SD_CARD  0  //SD��,���Ϊ0

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive    //��ʼ������                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
    BYTE pdrv               /* Physical drive nmuber (0..) */
)
{
    DSTATUS stat;
    int result;
    switch (pdrv)
    {
    case SD_CARD :
        result = SD_Init();
        if (result == SD_OK)stat = RES_OK;
        // translate the reslut code here
        return stat;

    }
    return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status  //��ô���״̬                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
    BYTE pdrv       /* Physical drive nmuber (0..) */
)
{
    // DSTATUS stat;
    // int result;
    // switch (pdrv)
    // {
    // case SD_CARD :
    //     result = ATA_disk_status();

    //     // translate the reslut code here

    //     return stat;
    // }
    // return STA_NOINIT;
    return RES_OK;
}



/*-----------------------------------------------------------------------
Read Sector(s)
������
drv:���̱��0~9
buff:���ݽ��ջ����׵�ַ
sector:������ַ
count:��Ҫ��ȡ��������                                                    
-----------------------------------------------------------------------*/

DRESULT disk_read (
    BYTE pdrv,      /* Physical drive nmuber (0..) */
    BYTE *buff,     /* Data buffer to store read data */
    DWORD sector,   /* Sector address (LBA) */
    BYTE count      /* Number of sectors to read (1..128) */
)
{
    DRESULT res;
    int result;
    if (!count)return RES_PARERR;//count���ܵ���0�����򷵻ز�������
    switch (pdrv)
    {
    case SD_CARD :
        // translate the arguments here
        result = SD_ReadDisk(buff, sector, count);
        // translate the reslut code here
        if (result == SD_OK)res = RES_OK;
        return res;
        // case MMC :
        //     // translate the arguments here

        //     result = MMC_disk_read(buff, sector, count);

        //     // translate the reslut code here

        //     return res;

        // case USB :
        //     // translate the arguments here

        //     result = USB_disk_read(buff, sector, count);

        //     // translate the reslut code here

        //     return res;
    }
    return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)
 //д����
 //drv:���̱��0~9
 //buff:���������׵�ַ
 //sector:������ַ
 //count:��Ҫд���������                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
    BYTE pdrv,          /* Physical drive nmuber (0..) */
    const BYTE *buff,   /* Data to be written */
    DWORD sector,       /* Sector address (LBA) */
    BYTE count          /* Number of sectors to write (1..128) */
)
{
    DRESULT res;
    int result;
    u8 retry = 0X1F;    //д��ʧ�ܵ�ʱ��,���Դ���

    if (!count)return RES_PARERR;//count���ܵ���0�����򷵻ز�������
    switch (pdrv)
    {
    case SD_CARD :
        // translate the arguments here
        while (retry--)
        {
            result = SD_WriteDisk((u8 *)buff, sector, count);
            if (result == SD_OK)
            {
                res = RES_OK;
                break;
            }

        }
        // translate the reslut code here
        return res;

        // case MMC :
        //     // translate the arguments here

        //     result = MMC_disk_write(buff, sector, count);

        //     // translate the reslut code here

        //     return res;

        // case USB :
        //     // translate the arguments here

        //     result = USB_disk_write(buff, sector, count);

        //     // translate the reslut code here

        //     return res;
    }
    return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions
//����������Ļ��
 //drv:���̱��0~9
 //ctrl:���ƴ���
 //buff:����/���ջ�����ָ��                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
    BYTE pdrv,      /* Physical drive nmuber (0..) */
    BYTE cmd,       /* Control code */
    void *buff      /* Buffer to send/receive control data */
)
{
    DRESULT res;
    int result;

    switch (pdrv)
    {
    case SD_CARD :
        // pre-process here
        switch (cmd)
        {
        case CTRL_SYNC:
            result = RES_OK;
            break;
        case GET_SECTOR_SIZE:
            *(WORD *)buff = 512;
            result = RES_OK;
            break;
        case GET_BLOCK_SIZE:
            *(WORD *)buff = 8;
            result = RES_OK;
            break;
        case GET_SECTOR_COUNT:
            result = RES_OK;
            break;
        default:
            result = RES_PARERR;
            break;
        }
        // post-process here
		if(result==SD_OK)
			res=RES_OK;
        return res;
    }
    return RES_PARERR;
}
#endif

//���ʱ��
//User defined function to give a current time to fatfs module      */
//31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */
//15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */
DWORD get_fattime (void)
{
    return 0;
}
#ifdef SYS_MEMMALLOC_ENABLE_

//��̬�����ڴ�
void *ff_memalloc (UINT size)
{
    return (void *)mymalloc(SRAMIN, size);
}
//�ͷ��ڴ�
void ff_memfree (void *mf)
{
    myfree(SRAMIN, mf);
}
#endif
