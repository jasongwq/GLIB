#ifndef __EXFUNS_H
#define __EXFUNS_H 	
#include "ff.h"
#include "sys.h"



/////////////////////////////////////////////////////////////////////////////////////////////////////
extern FATFS *fxs[1];  
extern FIL *file;	 
extern FIL *ftemp;	 
extern UINT br,bxw;
extern FILINFO fileinfo;
extern DIR dir;
extern u8 *fatbuf;//SD卡数据缓存区


//f_typetell返回的类型定义
//根据表FILE_TYPE_TBL获得.在exfuns.c里面定义
#define T_BIN		0X00	//bin文件
#define T_LRC		0X10	//lrc文件
#define T_NES		0X20	//nes文件
#define T_TEXT		0X30	//.txt文件
#define T_C			0X31	//.c文件
#define T_H			0X32    //.h文件
#define T_FLAC		0X4C	//flac文件
#define T_BMP		0X50	//bmp文件
#define T_JPG		0X51	//jpg文件
#define T_JPEG		0X52	//jpeg文件		 
#define T_GIF		0X53	//gif文件  

 
u8 exfuns_init(void);		//申请内存
u8 f_typetell(char *fname);	//识别文件类型
u8 exf_getfree(u8 *drv,u32 *total,u32 *free);//得到磁盘总容量和剩余容量
u32 exf_fdsize(u8 *fdname);																				   //得到文件夹大小
// u8* exf_get_src_dname(u8* dpfn);																		   
// u8 exf_copy(u8(*fcpymsg)(u8*pname,u8 pct,u8 mode),u8 *psrc,u8 *pdst,u32 totsize,u32 cpdsize,u8 fwmode);	   //文件复制
// u8 exf_fdcopy(u8(*fcpymsg)(u8*pname,u8 pct,u8 mode),u8 *psrc,u8 *pdst,u32 *totsize,u32 *cpdsize,u8 fwmode);//文件夹复制

#endif


