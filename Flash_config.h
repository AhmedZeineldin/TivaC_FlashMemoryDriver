/*
 * Flash_config.h
 *
 *  Created on: May 31, 2020
 *      Author: dodo_
 */

#ifndef FLASH_CONFIG_H_
#define FLASH_CONFIG_H_
#include "std_types.h"
//The minimum number of blocks guaranteed for the code to reside in the flash and be protected from being erased and/or overwritten
#define MINIMUM_FLASH_GURANTEE_SIZE     124    //in blocks
#define FLASH_BLOCK_SIZE                1024   //in bytes
#define SIZE_OF_WORD                    4      //in bytes
#define FLASH_SIZE                      256    //in blocks




#endif /* FLASH_CONFIG_H_ */
