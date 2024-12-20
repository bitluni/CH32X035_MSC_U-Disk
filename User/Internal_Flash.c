/********************************** (C) COPYRIGHT *******************************
 * File Name          : Internal_Flash.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : Internal Flash program
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include "ch32x035.h"
#include "Internal_Flash.h"
#include "ch32x035_flash.h"
uint8_t *lastSector = (uint8_t *)0x08005000;


void IFlash_Prog_512(uint32_t address,uint32_t *pbuf)
{
    //lastSector = address;
    if (address < IFLASH_UDISK_START_ADDR || (address + 511) > IFLASH_UDISK_END_ADDR )
    {
        printf("Error Address %x\n",address);
        return;
    }
    address &= 0x00FFFFFF;
    address |= 0x08000000;
    __disable_irq();
    FLASH_Unlock_Fast();
    FLASH_ErasePage_Fast(address);
    //TODO FLASH_ProgramPage_Fast(address, pbuf);
    FLASH_ROM_WRITE(address, pbuf, 256);
    FLASH_ErasePage_Fast(address + INTERNAL_FLASH_PAGE_SIZE);
    //FLASH_ProgramPage_Fast(address+ INTERNAL_FLASH_PAGE_SIZE, pbuf + INTERNAL_FLASH_PAGE_SIZE / 4);
    FLASH_ROM_WRITE(address+ INTERNAL_FLASH_PAGE_SIZE, pbuf+ INTERNAL_FLASH_PAGE_SIZE / 4, 256);
    FLASH_Lock_Fast();
    __enable_irq();
}

void IFlash_Prog_256(uint32_t address, uint32_t *pbuf)
{
    //lastSector = address;
    if (address < IFLASH_UDISK_START_ADDR || (address + 255) > IFLASH_UDISK_END_ADDR )
    {
        printf("Error Address %x\n",address);
        return;
    }
    address &= 0x00FFFFFF;
    address |= 0x08000000;
    __disable_irq();
    FLASH_Unlock_Fast();
    FLASH_ErasePage_Fast(address);
    //TODO FLASH_ProgramPage_Fast(address, pbuf);
    FLASH_ROM_WRITE(address, pbuf, 256);
    FLASH_Lock_Fast();
    __enable_irq();
}
