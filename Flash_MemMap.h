/*
 * Flash_MemMap.h
 *
 *  Created on: May 31, 2020
 *      Author: dodo_
 */

#ifndef FLASH_MEMMAP_H_
#define FLASH_MEMMAP_H_
#include "std_types.h"
#define BOOTCFG_REG_BASE_ADDRESS 0x400FE000
#define FLASH_REGS_BASE_ADDRESS  0x400FD000
#define FMA                      *((volatile u32*)(FLASH_REGS_BASE_ADDRESS + 0x000))
#define FMD                      *((volatile u32*)(FLASH_REGS_BASE_ADDRESS + 0x004))
#define FMC                      *((volatile u32*)(FLASH_REGS_BASE_ADDRESS + 0x008))
#define BOOTCFG                  *((volatile u32*)(BOOTCFG_REG_BASE_ADDRESS + 0x1D0))


#endif /* FLASH_MEMMAP_H_ */
