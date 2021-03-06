#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "common.h"
#include "GPIO_Driver.h"
#include "System_Driver.h"
#include "M95160_Driver.h"
#include "SPI_Driver.h"


#include <string.h>
#include "xgate.h"

#pragma push

/* this variable definition is to demonstrate how to share data between XGATE and S12X */
#pragma DATA_SEG SHARED_DATA
volatile int shared_counter; /* volatile because both cores are accessing it. */

/* Two stacks in XGATE core3 */ 
#pragma DATA_SEG XGATE_STK_L
word XGATE_STACK_L[1]; 
#pragma DATA_SEG XGATE_STK_H
word XGATE_STACK_H[1];

#pragma pop

#define ROUTE_INTERRUPT(vec_adr, cfdata)                \
  INT_CFADDR= (vec_adr) & 0xF0;                         \
  INT_CFDATA_ARR[((vec_adr) & 0x0F) >> 1]= (cfdata)

#define SOFTWARETRIGGER0_VEC  0x72 /* vector address= 2 * channel id */

static void SetupXGATE(void) {
  /* initialize the XGATE vector block and
     set the XGVBR register to its start address */
  XGVBR= (unsigned int)(void*__far)(XGATE_VectorTable - XGATE_VECTOR_OFFSET);

  /* switch software trigger 0 interrupt to XGATE */
  ROUTE_INTERRUPT(SOFTWARETRIGGER0_VEC, 0x81); /* RQST=1 and PRIO=1 */

  /* when changing your derivative to non-core3 one please remove next five lines */
  XGISPSEL= 1;
  XGISP31= (unsigned int)(void*__far)(XGATE_STACK_L + 1);
  XGISPSEL= 2;
  XGISP74= (unsigned int)(void*__far)(XGATE_STACK_H + 1);
  XGISPSEL= 0;

  /* enable XGATE mode and interrupts */
  XGMCTL= 0xFBC1; /* XGE | XGFRZ | XGIE */

  /* force execution of software trigger 0 handler */
  XGSWT= 0x0101;
}





void main(void) 
{  
    uint8_t R_S = 0;
    
    uint8_t R_Buffer[16];
    
    uint8_t W_Buffer[16] = {0x23, 0x38, 0x32, 0x19, 0x20, 0x90, 0x55, 0x56,
    0x23, 0x38, 0x32, 0x19, 0x20, 0x90, 0x55, 0x56};
    
    int16_t res = 0xFFu;
    
    (void)SystemClock_Init(BusClock_32MHz);
    
    SetupXGATE();
    
    GPIO_Init(GPIOT, GPIO_Pin6, GPIO_Output);
    GPIO_SetBit(GPIOT, GPIO_Pin6);
    
    M95160_Init();
    
    M95160_WriteStatusRegister(SPI0_Port, 0x00u);
    
    (void)M95160_ReadStatusRegister(SPI0_Port, &R_S);
    
    (void)M95160_WriteSequenceBytesData(SPI0_Port, 0x0060u, W_Buffer, 16);
    
    (void)M95160_ReadSequenceBytesData(SPI0_Port, 0x0060u, R_Buffer, 16);

    EnableInterrupts;

    for(;;) 
    {
    } /* loop forever */
}
