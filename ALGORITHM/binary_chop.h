#ifndef __BINARY_CHOP_H__
#define __BINARY_CHOP_H__
#include "sys.h"
#ifdef __cplusplus
       extern "C" {
#endif
/*
	pTable:To find an Key in array
	Key:
	Cnt:size of the array //sizeof(a)/sizeof(a[0])
	Size:size of the Key //sizeof(a[0])
	CmpFunc:
 int cmp(const void *p1, const void *p2)
 {
   return *(int*)p1-*(int*)p2;
 }
 */
typedef int (*CMP_FUN)(const void *Key, const void *dst);
int binary_chop(const void *pTable, int Cnt, int Size, void *Key, CMP_FUN CmpFunc);
				 
#ifdef __cplusplus
}
#endif
#endif

