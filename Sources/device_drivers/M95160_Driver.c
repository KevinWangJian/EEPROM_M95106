

#include "M95160_Driver.h"
#include "SPI_Driver.h"
#include "GPIO_Driver.h"




void M95160_Init(void) 
{
    SPIx_ConfigType spi_config;
    
    spi_config.SPI_ALLInterrupt_Enable = 0;
    spi_config.SPI_CPHA = 0;
    spi_config.SPI_CPOL = 0;
    spi_config.SPI_Enable = 1;
    spi_config.SPI_HardwarePCSSelect = 0;
    spi_config.SPI_LSBFirst = 0;
    spi_config.SPI_MasterOrSlaveMode = 1;
    spi_config.SPI_TransferLength = 0;
    spi_config.SPI_TransmitInterrupt_Enable = 0;
    
    (void)SPI_Init(SPI0_Port, SPI0_PortSPins, &spi_config, High_Speed);
    
    M95160_CS_Output();
    
    M95160_CS_LOW();
}



static void M95160_WriteEnable(void) 
{
    M95160_CS_LOW();
    
    (void)SPI_WriteByteData(SPI0_Port, WREN);
    
    M95160_CS_HIGH();   
}



void M95160_WriteStatusRegister(uint8_t W_Value) 
{
    M95160_WriteEnable();
    
    M95160_CS_LOW();
    
    (void)SPI_WriteByteData(SPI0_Port, WRSR);
    
    (void)SPI_WriteByteData(SPI0_Port, W_Value);
    
    M95160_CS_HIGH();    
}



int16_t M95160_ReadStatusRegister(uint8_t* R_Value) 
{
    uint16_t Time_Count = 0;
    
    M95160_CS_LOW();
    
    (void)SPI_WriteByteData(SPI0_Port, RDSR);
    
    do 
    {
        (void)SPI_ReadByteData(SPI0_Port, 0xFFu, R_Value);
        
        Time_Count++;
        
    }while (((*R_Value & 0x01) != 0) && (Time_Count < 0xFFFFu));
    
    if (Time_Count >= 0xFFFFu) 
    {
        M95160_CS_HIGH();
        
        return -1;
    }

    M95160_CS_HIGH();
    
    return 0;
}

       
       



int16_t M95160_WriteByteData(int16_t Memory_Addr, uint8_t W_Data) 
{
    uint8_t Address[2];
    uint8_t i,ret_val;
    
    if ((Memory_Addr < MEMORY_STARTADDRESS) || (Memory_Addr > MEMORY_ENDADDRESS))return -1;
    
    Address[0] = (uint8_t)((Memory_Addr >> 8) & 0x00FFu);
    Address[1] = (uint8_t)(Memory_Addr & 0x00FFu);
    
    if (M95160_ReadStatusRegister(&ret_val) != 0)return -1;
    
    M95160_WriteEnable();
    
    M95160_CS_LOW();
    
    (void)SPI_WriteByteData(SPI0_Port, WRITE);
    
    for (i = 0; i < 2; i++) 
    {
        (void)SPI_WriteByteData(SPI0_Port, Address[i]);
    }
    
    (void)SPI_WriteByteData(SPI0_Port, W_Data);
    
    M95160_CS_HIGH();
    
    if (M95160_ReadStatusRegister(&ret_val) != 0)return -1;
    
    return 0;
}


int16_t M95160_ReadSequenceData(int16_t Memory_Addr, uint8_t* R_Data, uint16_t R_Length) 
{
    uint8_t Addr_H, Addr_L;
    uint8_t i;
    
    if ((Memory_Addr < MEMORY_STARTADDRESS) || (Memory_Addr > MEMORY_ENDADDRESS))return -1;
    
    if (R_Data == NULL)return -1;
    
    if (R_Length > TOTAL_SIZE)return -1;
    
    Addr_H = (uint8_t)(Memory_Addr >> 8);
    Addr_L = (uint8_t)(Memory_Addr & 0x00FFu);
    
    M95160_CS_LOW();
    
    (void)SPI_WriteByteData(SPI0_Port, READ);
    
    (void)SPI_WriteByteData(SPI0_Port, Addr_H);
    
    (void)SPI_WriteByteData(SPI0_Port, Addr_L);
    
    for (i = 0; i < R_Length; i++) 
    {
        (void)SPI_ReadByteData(SPI0_Port, 0xFFu, R_Data);
        
        R_Data++;      
    }
        
    M95160_CS_HIGH();
    
    return 0;        
}



#if 0
int16_t M95160_WriteSequenceData(int16_t Memory_Addr, uint8_t* W_Data, uint8_t W_Length)
{
    uint8_t Addr_H, Addr_L;
    uint8_t i,ret_val;

    if ((Memory_Addr < MEMORY_STARTADDRESS) || (Memory_Addr > MEMORY_ENDADDRESS))return -1;
    
    if (W_Data == NULL)return -1;
    
    if (W_Length > PAGEZ_SIZE)return -1;
    
    Addr_H = (uint8_t)(Memory_Addr >> 8);
    Addr_L = (uint8_t)(Memory_Addr & 0x00FFu);
    
    M95160_WriteEnable();
    
    M95160_CS_LOW();
    
    (void)SPI_WriteByteData(SPI0_Port, WRITE);
    
    (void)SPI_WriteByteData(SPI0_Port, Addr_H);
    
    (void)SPI_WriteByteData(SPI0_Port, Addr_L);
    
    for (i = 0; i < W_Length; i++) 
    {
        (void)SPI_WriteByteData(SPI0_Port, *W_Data++);      
    }
        
    M95160_CS_HIGH();
    
    if (M95160_ReadStatusRegister(&ret_val) != 0)return -1;
    
    return 0;    
}
#endif