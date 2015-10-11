/**
  ******************************************************************************
  * @Copyright (C), 1997-2015, Hangzhou Gold Electronic Equipment Co., Ltd.
  * @file name: M95160_Driver.h
  * @author: Wangjian
  * @Descriptiuon: Provide a set of functions about initialize M95160 chip,
  *                writting data to M95160 and reading data from M95160.
  * @Others: None
  * @History: 1. Created by Wangjian.
  *           2. a. Removed Enable M95160 chip Write functon;
  *              b. Changed all API function's name by adding SPI port which 
  *                 user can specified.
  * @version: V1.0.1
  * @date:    11-Nov-2015

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
  
#ifndef  __M95160_DRIVER_H
#define  __M95160_DRIVER_H

#include <MC9S12XEQ512.h>
#include <hidef.h>
#include "derivative.h"

#include "common.h"
#include "GPIO_Driver.h"
#include "SPI_Driver.h"

 
/* Exported types ------------------------------------------------------------*/  

/* EEPROM chip M95160 driver version: Rev1.0.1 */
#define   M95160_DRIVER_VERSION     (101)


#define   M95160_CS_Output()    GPIO_Init(GPIOS, GPIO_Pin7, GPIO_Output)

#define   M95160_CS_HIGH()      GPIO_SetBit(GPIOS, GPIO_Pin7)    

#define   M95160_CS_LOW()       GPIO_ClearBit(GPIOS, GPIO_Pin7)


/* EEPROM command */
#define   WREN    (0x06u)       /* Write Enable */
#define   WRDI    (0x04u)       /* Write Disable */
#define   RDSR    (0x05u)       /* Read Status Register */
#define   WRSR    (0x01u)       /* Write Status Register */
#define   READ    (0x03u)       /* Read from memory array */
#define   WRITE   (0x02u)       /* Write to memory array */


#define   MEMORY_STARTADDRESS    (0x0000u)

#define   MEMORY_ENDADDRESS      (0x07FFu)

#define   PAGEZ_SIZE   (32)

#define   TOTAL_SIZE   (2048)



#ifdef __cplusplus
extern "C" {
#endif

/* Exported functions ------------------------------------------------------- */

void M95160_Init(void);


void M95160_WriteStatusRegister(SPIx_PortsType SPIx, uint8_t W_Value);


int16_t M95160_ReadStatusRegister(SPIx_PortsType SPIx, uint8_t* R_Value);


int16_t M95160_WriteSingleByteData(SPIx_PortsType SPIx, int16_t Memory_Addr, uint8_t W_Data);


int16_t M95160_WriteSequenceBytesData(SPIx_PortsType SPIx, int16_t Memory_Addr, uint8_t* W_Data, uint8_t W_Length);


int16_t M95160_ReadSequenceBytesData(SPIx_PortsType SPIx, int16_t Memory_Addr, uint8_t* R_Data, uint16_t R_Length);


#ifdef __cplusplus
}
#endif

#endif

/*****************************END OF FILE**************************************/