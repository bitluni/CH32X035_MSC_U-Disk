/********************************** (C) COPYRIGHT *******************************
* File Name          : ch32v20x_usbfs_device.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2022/08/20
* Description        : This file provides all the USBFS firmware functions.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

#include "ch32x035_usbfs_device.h"
#include "SW_UDISK.h"
/*******************************************************************************/
/* Variable Definition */
/* Global */
const    uint8_t  *pUSBFS_Descr;

/* Setup Request */
volatile uint8_t  USBFS_SetupReqCode;
volatile uint8_t  USBFS_SetupReqType;
volatile uint16_t USBFS_SetupReqValue;
volatile uint16_t USBFS_SetupReqIndex;
volatile uint16_t USBFS_SetupReqLen;

/* USB Device Status */
volatile uint8_t  USBFS_DevConfig;
volatile uint8_t  USBFS_DevAddr;
volatile uint8_t  USBFS_DevSleepStatus;
volatile uint8_t  USBFS_DevEnumStatus;

/* Endpoint Buffer */
__attribute__ ((aligned(4))) uint8_t USBFS_EP0_4Buf[ DEF_USBD_UEP0_SIZE ];    //ep0(64)
__attribute__ ((aligned(4))) uint8_t UDisk_In_Buf[ DEF_UDISK_PACK_64 ];
__attribute__ ((aligned(4))) uint8_t UDisk_Out_Buf[ DEF_UDISK_PACK_64 ];

/* USB IN Endpoint Busy Flag */
volatile uint8_t  USBFS_Endp_Busy[ DEF_UEP_NUM ];

/******************************************************************************/
/* Interrupt Service Routine Declaration*/
void USBFS_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*********************************************************************
 * @fn      USBFS_RCC_Init
 *
 * @brief   Initializes the usbfs clock configuration.
 *
 * @return  none
 */
void USBFS_RCC_Init(void)
{
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE );
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_USBFS, ENABLE );
}

/*********************************************************************
 * @fn      USBFS_Device_Endp_Init
 *
 * @brief   Initializes USB device endpoints.
 *
 * @return  none
 */
void USBFS_Device_Endp_Init( void )
{

    USBFSD->UEP2_3_MOD = USBFS_UEP2_TX_EN|USBFS_UEP3_RX_EN;

    USBFSD->UEP0_DMA = (uint32_t)USBFS_EP0_4Buf;
    USBFSD->UEP2_DMA = (uint32_t)UDisk_In_Buf;
    USBFSD->UEP3_DMA = (uint32_t)UDisk_Out_Buf;

    /* TODO
    USBFSD->UEP0_RX_CTRL = USBFS_UEP_R_RES_ACK;
    USBFSD->UEP3_RX_CTRL = USBFS_UEP_R_RES_ACK;

    USBFSD->UEP0_TX_CTRL = USBFS_UEP_T_RES_NAK;
    USBFSD->UEP2_TX_CTRL = USBFS_UEP_T_RES_NAK;
*/
    USBFSD->UEP0_CTRL_H = USBFS_UEP_R_RES_ACK | USBFS_UEP_T_RES_NAK;
    USBFSD->UEP3_CTRL_H = USBFS_UEP_R_RES_ACK | USBFS_UEP_T_RES_NAK;

    USBFSD->UEP2_TX_LEN = 0;

    /* Clear End-points Busy Status */
    for(uint8_t i=0; i<DEF_UEP_NUM; i++ )
    {
        USBFS_Endp_Busy[ i ] = 0;
    }
}

/*********************************************************************
 * @fn      GPIO_USB_INIT
 *
 * @brief   Initializes USB GPIO.
 *
 * @return  none
 */
void GPIO_USB_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_16;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_17;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      USBFS_Device_Init
 *
 * @brief   Initializes USB device.
 *
 * @return  none
 */
void USBFS_Device_Init( FunctionalState sta , PWR_VDD VDD_Voltage)
{
    if( VDD_Voltage == PWR_VDD_5V )
    {
        AFIO->CTLR = (AFIO->CTLR & ~(UDP_PUE_MASK | UDM_PUE_MASK | USB_PHY_V33)) | UDP_PUE_10K | USB_IOEN;
    }
    else
    {
        AFIO->CTLR = (AFIO->CTLR & ~(UDP_PUE_MASK | UDM_PUE_MASK )) | USB_PHY_V33 | UDP_PUE_1K5 | USB_IOEN;
    }

    if( sta )
    {
        GPIO_USB_INIT();
        USBFSD->BASE_CTRL = 0x00;
        USBFS_Device_Endp_Init( );
        USBFSD->DEV_ADDR = 0x00;
        USBFSD->BASE_CTRL = USBFS_UC_DEV_PU_EN | USBFS_UC_INT_BUSY | USBFS_UC_DMA_EN;
        USBFSD->INT_FG = 0xff;
        USBFSD->UDEV_CTRL = USBFS_UD_PD_DIS | USBFS_UD_PORT_EN;
        USBFSD->INT_EN = USBFS_UIE_SUSPEND | USBFS_UIE_BUS_RST | USBFS_UIE_TRANSFER;
        NVIC_EnableIRQ( USBFS_IRQn );
    }
    else
    {
        USBFSD->BASE_CTRL = USBFS_UC_RESET_SIE | USBFS_UC_CLR_ALL;
        Delay_Us( 10 );
        USBFSD->BASE_CTRL = 0x00;
        NVIC_DisableIRQ( USBFS_IRQn );
    }
}

uint8_t* USBFSD_UEP_BUF(int endp)
{
    switch(endp)
    {
        case DEF_UEP0:
            return (uint8_t*)USBFSD->UEP0_DMA;
        case DEF_UEP1:
            return (uint8_t*)USBFSD->UEP1_DMA;
        case DEF_UEP2:
            return (uint8_t*)USBFSD->UEP2_DMA;
        case DEF_UEP3:
            return (uint8_t*)USBFSD->UEP3_DMA;
        case DEF_UEP4:  //TODO is this correct?
            return (uint8_t*)USBFSD->UEP0_DMA;
        case DEF_UEP5:
            return (uint8_t*)USBFSD->UEP5_DMA;
        case DEF_UEP6:
            return (uint8_t*)USBFSD->UEP6_DMA;
        case DEF_UEP7:
            return (uint8_t*)USBFSD->UEP7_DMA;
    }
    return 0;
}

int USBFS_Endpoint_Mode_Get(int endp)
{
    switch(endp)
    {
        case DEF_UEP0:
            //TODO 0
            return 0;
        case DEF_UEP1:
            return USBFSD->UEP4_1_MOD >> 4;
        case DEF_UEP2:
            return USBFSD->UEP2_3_MOD & 0xf;
        case DEF_UEP3:
            return USBFSD->UEP2_3_MOD >> 4;
        case DEF_UEP4:
            return USBFSD->UEP4_1_MOD & 0xf;
        case DEF_UEP5:
            return (USBFSD->UEP567_MOD & 0x3) << 2;
        case DEF_UEP6:
            return ((USBFSD->UEP567_MOD >> 2) & 0x3) << 2;
        case DEF_UEP7:
            return ((USBFSD->UEP567_MOD >> 4) & 0x3) << 2;
        //TODO 8-15
    }
    return 0;
}

void USBFSD_UEP_DMA_Set(int endp, uint32_t addr)
{
    switch(endp)
    {
        case DEF_UEP0:
            USBFSD->UEP0_DMA = addr;
            break;
        case DEF_UEP1:
            USBFSD->UEP1_DMA = addr;
            break;
        case DEF_UEP2:
            USBFSD->UEP2_DMA = addr;
            break;
        case DEF_UEP3:
            USBFSD->UEP3_DMA = addr;
            break;
        case DEF_UEP5:
            USBFSD->UEP5_DMA = addr;
            break;
        case DEF_UEP6:
            USBFSD->UEP6_DMA = addr;
            break;
        case DEF_UEP7:
            USBFSD->UEP7_DMA = addr;
            break;
    }
}

void USBFSD_UEP_TLEN_Set(int endp, int len)
{
    switch(endp)
    {
        case DEF_UEP0:
            USBFSD->UEP0_TX_LEN = len;
            break;
        case DEF_UEP1:
            USBFSD->UEP1_TX_LEN = len;
            break;
        case DEF_UEP2:
            USBFSD->UEP2_TX_LEN = len;
            break;
        case DEF_UEP3:
            USBFSD->UEP3_TX_LEN = len;
            break;
        case DEF_UEP4:
            USBFSD->UEP4_TX_LEN = len;
            break;
        case DEF_UEP5:
            USBFSD->UEP5_TX_LEN = len;
            break;
        case DEF_UEP6:
            USBFSD->UEP6_TX_LEN = len;
            break;
        case DEF_UEP7:
            USBFSD->UEP7_TX_LEN = len;
            break;
    }
}

void USBFSD_UEP_CTRL_Set(int endp, int val)
{
    switch(endp)
    {
        case DEF_UEP0:
            USBFSD->UEP0_CTRL_H = val;
            break;
        case DEF_UEP1:
            USBFSD->UEP1_CTRL_H = val;
            break;
        case DEF_UEP2:
            USBFSD->UEP2_CTRL_H = val;
            break;
        case DEF_UEP3:
            USBFSD->UEP3_CTRL_H = val;
            break;
        case DEF_UEP4:
            USBFSD->UEP4_CTRL_H = val;
            break;
        case DEF_UEP5:
            USBFSD->UEP5_CTRL_H = val;
            break;
        case DEF_UEP6:
            USBFSD->UEP6_CTRL_H = val;
            break;
        case DEF_UEP7:
            USBFSD->UEP7_CTRL_H = val;
            break;
    }
}

uint16_t USBFSD_UEP_CTRL_Get(int endp)
{
    switch(endp)
    {
        case DEF_UEP0:
            return USBFSD->UEP0_CTRL_H;
        case DEF_UEP1:
            return USBFSD->UEP1_CTRL_H;
        case DEF_UEP2:
            return USBFSD->UEP2_CTRL_H;
        case DEF_UEP3:
            return USBFSD->UEP3_CTRL_H;
        case DEF_UEP4:
            return USBFSD->UEP4_CTRL_H;
        case DEF_UEP5:
            return USBFSD->UEP5_CTRL_H;
        case DEF_UEP6:
            return USBFSD->UEP6_CTRL_H;
        case DEF_UEP7:
            return USBFSD->UEP7_CTRL_H;
    }
}

/*********************************************************************
 * @fn      USBFS_Endp_DataUp
 *
 * @brief   USBFS device data upload
 *
 * @return  none
 */
uint8_t USBFS_Endp_DataUp(uint8_t endp, uint8_t *pbuf, uint16_t len, uint8_t mod)
{
    uint8_t endp_mode;
    uint8_t buf_load_offset;

    /* DMA config, endp_ctrl config, endp_len config */
    if( (endp >= DEF_UEP1) && (endp <= DEF_UEP7) )
    {
        if( USBFS_Endp_Busy[ endp ] == 0 )
        {
            endp_mode = USBFS_Endpoint_Mode_Get(endp);
            if( endp_mode & USBFSD_UEP_TX_EN )
            {
                if( endp_mode & USBFSD_UEP_RX_EN )
                {
                    buf_load_offset = 64;
                }
                else
                {
                    buf_load_offset = 0;
                }

                if( buf_load_offset == 0 )
                {
                    if( mod == DEF_UEP_DMA_LOAD )
                    {
                        /* DMA mode */
                        //TODO no endp 4
                        USBFSD_UEP_DMA_Set(endp, (uint16_t)(uint32_t)pbuf);
                    }
                    else
                    {
                        /* copy mode */
                        memcpy( USBFSD_UEP_BUF(endp), pbuf, len );
                    }
                }
                else
                {
                    memcpy( USBFSD_UEP_BUF(endp)+buf_load_offset, pbuf, len );
                }
                /* Set end-point busy */
                USBFS_Endp_Busy[ endp ] = 0x01;
                /* tx length */
                USBFSD_UEP_TLEN_Set(endp, len);
                /* response ack */
                USBFSD_UEP_CTRL_Set(endp, (USBFSD_UEP_CTRL_Get(endp) & ~USBFS_UEP_T_RES_MASK) | USBFS_UEP_T_RES_ACK);
            }
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }
    return 0;
}


/*********************************************************************
 * @fn      USBFS_IRQHandler
 *
 * @brief   This function handles HD-FS exception.
 *
 * @return  none
 */
void USBFS_IRQHandler( void )
{
    uint8_t  intflag, intst, errflag;
    uint16_t len;

    intflag = USBFSD->INT_FG;
    intst   = USBFSD->INT_ST;

    if( intflag & USBFS_UIF_TRANSFER )
    {
        switch (intst & USBFS_UIS_TOKEN_MASK)
        {
            /* data-in stage processing */
            case USBFS_UIS_TOKEN_IN:
                switch ( intst & ( USBFS_UIS_TOKEN_MASK | USBFS_UIS_ENDP_MASK ) )
                {
                    /* end-point 0 data in interrupt */
                    case USBFS_UIS_TOKEN_IN | DEF_UEP0:
                        if( USBFS_SetupReqLen == 0 )
                        {
                            //TODO USBFSD->UEP0_RX_CTRL = USBFS_UEP_R_TOG | USBFS_UEP_R_RES_ACK;
                            USBFSD->UEP0_CTRL_H = USBFS_UEP_R_TOG | USBFS_UEP_R_RES_ACK;
                        }
                        if ( ( USBFS_SetupReqType & USB_REQ_TYP_MASK ) != USB_REQ_TYP_STANDARD )
                        {
                            /* Non-standard request endpoint 0 Data upload */
                        }
                        else
                        {
                            /* Standard request endpoint 0 Data upload */
                            switch( USBFS_SetupReqCode )
                            {
                                case USB_GET_DESCRIPTOR:
                                        len = USBFS_SetupReqLen >= DEF_USBD_UEP0_SIZE ? DEF_USBD_UEP0_SIZE : USBFS_SetupReqLen;
                                        memcpy( USBFS_EP0_4Buf, pUSBFS_Descr, len );
                                        USBFS_SetupReqLen -= len;
                                        pUSBFS_Descr += len;
                                        USBFSD->UEP0_TX_LEN   = len;
                                        //TODO USBFSD->UEP0_TX_CTRL ^= USBFS_UEP_T_TOG;
                                        USBFSD->UEP0_CTRL_H ^= USBFS_UEP_T_TOG;
                                        break;

                                case USB_SET_ADDRESS:
                                        USBFSD->DEV_ADDR = (USBFSD->DEV_ADDR & USBFS_UDA_GP_BIT) | USBFS_DevAddr;
                                        break;

                                default:
                                        break;
                            }
                        }
                        break;

                    /* end-point 2 data in interrupt */
                    case ( USBFS_UIS_TOKEN_IN | DEF_UEP2 ):
/*TODO                        USBFSD->UEP2_TX_CTRL ^= USBFS_UEP_T_TOG;
                        USBFSD->UEP2_TX_CTRL = (USBFSD->UEP2_TX_CTRL & ~USBFS_UEP_T_RES_MASK) | USBFS_UEP_T_RES_NAK;*/
                        USBFSD->UEP2_CTRL_H ^= USBFS_UEP_T_TOG;
                        USBFSD->UEP2_CTRL_H = (USBFSD->UEP2_CTRL_H & ~USBFS_UEP_T_RES_MASK) | USBFS_UEP_T_RES_NAK;
                        USBFS_Endp_Busy[ DEF_UEP2 ] = 0;
						UDISK_In_EP_Deal();
                        break;
                    default :
                        break;
                }
                break;

            /* data-out stage processing */
            case USBFS_UIS_TOKEN_OUT:
                switch ( intst & ( USBFS_UIS_TOKEN_MASK | USBFS_UIS_ENDP_MASK ) )
                {
                    /* end-point 0 data out interrupt */
                    case USBFS_UIS_TOKEN_OUT | DEF_UEP0:
                        len = USBFSD->RX_LEN;
                        if ( intst & USBFS_UIS_TOG_OK )
                        {
                            if ( ( USBFS_SetupReqType & USB_REQ_TYP_MASK ) != USB_REQ_TYP_STANDARD )
                            {
                                /* Non-standard request end-point 0 Data download */
                                /* Add your code here */
                            }
                            else
                            {
                                /* Standard request end-point 0 Data download */
                                /* Add your code here */
                            }
                            if( USBFS_SetupReqLen == 0 )
                            {
                                USBFSD->UEP0_TX_LEN  = 0;
//TODO                                USBFSD->UEP0_TX_CTRL = USBFS_UEP_T_TOG | USBFS_UEP_T_RES_ACK;
                                USBFSD->UEP0_CTRL_H = USBFS_UEP_T_TOG | USBFS_UEP_T_RES_ACK;
                            }
                        }
                        break;

                    /* end-point 3 data out interrupt */
                    case USBFS_UIS_TOKEN_OUT | DEF_UEP3:
                        if ( intst & USBFS_UIS_TOG_OK )
                        {
                            len = USBFSD->RX_LEN;
/*TODO                            USBFSD->UEP3_RX_CTRL ^= USBFS_UEP_R_TOG;
                            USBFSD->UEP3_RX_CTRL = (USBFSD->UEP3_RX_CTRL & ~USBFS_UEP_R_RES_MASK) | USBFS_UEP_R_RES_NAK;*/
                            USBFSD->UEP3_CTRL_H ^= USBFS_UEP_R_TOG;
                            USBFSD->UEP3_CTRL_H = (USBFSD->UEP3_CTRL_H & ~USBFS_UEP_R_RES_MASK) | USBFS_UEP_R_RES_NAK;
                            UDISK_Out_EP_Deal(UDisk_Out_Buf,len);
//TODO                            USBFSD->UEP3_RX_CTRL = (USBFSD->UEP3_RX_CTRL & ~USBFS_UEP_R_RES_MASK) | USBFS_UEP_R_RES_ACK;
                            USBFSD->UEP3_CTRL_H = (USBFSD->UEP3_CTRL_H & ~USBFS_UEP_R_RES_MASK) | USBFS_UEP_R_RES_ACK;
                        }
                        break;
                }
                break;

            /* Setup stage processing */
            case USBFS_UIS_TOKEN_SETUP:
/*                USBFSD->UEP0_TX_CTRL = USBFS_UEP_T_TOG|USBFS_UEP_T_RES_NAK;
                USBFSD->UEP0_RX_CTRL = USBFS_UEP_R_TOG|USBFS_UEP_R_RES_NAK;*/
                USBFSD->UEP0_CTRL = USBFS_UEP_T_TOG|USBFS_UEP_T_RES_NAK;
                USBFSD->UEP0_CTRL = USBFS_UEP_R_TOG|USBFS_UEP_R_RES_NAK;
                /* Store All Setup Values */
                USBFS_SetupReqType  = pUSBFS_SetupReqPak->bRequestType;
                USBFS_SetupReqCode  = pUSBFS_SetupReqPak->bRequest;
                USBFS_SetupReqLen   = pUSBFS_SetupReqPak->wLength;
                USBFS_SetupReqValue = pUSBFS_SetupReqPak->wValue;
                USBFS_SetupReqIndex = pUSBFS_SetupReqPak->wIndex;
                len = 0;
                errflag = 0;
                if ( ( USBFS_SetupReqType & USB_REQ_TYP_MASK ) != USB_REQ_TYP_STANDARD )
                {
                    /* usb non-standard request processing */
                    if (( USBFS_SetupReqType & USB_REQ_TYP_MASK ) == USB_REQ_TYP_CLASS)
                    {
                        if (USBFS_SetupReqCode == CMD_UDISK_GET_MAX_LUN)
                        {
                            USBFS_EP0_4Buf[0] = 0;
                            pUSBFS_Descr = (uint8_t*)USBFS_EP0_4Buf;
                            len = 1;
                        }
                        else if (USBFS_SetupReqCode == CMD_UDISK_RESET)
                        {
                            /* UDisk Reset */
                            Udisk_Sense_Key = 0x00;
                            Udisk_Sense_ASC = 0x00;
                            Udisk_CSW_Status = 0x00;
                            Udisk_Transfer_Status = 0x00;
                            UDISK_Transfer_DataLen = 0x00;
                        }
                        else
                        {
                            errflag = 0xFF;
                        }
                    }
                    else
                    {
                        errflag = 0xFF;
                    }

                }
                else
                {
                    /* usb standard request processing */
                    switch( USBFS_SetupReqCode )
                    {
                        /* get device/configuration/string/report/... descriptors */
                        case USB_GET_DESCRIPTOR:
                            switch( (uint8_t)( USBFS_SetupReqValue >> 8 ) )
                            {
                                /* get usb device descriptor */
                                case USB_DESCR_TYP_DEVICE:
                                    pUSBFS_Descr = MyDevDescr;
                                    len = DEF_USBD_DEVICE_DESC_LEN;
                                    break;

                                /* get usb configuration descriptor */
                                case USB_DESCR_TYP_CONFIG:
                                    pUSBFS_Descr = MyCfgDescr;
                                    len = DEF_USBD_CONFIG_DESC_LEN;
                                    break;

                                /* get usb string descriptor */
                                case USB_DESCR_TYP_STRING:
                                    switch( (uint8_t)( USBFS_SetupReqValue & 0xFF ) )
                                    {
                                        /* Descriptor 0, Language descriptor */
                                        case DEF_STRING_DESC_LANG:
                                            pUSBFS_Descr = MyLangDescr;
                                            len = DEF_USBD_LANG_DESC_LEN;
                                            break;

                                        /* Descriptor 1, Manufacturers String descriptor */
                                        case DEF_STRING_DESC_MANU:
                                            pUSBFS_Descr = MyManuInfo;
                                            len = DEF_USBD_MANU_DESC_LEN;
                                            break;

                                        /* Descriptor 2, Product String descriptor */
                                        case DEF_STRING_DESC_PROD:
                                            pUSBFS_Descr = MyProdInfo;
                                            len = DEF_USBD_PROD_DESC_LEN;
                                            break;

                                        /* Descriptor 3, Serial-number String descriptor */
                                        case DEF_STRING_DESC_SERN:
                                            pUSBFS_Descr = MySerNumInfo;
                                            len = DEF_USBD_SN_DESC_LEN;
                                            break;

                                        default:
                                            errflag = 0xFF;
                                            break;
                                    }
                                    break;

                                default :
                                    errflag = 0xFF;
                                    break;
                            }

                            /* Copy Descriptors to Endp0 DMA buffer */
                            if( USBFS_SetupReqLen>len )
                            {
                                USBFS_SetupReqLen = len;
                            }
                            len = (USBFS_SetupReqLen >= DEF_USBD_UEP0_SIZE) ? DEF_USBD_UEP0_SIZE : USBFS_SetupReqLen;
                            memcpy( USBFS_EP0_4Buf, pUSBFS_Descr, len );
                            pUSBFS_Descr += len;
                            break;

                        /* Set usb address */
                        case USB_SET_ADDRESS:
                            USBFS_DevAddr = (uint8_t)( USBFS_SetupReqValue & 0xFF );
                            break;

                        /* Get usb configuration now set */
                        case USB_GET_CONFIGURATION:
                            USBFS_EP0_4Buf[0] = USBFS_DevConfig;
                            if ( USBFS_SetupReqLen > 1 )
                            {
                                USBFS_SetupReqLen = 1;
                            }
                            break;

                        /* Set usb configuration to use */
                        case USB_SET_CONFIGURATION:
                            USBFS_DevConfig = (uint8_t)( USBFS_SetupReqValue & 0xFF );
                            USBFS_DevEnumStatus = 0x01;
                            break;

                        /* Clear or disable one usb feature */
                        case USB_CLEAR_FEATURE:
                            if ( ( USBFS_SetupReqType & USB_REQ_RECIP_MASK ) == USB_REQ_RECIP_DEVICE )
                            {
                                /* clear one device feature */
                                if( (uint8_t)( USBFS_SetupReqValue & 0xFF ) == USB_REQ_FEAT_REMOTE_WAKEUP )
                                {
                                    /* clear usb sleep status, device not prepare to sleep */
                                    USBFS_DevSleepStatus &= ~0x01;
                                }
                            }
                            else if( ( USBFS_SetupReqType & USB_REQ_RECIP_MASK ) == USB_REQ_RECIP_ENDP )
                            {
                                /* Clear End-point Feature */
                                if( (uint8_t)( USBFS_SetupReqValue & 0xFF ) == USB_REQ_FEAT_ENDP_HALT )
                                {
                                    switch( (uint8_t)( USBFS_SetupReqIndex & 0xFF ) )
                                    {
                                        case ( DEF_UEP_IN | DEF_UEP2 ):
                                            /* Set End-point 2 IN NAK */
//TODO                                            USBFSD->UEP2_TX_CTRL = USBFS_UEP_T_RES_NAK;
                                            USBFSD->UEP2_CTRL = USBFS_UEP_T_RES_NAK;
                                            /* upload CSW */
                                            if( Udisk_Transfer_Status & DEF_UDISK_CSW_UP_FLAG )
                                            {
                                                UDISK_Up_CSW( );
                                            }
                                            break;
                                        case ( DEF_UEP_OUT | DEF_UEP3 ):
                                            /* Set End-point 3 OUT ACK */
//TODO                                            USBFSD->UEP3_RX_CTRL = USBFS_UEP_R_RES_ACK;
                                            USBFSD->UEP3_CTRL_H = USBFS_UEP_R_RES_ACK;
                                            /* upload CSW */
                                            if( Udisk_Transfer_Status & DEF_UDISK_CSW_UP_FLAG )
                                            {
                                                UDISK_Up_CSW( );
                                            }
                                            break;
                                        default:
                                            errflag = 0xFF;
                                            break;
                                    }
                                }
                                else
                                {
                                    errflag = 0xFF;
                                }
                            }
                            else
                            {
                                errflag = 0xFF;
                            }
                            break;

                        /* set or enable one usb feature */
                        case USB_SET_FEATURE:
                            if( ( USBFS_SetupReqType & USB_REQ_RECIP_MASK ) == USB_REQ_RECIP_DEVICE )
                            {
                                /* Set Device Feature */
                                if( (uint8_t)( USBFS_SetupReqValue & 0xFF ) == USB_REQ_FEAT_REMOTE_WAKEUP )
                                {
                                    if( MyCfgDescr[ 7 ] & 0x20 )
                                    {
                                        /* Set Wake-up flag, device prepare to sleep */
                                        USBFS_DevSleepStatus |= 0x01;
                                    }
                                    else
                                    {
                                        errflag = 0xFF;
                                    }
                                }
                                else
                                {
                                    errflag = 0xFF;
                                }
                            }
                            else if( ( USBFS_SetupReqType & USB_REQ_RECIP_MASK ) == USB_REQ_RECIP_ENDP )
                            {
                                /* Set End-point Feature */
                                if( (uint8_t)( USBFS_SetupReqValue & 0xFF ) == USB_REQ_FEAT_ENDP_HALT )
                                {
                                    /* Set end-points status stall */
                                    switch( (uint8_t)( USBFS_SetupReqIndex & 0xFF ) )
                                    {
                                        case ( DEF_UEP_IN | DEF_UEP2 ):
                                            /* Set End-point 2 IN STALL */
//TODO                                            USBFSD->UEP2_TX_CTRL = ( USBFSD->UEP2_TX_CTRL & ~USBFS_UEP_T_RES_MASK ) | USBFS_UEP_T_RES_STALL;
                                            USBFSD->UEP2_CTRL_H = ( USBFSD->UEP2_CTRL_H & ~USBFS_UEP_T_RES_MASK ) | USBFS_UEP_T_RES_STALL;
                                            break;

                                        case ( DEF_UEP_OUT | DEF_UEP3 ):
                                            /* Set End-point 3 OUT STALL */
//TODO                                            USBFSD->UEP3_RX_CTRL = ( USBFSD->UEP3_RX_CTRL & ~USBFS_UEP_R_RES_MASK ) | USBFS_UEP_R_RES_STALL;
                                            USBFSD->UEP3_CTRL_H = ( USBFSD->UEP3_CTRL_H & ~USBFS_UEP_R_RES_MASK ) | USBFS_UEP_R_RES_STALL;
                                            break;

                                        default:
                                            errflag = 0xFF;
                                            break;
                                    }
                                }
                                else
                                {
                                    errflag = 0xFF;
                                }
                            }
                            else
                            {
                                errflag = 0xFF;
                            }
                            break;

                        /* This request allows the host to select another setting for the specified interface  */
                        case USB_GET_INTERFACE:
                            USBFS_EP0_4Buf[0] = 0x00;
                            if ( USBFS_SetupReqLen > 1 )
                            {
                                USBFS_SetupReqLen = 1;
                            }
                            break;

                        case USB_SET_INTERFACE:
                            break;

                        /* host get status of specified device/interface/end-points */
                        case USB_GET_STATUS:
                            USBFS_EP0_4Buf[ 0 ] = 0x00;
                            USBFS_EP0_4Buf[ 1 ] = 0x00;
                            if ( ( USBFS_SetupReqType & USB_REQ_RECIP_MASK ) == USB_REQ_RECIP_DEVICE )
                            {
                                if( USBFS_DevSleepStatus & 0x01 )
                                {
                                    USBFS_EP0_4Buf[ 0 ] = 0x02;
                                }
                            }
                            else if( ( USBFS_SetupReqType & USB_REQ_RECIP_MASK ) == USB_REQ_RECIP_ENDP )
                            {
                                switch( (uint8_t)( USBFS_SetupReqIndex & 0xFF ) )
                                {
                                    case ( DEF_UEP_IN | DEF_UEP2 ):
//TODO                                        if( ( (USBFSD->UEP2_TX_CTRL) & USBFS_UEP_T_RES_MASK ) == USBFS_UEP_T_RES_STALL )
                                        if( ( (USBFSD->UEP2_CTRL_H) & USBFS_UEP_T_RES_MASK ) == USBFS_UEP_T_RES_STALL )
                                        {
                                            USBFS_EP0_4Buf[ 0 ] = 0x01;
                                        }
                                        break;

                                    case ( DEF_UEP_OUT | DEF_UEP3 ):
//TODO                                        if( ( (USBFSD->UEP3_RX_CTRL) & USBFS_UEP_R_RES_MASK ) == USBFS_UEP_R_RES_STALL )
                                        if( ( (USBFSD->UEP3_CTRL_H) & USBFS_UEP_R_RES_MASK ) == USBFS_UEP_R_RES_STALL )
                                        {
                                            USBFS_EP0_4Buf[ 0 ] = 0x01;
                                        }
                                        break;

                                    default:
                                        errflag = 0xFF;
                                        break;
                                }
                            }
                            else
                            {
                                errflag = 0xFF;
                            }

                            if( USBFS_SetupReqLen > 2 )
                            {
                                USBFS_SetupReqLen = 2;
                            }

                            break;

                        default:
                            errflag = 0xFF;
                            break;
                    }
                }
                /* errflag = 0xFF means a request not support or some errors occurred, else correct */
                if( errflag == 0xFF)
                {
                    /* if one request not support, return stall */
/*TODO                    USBFSD->UEP0_TX_CTRL = USBFS_UEP_T_TOG|USBFS_UEP_T_RES_STALL;
                    USBFSD->UEP0_RX_CTRL = USBFS_UEP_R_TOG|USBFS_UEP_R_RES_STALL;*/
                    USBFSD->UEP0_CTRL_H = USBFS_UEP_T_TOG|USBFS_UEP_T_RES_STALL;
                    USBFSD->UEP0_CTRL_H = USBFS_UEP_R_TOG|USBFS_UEP_R_RES_STALL;
                }
                else
                {
                    /* end-point 0 data Tx/Rx */
                    if( USBFS_SetupReqType & DEF_UEP_IN )
                    {
                        /* tx */
                        len = (USBFS_SetupReqLen>DEF_USBD_UEP0_SIZE) ? DEF_USBD_UEP0_SIZE : USBFS_SetupReqLen;
                        USBFS_SetupReqLen -= len;
                        USBFSD->UEP0_TX_LEN  = len;
//TODO                        USBFSD->UEP0_TX_CTRL = USBFS_UEP_T_TOG|USBFS_UEP_T_RES_ACK;
                        USBFSD->UEP0_CTRL_H = USBFS_UEP_T_TOG|USBFS_UEP_T_RES_ACK;
                    }
                    else
                    {
                        /* rx */
                        if( USBFS_SetupReqLen == 0 )
                        {
                            USBFSD->UEP0_TX_LEN  = 0;
//TODO                            USBFSD->UEP0_TX_CTRL = USBFS_UEP_T_TOG|USBFS_UEP_T_RES_ACK;
                            USBFSD->UEP0_CTRL_H = USBFS_UEP_T_TOG|USBFS_UEP_T_RES_ACK;
                        }
                        else
                        {
//                            USBFSD->UEP0_RX_CTRL = USBFS_UEP_R_TOG|USBFS_UEP_R_RES_ACK;
                            USBFSD->UEP0_CTRL_H = USBFS_UEP_R_TOG|USBFS_UEP_R_RES_ACK;
                        }
                    }
                }
                break;

            default :
                break;
        }
        USBFSD->INT_FG = USBFS_UIF_TRANSFER;
    }
    else if( intflag & USBFS_UIF_BUS_RST )
    {
        /* usb reset interrupt processing */
        USBFS_DevConfig = 0;
        USBFS_DevAddr = 0;
        USBFS_DevSleepStatus = 0;
        USBFS_DevEnumStatus = 0;

        USBFSD->DEV_ADDR = 0;
        USBFS_Device_Endp_Init( );
        USBFSD->INT_FG = USBFS_UIF_BUS_RST;
    }
    else if( intflag & USBFS_UIF_SUSPEND )
    {
        USBFSD->INT_FG = USBFS_UIF_SUSPEND;
        Delay_Us(10);
        /* usb suspend interrupt processing */
        if ( USBFSD->MIS_ST & USBFS_UMS_SUSPEND )
        {
            USBFS_DevSleepStatus |= 0x02;
            if( USBFS_DevSleepStatus == 0x03 )
            {
                /* Handling usb sleep here */
            }
        }
        else
        {
            USBFS_DevSleepStatus &= ~0x02;
        }
    }
    else
    {
        /* other interrupts */
        USBFSD->INT_FG = intflag;
    }
}

/*********************************************************************
 * @fn      USBFS_Send_Resume
 *
 * @brief   USBFS device sends wake-up signal to host
 *
 * @return  none
 */
void USBFS_Send_Resume(void)
{
    USBFSD->UDEV_CTRL ^= USBFS_UD_LOW_SPEED;
    Delay_Ms( 5 );
    USBFSD->UDEV_CTRL ^= USBFS_UD_LOW_SPEED;
    Delay_Ms( 1 );
}

