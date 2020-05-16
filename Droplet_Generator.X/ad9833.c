/**
  AD9833 C File

  File Name:
    ad9833.c

  Summary:
    This file implemnets functions to generate Wavefomrs using the AD9833 and 
    the SPI1 Module 

  Author:
    D.Bachmann
  
  Date:
    11.05.2020
  
  Revision:
    1.0
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/mcc.h"

void AD9833_Init(void)
{    
    //Set the Reset Bit in the Control Register
    SPI1_WriteWord(0x0100);
    __delay_ms(50);
    
    //Set the Frequency to 3MHz
    AD9833_SetFrequency(3000000);      
    
}

/**
  Section: AD9833 APIs
*/
void AD9833_SetFrequency(long frequency)
{    
    //Calculation from Frequency to Register Value
    long freq = (frequency * pow(2, 28)) / 25000000;
    
    //setting the first 14 bit as MSB
    int MSB = (int)((freq & 0xFFFC000) >> 14);    
    //setting the last 14 bit as LSB
    int LSB = (int)(freq & 0x3FFF);

    //masking the Address over MSB and LSB
    LSB |= 0x4000;
    MSB |= 0x4000;
    
    //setting B28 bit of the control register to load MSB and LSB seperatly
    SPI1_WriteWord(0x2100);
    
    //Load LSB to the frequency register
    SPI1_WriteWord(LSB);
    //Load MSB to the frequency register
    SPI1_WriteWord(MSB);
    //set Phase to 0° in Phase Register
    SPI1_WriteWord(0xC000);
    
    //set output waveform to Square waveform
    SPI1_WriteWord(0x2028);
    
}
/**
 End of File
*/
