#ifndef _AES_H_
#define _AES_H_
#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char AES_Key_Table[32];
extern void aesEncInit(void);
extern void aesEncrypt( unsigned char * buffer, unsigned char * chainBlock );


#ifdef __cplusplus
}
#endif
#endif

