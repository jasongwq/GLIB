#include "exfuns.h"
#include "ff.h"
#include "sdio_sdcard.h"
static unsigned int fatbuf_Offset = 0;
int task8(void)
{
    _SS
    exfuns_init();          //为fatfs相关变量申请内存
    f_mount(0, fxs[0]);     //挂载SD卡
    while (SD_Init())       //检测SD卡
    {
        WaitX(200);
//        display_string_5x7(6, 1, (unsigned char *)"      SD ER          ");
    }
//    display_string_5x7(6, 1, (unsigned char *)"      SD OK          ");
    /**************测试**************/
    // f_open(file, "0://hjk.txt", FA_CREATE_ALWAYS);
    // f_close (file);
    // f_open(file, "0://123.txt", FA_OPEN_ALWAYS);
    // f_open(file, "0://123.txt", FA_WRITE);
    // f_write(file, "I Love you!", 12, &bxw);
    // f_lseek(file, 20);
    // f_write(file, "\n你好", 6, &bxw);
    // f_printf(file, "nihao你好nihao");
    // f_close(file);
    /**************测试**************/
    f_open(file, "0://data.txt", FA_OPEN_ALWAYS);
		//Open data file
		f_open(file, "0://data.txt", FA_WRITE);
		f_lseek(file,file->fsize);
    while (1)
    {
        WaitX(5000);
        //time
//        sprintf((char *)fatbuf + (fatbuf_Offset += 0), "\r\ndate:%s", srtc_time);
//        //DHT11
//        sprintf((char *)fatbuf + (fatbuf_Offset += 30), "Temperature:%2d ", Temperature);
//        sprintf((char *)fatbuf + (fatbuf_Offset += 14), "Humidity:%2d ", humidity);
//        //Angle
//        sprintf((char *)fatbuf + (fatbuf_Offset += 14), "Angle:X-%4d ", Steering_Angle.x);
//        sprintf((char *)fatbuf + (fatbuf_Offset += 15), "Angle:Y-%4d ", Steering_Angle.y);

        f_write(file, (char *)fatbuf, (fatbuf_Offset += 15), &bxw);

        f_sync(file);
    }
		f_close(file);
    _EE
}