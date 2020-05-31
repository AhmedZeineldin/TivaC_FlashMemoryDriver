/*
 * Flash_int.h
 *
 *  Created on: May 31, 2020
 *      Author: dodo_
 */

#ifndef FLASH_INT_H_
#define FLASH_INT_H_
#include "std_types.h"
void Flash_vEnable(void);
void Flash_vErase(u8 u8_Loc_BlockNum);
//NOTE THAT: " u32_Loc_dataLength " in the " Flash_vWriteData() " is in (words)
void Flash_vWriteData(u32 * u32ptr_Loc_Data,u32 u32_Loc_dataLength,u32 u32_Loc_flashAddress );
void Flash_vRead(u32 * u32ptr_Loc_Data, u32 u32_Loc_dataLength,u32 u32_Loc_initialAddress);


#endif /* FLASH_INT_H_ */
