
#ifndef  __M95160_DRIVER_H
#define  __M95160_DRIVER_H

#include <MC9S12XEQ512.h>
#include <hidef.h>
#include "derivative.h"

#include "common.h"
#include "GPIO_Driver.h"

 
/* Exported types ------------------------------------------------------------*/  

/* EEPROM chip M95160 driver version: Rev1.0.0 */
#define   M95160_DRIVER_VERSION     (100)


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

int16_t M95160_ReadStatusRegister(uint8_t* R_Value);

void M95160_WriteStatusRegister(uint8_t W_Value);

int16_t M95160_WriteByteData(int16_t Memory_Addr, uint8_t W_Data);

int16_t M95160_WriteSequenceData(int16_t Memory_Addr, uint8_t* W_Data, uint8_t W_Length);

int16_t M95160_ReadSequenceData(int16_t Memory_Addr, uint8_t* R_Data, uint16_t R_Length);

#ifdef __cplusplus
}
#endif

#endif

/*****************************END OF FILE**************************************/