#include "binary_chop.h"//typedef int (*CMP_FUN)(const void *Key, const void *dst);

#define GET_DATA(arr, pos, size) ((unsigned char *)(arr) + (pos) * (size))


//int cmp(const void *p1, const void *p2)
//{
//  return *(int*)p1-*(int*)p2;
//}
int binary_chop(const void *pTable, int Cnt, int Size, void *Key, CMP_FUN CmpFunc)
{
    int Start, Mid, End;
    Start = 0;
    End = Cnt - 1;
    if (Start > End)
    {
        return -1;
    }
    while (Start <= End)
    {
        Mid = (Start + End) / 2;
        if ( CmpFunc(Key, GET_DATA(pTable, Mid, Size)) < 0 )
        {
            End = Mid - 1;
        }
        else if ( CmpFunc(Key, GET_DATA(pTable, Mid, Size)) > 0 )
        {
            Start = Mid + 1;
        }
        else
        {
            return Mid;//GET_DATA(pTable, Mid, Size);
        }
    }
    return -1;
}
// int binary_chop(int *a, int key, int n)
// {
//     int left = 0, right = n - 1, mid = 0;
//     mid = (left + right) / 2;
//     while (left < right && a[mid] != key )
//     {
//         if (a[mid] < key)
//             left = mid + 1;
//         else if ( a[mid] > key )
//             right = mid - 1;
//         mid = ( left + right ) / 2;
//     }
//     if ( a[mid] == key )
//         return mid;
//     return -1;
// }

//int maintest_binary_chop()
//int main()
//{
//    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 13, 45, 67, 89, 99, 101, 111, 123, 134, 565, 677};
//    int b[] = { 677, 1, 7, 11, 67 };
//    int i;
//    for ( i = 0; i < sizeof(b) / sizeof(b[0]); i++ )
//    {
//        //printf( "%d\n", recurbinary(a, 99, 0, sizeof(a) / sizeof(a[0]) - 1) );
//        //printf( "%d\n", binary_chop( a, b[i], sizeof(a) / sizeof(a[0])));
//        printf( "%d\n", binary_chop(a,sizeof(a)/sizeof(a[0]),sizeof(a[0]),&b[i],&cmp));
//    }
//    return 0;
//}


