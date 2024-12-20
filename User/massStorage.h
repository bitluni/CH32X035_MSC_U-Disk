#pragma once

#include "ch32x035_usbfs_device.h"
#include "Internal_Flash.h"
#include "SPI_FLASH.h"
#include "SW_UDISK.h"
#include "debug.h"

void initMassStorage()
{
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n",SystemCoreClock);
    Delay_Ms( 10 );
#if (STORAGE_MEDIUM == MEDIUM_SPI_FLASH)
    printf("USBD UDisk Demo\r\nStorage Medium: SPI FLASH \r\n");
    /* SPI flash init */
    FLASH_Port_Init( );
    /* FLASH ID check */
    FLASH_IC_Check( );
#elif (STORAGE_MEDIUM == MEDIUM_INTERAL_FLASH)
    printf("USBD UDisk Demo\r\nStorage Medium: INTERNAL FLASH \r\n");
    Flash_Sector_Count = IFLASH_UDISK_SIZE  / DEF_UDISK_SECTOR_SIZE;
    Flash_Sector_Size = DEF_UDISK_SECTOR_SIZE;
#endif

    /* Enable Udisk */
    Udisk_Capability = Flash_Sector_Count;
    Udisk_Status |= DEF_UDISK_EN_FLAG;

    /* Usb Init */
    USBFS_RCC_Init( );
    USBFS_Device_Init( ENABLE, PWR_VDD_3V3);
    NVIC_EnableIRQ( USBFS_IRQn );
}
