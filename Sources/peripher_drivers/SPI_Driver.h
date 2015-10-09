
/**
  ******************************************************************************
  * @Copyright (C), 1997-2015, Hangzhou Gold Electronic Equipment Co., Ltd.
  * @file name: SPI_Driver.h
  * @author: Wangjian
  * @Descriptiuon: Provides a set of functions to help users to use MC9S12 SPI 
  *                ports.This functions include initializing SPI ports,reading 
  *                and writing data by SPI ports.
  * @Others: None
  * @History: 1. Created by Wangjian.
  * @version: V1.0.0
  * @date:    18-Sep-2015

  ******************************************************************************
  * @attention
  *
  * Licensed under GPLv2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.gnu.org/licenses/gpl-2.0.html
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_DRIVER_H
#define __SPI_DRIVER_H


#include <MC9S12XEQ512.h>
#include <hidef.h>
#include "derivative.h"

#include "common.h"

 

 /* Exported types ------------------------------------------------------------*/  

/* MC9S12X serious SPI driver version: 1.0.0 */
#define   SPI_DRIVER_VERSION     (100)

   
   
/* SPI Ports declaration */
typedef enum 
{
    SPI0_Port = 0,            /* SPI0 Ports */
    SPI1_Port,                /* SPI1 Ports */
    SPI2_Port,                /* SPI2 Ports */
}SPIx_PortsType;



/* SPI ports signal remap declaration */
typedef enum
{
    SPI0_PortMPins = 0,       /* SPI0 remap to Port M */
    SPI0_PortSPins,           /* SPI0 remap to Port S */
    
    SPI1_PortHPins,           /* SPI1 remap to Port H */
    SPI1_PortPPins,           /* SPI1 remap to Port P */
    
    SPI2_PortHPins,           /* SPI2 remap to Port H */
    SPI2_PortPPins,           /* SPI2 remap to Port P */
}SPIx_PinsRemap;



/* SPI transport properties declaration */
typedef struct
{
    uint8_t SPI_ALLInterrupt_Enable       :1;       /* SPI total interrupt. 0, disable SPI total interrupt; 1, enable SPI total interrupt; */
    uint8_t SPI_Enable                    :1;       /* SPI module enable. 0, disable SPI module; 1, enable SPI module; */
    uint8_t SPI_TransmitInterrupt_Enable  :1;       /* SPI transport interrupt. 0, disable transport interrupt; 1, enable transport interrupt; */
    uint8_t SPI_MasterOrSlaveMode         :1;       /* SPI works in master mode or slave mode. 0, SPI works in slave mode; 1, SPI works in master mode; */
    uint8_t SPI_CPOL                      :1;       /* SPI clock polarity. 0, SCK in idle status is low; 1, SCK in idle status is high; */
    uint8_t SPI_CPHA                      :1;       /* SPI clock phase. 0, sampling of data occurs at odd edges of the SCK clock; 1, sampling of data occurs at even edges of the SCK clock; */
    uint8_t SPI_LSBFirst                  :1;       /* SPI data transport sequence.0, MSB first; 1, LSB first. */
    uint8_t SPI_TransferLength            :1;       /* SPI data transport length. 0, 8-bit transfer length; 1, 16-bit transfer length; */
    uint8_t SPI_HardwarePCSSelect         :1;       /* SPI CS signal control. 0, not controlLed by SPI but controlLed by GPIO; 1, controlLed by SPI; */
}SPIx_ConfigType;



/* SPI transport speed mode */
typedef enum
{
	High_Speed = 0,                  /* 200Kbps */
	Low_Speed,                       /* 1Mbps */
}SPIxSpeed_Typedef;


#ifdef __cplusplus
extern "C" {
#endif

/* Exported functions ------------------------------------------------------- */


int16_t SPI_Init(SPIx_PortsType SPIx, SPIx_PinsRemap Pins, SPIx_ConfigType *p_Config, SPIxSpeed_Typedef sp_mode);

int16_t SPI_WriteByteData(SPIx_PortsType SPIx, uint8_t Tx_data);

int16_t SPI_ReadByteData(SPIx_PortsType SPIx, uint8_t dummy_data, uint8_t* Rx_data);

int16_t SPI_WriteReadByteData(SPIx_PortsType SPIx, uint8_t Tx_data, uint8_t* Rx_data);


#ifdef __cplusplus
}
#endif

#endif

/*****************************END OF FILE**************************************/