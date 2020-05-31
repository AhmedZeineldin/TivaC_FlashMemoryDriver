

/**
 * main.c
 */
#include "Flash_int.h"
#include "std_types.h"
void InitilizeArr(u32*u32Ptr_Loc_arrPtr,u32 u32_Loc_Size);
void main(void)
{
    static u32 receiveArr[2000] = {0};
    static u32 sendArr[2000];
    InitilizeArr(sendArr,2000);
    Flash_vEnable();
    Flash_vWriteData(sendArr,2000,126976);
    Flash_vRead(receiveArr,2000,126976);
    while(1);
}

void InitilizeArr(u32*u32Ptr_Loc_arrPtr,u32 u32_Loc_Size)
{
    u32 i;
    for( i = 0 ; i < u32_Loc_Size ;i++ )
    {
        u32Ptr_Loc_arrPtr[i] = i;
    }
}
