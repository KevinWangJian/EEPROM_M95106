/**
  ******************************************************************************
  * @Copyright (C), 1997-2015, Hangzhou Gold Electronic Equipment Co., Ltd.
  * @file name: SPI_Driver.c
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

/* Includes ------------------------------------------------------------------*/
#include "SPI_Driver.h"




/**
  * @brief   Initialize SPI ports.
  * @param   SPIx, The specified SPI port.
  *          Pins, SPI signal pins remap to the corresponding ports.
  *          *p_Config, Data buffer which store SPI configure parameters.
  *          sp_mode, SPI transfer speed. 
  * @Attention  Users should call this function first before others.
  * @returns 0 means success, -1 means failure.
  */
int16_t SPI_Init(SPIx_PortsType SPIx, SPIx_PinsRemap Pins, SPIx_ConfigType *p_Config, SPIxSpeed_Typedef sp_mode) 
{
    int ret_val = -1;
    
    if ((SPIx < SPI0_Port) || (SPIx > SPI2_Port))return (ret_val);
    
    if ((Pins < SPI0_PortMPins) || (Pins > SPI2_PortPPins))return (ret_val);
    
    if (p_Config == NULL)return (ret_val);
    
    if ((sp_mode < High_Speed) || (sp_mode > Low_Speed))return (ret_val);
    
    if (SPIx == SPI0_Port) 
    {
        if (Pins == SPI0_PortMPins) 
        {
            /* Configure Module Routing Register(MODRR) and remap SPI0 signals to ports M */
            MODRR_MODRR4 = 1;
            /* Configure PM2,PM3,PM4,PM5 pins as MISO,SS,MOSI,SCK signal pins of SPI0. */
            DDRM_DDRM2 = 0;
            DDRM_DDRM3 = 1;
            DDRM_DDRM4 = 1;
            DDRM_DDRM5 = 1;
        } 
        else 
        {
            /* Configure Module Routing Register(MODRR) and remap SPI0 signals to ports S */
            MODRR_MODRR4 = 0;
            /* Configure PS4,PS5,PS6,PS7 pins as MISO,SS,MOSI,SCK signal pins of SPI0. */
            DDRS_DDRS4 = 0;                                                
            DDRS_DDRS5 = 1;
            DDRS_DDRS6 = 1;
            DDRS_DDRS7 = 1;
        }
        
        SPI0CR1_SPIE = p_Config->SPI_ALLInterrupt_Enable;
        
        SPI0CR1_SPE = p_Config->SPI_Enable;
        
        SPI0CR1_SPTIE = p_Config->SPI_TransmitInterrupt_Enable;
        
        SPI0CR1_MSTR = p_Config->SPI_MasterOrSlaveMode;
        
        SPI0CR1_CPOL = p_Config->SPI_CPOL;
        
        SPI0CR1_CPHA = p_Config->SPI_CPHA;
        
        SPI0CR1_SSOE = p_Config->SPI_HardwarePCSSelect;
        SPI0CR2_MODFEN = p_Config->SPI_HardwarePCSSelect;
        
        SPI0CR1_LSBFE = p_Config->SPI_LSBFirst;
        
        SPI0CR2_XFRW = p_Config->SPI_TransferLength;
        
        /* Configure the SPI transfer baud rate.
           BaudRateDivisor = (SPPR + 1)*2^(SPR + 1)
           Baud Rate = BusClock / BaudRateDivisor
         */
        if (sp_mode == Low_Speed)       // Low speed mode
        {
            SPI0BR = 0x44;              // 200Kbps(Clock source is Bus clock and the frequency is 32MHz)
        }
        else if (sp_mode == High_Speed) // High speed mode
        {
            SPI0BR = 0x04;              // 1Mbps(Clock source is Bus clock and the frequency is 32MHz)
        }
        
        ret_val = 0;
    } 
    else if (SPIx == SPI1_Port)
    {
        if (Pins == SPI1_PortHPins) 
        {
            /* Configure Module Routing Register(MODRR) and remap SPI1 signals to ports H */
            MODRR_MODRR5 = 1;
            
            /* Configure PH0,PH1,PH2,PH3 pins as MISO,SS,MOSI,SCK signal pins of SPI1. */
            DDRH_DDRH3 = 1;                                                
            DDRH_DDRH2 = 1;
            DDRH_DDRH1 = 1;
            DDRH_DDRH0 = 0;
        } 
        else 
        {
            /* Configure Module Routing Register(MODRR) and remap SPI1 signals to ports P */
            MODRR_MODRR5 = 0;
            
            /* Configure PP0,PP1,PP2,PP3 pins as MISO,SS,MOSI,SCK signal pins of SPI1. */ 
            DDRP_DDRP3 = 1;
            DDRP_DDRP2 = 1;
            DDRP_DDRP1 = 1;
            DDRP_DDRP0 = 0;
        }
        
        SPI1CR1_SPIE = p_Config->SPI_ALLInterrupt_Enable;
        
        SPI1CR1_SPE = p_Config->SPI_Enable;
        
        SPI1CR1_SPTIE = p_Config->SPI_TransmitInterrupt_Enable;
        
        SPI1CR1_MSTR = p_Config->SPI_MasterOrSlaveMode;
        
        SPI1CR1_CPOL = p_Config->SPI_CPOL;
        
        SPI1CR1_CPHA = p_Config->SPI_CPHA;
        
        SPI1CR1_SSOE = p_Config->SPI_HardwarePCSSelect;
        SPI1CR2_MODFEN = p_Config->SPI_HardwarePCSSelect;
        
        SPI1CR1_LSBFE = p_Config->SPI_LSBFirst;
        
        SPI1CR2_XFRW = p_Config->SPI_TransferLength; 
        
        /* Configure the SPI transfer baud rate.
           BaudRateDivisor = (SPPR + 1)*2^(SPR + 1)
           Baud Rate = BusClock / BaudRateDivisor
        */
        if (sp_mode == Low_Speed)       // Low speed mode
        {
            SPI1BR = 0x44;              // 200Kbps(Clock source is Bus clock and the frequency is 32MHz)
        }
        else if (sp_mode == High_Speed) // High speed mode
        {
            SPI1BR = 0x04;              // 1Mbps(Clock source is Bus clock and the frequency is 32MHz)
        }
        
        ret_val = 0;
    } 
    else
    {
        if (Pins == SPI2_PortHPins) 
        {
            MODRR_MODRR6 = 1;
            
            DDRH_DDRH7 = 1;
            DDRH_DDRH6 = 1;
            DDRH_DDRH5 = 1;
            DDRH_DDRH4 = 0;
        } 
        else 
        {
            MODRR_MODRR6 = 0;
            
            DDRP_DDRP4 = 0;                                               
            DDRP_DDRP5 = 1;
            DDRP_DDRP6 = 1;
            DDRP_DDRP7 = 1;
        }
        
        SPI2CR1_SPIE = p_Config->SPI_ALLInterrupt_Enable;
        
        SPI2CR1_SPE = p_Config->SPI_Enable;
        
        SPI2CR1_SPTIE = p_Config->SPI_TransmitInterrupt_Enable;
        
        SPI2CR1_MSTR = p_Config->SPI_MasterOrSlaveMode;
        
        SPI2CR1_CPOL = p_Config->SPI_CPOL;
        
        SPI2CR1_CPHA = p_Config->SPI_CPHA;
        
        SPI2CR1_SSOE = p_Config->SPI_HardwarePCSSelect;
        SPI2CR2_MODFEN = p_Config->SPI_HardwarePCSSelect;
        
        SPI2CR1_LSBFE = p_Config->SPI_LSBFirst;
        
        SPI2CR2_XFRW = p_Config->SPI_TransferLength;
        
        /* Configure the SPI transfer baud rate.
           BaudRateDivisor = (SPPR + 1)*2^(SPR + 1)
           Baud Rate = BusClock / BaudRateDivisor
        */
        if (sp_mode == Low_Speed)       // Low speed mode
        {
            SPI2BR = 0x44;              // 200Kbps(Clock source is Bus clock and the frequency is 32MHz)
        }
        else if (sp_mode == High_Speed) // High speed mode
        {
            SPI2BR = 0x04;              // 1Mbps(Clock source is Bus clock and the frequency is 32MHz)
        }
        
        ret_val = 0;
    }
    
    return (ret_val);
}



/**
  * @brief   Write one byte data by SPI port.
  * @param   SPIx, The specified SPI port.
  *          Tx_data, The data which will be written. 
  * @returns 0 means success, -1 means failure.
  */
int16_t SPI_WriteByteData(SPIx_PortsType SPIx, uint8_t Tx_data) 
{
    uint8_t dummy_byte;
    uint32_t Timeout_Count = 0;
    
    if ((SPIx < SPI0_Port) || (SPIx > SPI2_Port))return -1;
    
    if (SPIx == SPI0_Port) 
    {
        while (!SPI0SR_SPTEF) 
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        Timeout_Count = 0;
        
        (void)SPI0SR;
        
        SPI0DRL = Tx_data;
        
        while (!SPI0SR_SPIF) 
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        dummy_byte = SPI0DRL;
    } 
    else if (SPIx == SPI1_Port) 
    {
        while (!SPI1SR_SPTEF) 
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        Timeout_Count = 0;
        
        (void)SPI1SR;
        
        SPI1DRL = Tx_data;
        
        while (!SPI1SR_SPIF) 
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        dummy_byte = SPI1DRL;
    } 
    else if (SPIx == SPI2_Port) 
    {
        while (!SPI2SR_SPTEF) 
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        Timeout_Count = 0;
        
        (void)SPI2SR;
        
        SPI2DRL = Tx_data;
        
        while (!SPI2SR_SPIF) 
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        dummy_byte = SPI2DRL;
    }
    
    return 0;
}



/**
  * @brief   Read one byte data by SPI port.
  * @param   SPIx, The specified SPI port.
  *          dummy_data, The data which will be sent.Because it's a dummy written data,
  *          user can send any data to generate 8 SCK signals.
  *          *Rx_data, Data buffer which store the read data.
  * @returns 0 means success, -1 means failure.
  */
int16_t SPI_ReadByteData(SPIx_PortsType SPIx, uint8_t dummy_data, uint8_t* Rx_data) 
{
    uint32_t Timeout_Count = 0;
    
    if ((SPIx < SPI0_Port) || (SPIx > SPI2_Port))return -1;
    
    if (Rx_data == NULL)return -1;
    
    if (SPIx == SPI0_Port) 
    {
        while (!SPI0SR_SPTEF)
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        Timeout_Count = 0;
        
        (void)SPI0SR;
        
        SPI0DRL = dummy_data;
        
        while (!SPI0SR_SPIF) 
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        /* Load the received data to received buffer */
        *Rx_data = SPI0DRL;
    } 
    else if (SPIx == SPI1_Port) 
    {
        while (!SPI1SR_SPTEF)
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        Timeout_Count = 0;
        
        (void)SPI1SR;
        
        SPI1DRL = dummy_data;
        
        while (!SPI1SR_SPIF) 
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        /* Load the received data to received buffer */
        *Rx_data = SPI1DRL;
    } 
    else if (SPIx == SPI2_Port) 
    {
        while (!SPI2SR_SPTEF)
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        Timeout_Count = 0;
        
        (void)SPI2SR;
        
        SPI2DRL = dummy_data;
        
        while (!SPI2SR_SPIF) 
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        /* Load the received data to received buffer */
        *Rx_data = SPI2DRL;
    }    
    
    return 0;
}



/**
  * @brief   Write and read one byte data by SPI port.
  * @param   SPIx, The specified SPI port.
  *          Tx_data, The data which will be written.
  *          *Rx_data, Data buffer which store the read data.
  * @returns 0 means success, -1 means failure.
  */
int16_t SPI_WriteReadByteData(SPIx_PortsType SPIx, uint8_t Tx_data, uint8_t* Rx_data)
{    
    uint32_t Timeout_Count = 0;
    
    if ((SPIx < SPI0_Port) || (SPIx > SPI2_Port))return -1;
    
    if (Rx_data == NULL)return -1;
    
    if (SPIx == SPI0_Port)
    {
        /* Before a transmission,check whether SPI data register is empty. */
        while (!SPI0SR_SPTEF)
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        SPI0DRL = Tx_data;
        
        Timeout_Count = 0;
        
        /* Check whether received data in SPI data register. */
        while (!SPI0SR_SPIF)
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        /* Load the received data to received buffer */
        *Rx_data = SPI0DRL;
    }
    else if (SPIx == SPI1_Port)
    {
        /* Before a transmission,check whether SPI data register is empty. */
        while (!SPI1SR_SPTEF)
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        SPI1DRL = Tx_data;
        
        Timeout_Count = 0;
        
        /* Check whether received data in SPI data register. */
        while (!SPI1SR_SPIF)
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        /* Load the received data to received buffer */
        *Rx_data = SPI1DRL;
    } 
    else 
    {
        /* Before a transmission,check whether SPI data register is empty. */
        while (!SPI2SR_SPTEF)
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        SPI2DRL = Tx_data;
        
        Timeout_Count = 0;
        
        /* Check whether received data in SPI data register. */
        while (!SPI2SR_SPIF)
        {
            if (++Timeout_Count == 0xFFFFu)
            {
                /* Time out,return error */
                return -1;
            }
        }
        
        /* Load the received data to received buffer */
        *Rx_data = SPI2DRL;
    }
    
    return (0);
}

/*****************************END OF FILE**************************************/
