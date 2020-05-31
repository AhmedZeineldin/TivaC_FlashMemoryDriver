/*
 * Flash_prog.c
 *
 *  Created on: May 31, 2020
 *      Author: dodo_
 */

#include "Flash_int.h"
#include "Flash_MemMap.h"
#include "Flash_config.h"
static u16 u16_Glob_flashKey = 0;
/*===================================== Enables operations Flash memory ======================================================*/
void Flash_vEnable(void)
{
    // If the KEY flag (bit 4) is set, then the key is 0xA442.
    //  Otherwise, the key is 0x71D5 (pg. 583 of the TM4C123 datasheet).
    if (BOOTCFG & 0x10) {
        u16_Glob_flashKey = 0xA442;
    }
    else {
        u16_Glob_flashKey = 0x71D5;
    }

}
/*====================================== Erase operation function ===========================================================*/
void Flash_vErase(u8 u8_Loc_BlockNum)
{
    if( u8_Loc_BlockNum >= MINIMUM_FLASH_GURANTEE_SIZE )
    {
        if(u16_Glob_flashKey!=0)   //Checking that the flash enable function is used
        {
            FMA = u8_Loc_BlockNum * FLASH_BLOCK_SIZE;
            // Set the ERASE command bit.
            FMC = (u16_Glob_flashKey << 16) | 0x2;

            // Poll the ERASE bit until it is cleared.
            while (FMC & 0x2);

        }


    }
}
/*==================================== Write operation function ============================================================= */
void Flash_vWriteData(u32 * u32ptr_Loc_Data,u32 u32_Loc_dataLength,u32 u32_Loc_flashAddress )
{
    u8 u8_Loc_numOfBlocks;     //Number of blocks to be erased before writing to it
    u8 u8_Loc_eraseBlockCount;
    u8 u8_Loc_initialBlockNum;
    u32 u32_Loc_dataCounter;
    f32 f32_Loc_blockFraction; //used to calculate the exact number of blocks as the data length is not always multiple of block size

    //we have 2 parameters the starting block number which can be determined by the u32_Loc_flashAddress and the size of blocks to be
    //erased starting from that block which can be determined by the u32_Loc_dataLength
    u8_Loc_initialBlockNum = u32_Loc_flashAddress / FLASH_BLOCK_SIZE;
    f32_Loc_blockFraction = ( ((f32)u32_Loc_dataLength * SIZE_OF_WORD ) / FLASH_BLOCK_SIZE );

    if( ( f32_Loc_blockFraction - (u32)f32_Loc_blockFraction ) > 0 )
    {
        u8_Loc_numOfBlocks = (u32)f32_Loc_blockFraction + 1;
    }
    else
    {
        u8_Loc_numOfBlocks = (u32)f32_Loc_blockFraction;
    }

    if( ( u8_Loc_initialBlockNum >= MINIMUM_FLASH_GURANTEE_SIZE ) && ( ( u8_Loc_numOfBlocks + u8_Loc_initialBlockNum ) < FLASH_SIZE ) )
    {
        if(u16_Glob_flashKey!=0)   //Checking that the flash enable function is used
        {
            for( u8_Loc_eraseBlockCount = u8_Loc_initialBlockNum ; u8_Loc_eraseBlockCount < ( u8_Loc_initialBlockNum + u8_Loc_numOfBlocks ) ; u8_Loc_eraseBlockCount++ )
            {
                Flash_vErase(u8_Loc_eraseBlockCount);
            }
            // Write one word at a time...
            for ( u32_Loc_dataCounter = 0; u32_Loc_dataCounter < u32_Loc_dataLength; u32_Loc_dataCounter++)
            {
                // Set the data register.  This the word that will be written.
                FMD = u32ptr_Loc_Data[u32_Loc_dataCounter];

                FMA = u32_Loc_flashAddress +  ( u32_Loc_dataCounter * SIZE_OF_WORD );

                // Trigger a write operation...
                FMC = (u16_Glob_flashKey << 16) | 0x1;

                // Poll the WRITE bit until it is cleared.
                while (FMC & 0x1);

            }
        }
    }
}


/*==================================================== Flash Read function ==================================================*/
void Flash_vRead(u32 * u32ptr_Loc_Data, u32 u32_Loc_dataLength,u32 u32_Loc_initialAddress)
{
    u32 u32_Loc_dataCounter;
    // Copy the count of bytes into the target data buffer...
    for ( u32_Loc_dataCounter = 0; u32_Loc_dataCounter < u32_Loc_dataLength; u32_Loc_dataCounter++)
    {
        u32ptr_Loc_Data[u32_Loc_dataCounter] = *( (volatile u32*)(u32_Loc_initialAddress + ( u32_Loc_dataCounter * SIZE_OF_WORD ) ) );
    }

}
