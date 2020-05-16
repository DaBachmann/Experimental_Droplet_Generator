/**
  SPI1 Driver File

  File Name:
    spi1.c

  Summary:
    This is the driver implementation file for the SPI1 driver using PIC18F25k40
 
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
#include "mcc.h"


typedef struct { 
    uint8_t con1; 
    uint8_t stat;
    uint8_t add;
    uint8_t operation;
} spi1_configuration_t;

//con1 == SSPxCON1, stat == SSPxSTAT, add == SSPxADD, operation == Master/Slave
static const spi1_configuration_t spi1_configuration[] = {   
    { 0x2, 0x40, 0x1, 0 }
};

void SPI1_Initialize(void)
{
    //Setup PPS Pins RC1=CLK, RC2=MOSI
    SSP1CLKPPS = 17;
    SSP1DATPPS = 23;
    RC1PPS    = 13;
    RC2PPS    = 14;
    
    //SPI setup
    //CKE = Active to IDLE, SMP = High Speed 
    SSP1STAT = 0x40;
    //CKE = Idle:High Active:Low, SSPEN = disabled, SSPM = FOSC/64 
    SSP1CON1 = 0x12;
    SSP1ADD = 0x01;
    TRISCbits.TRISC1 = 0;
    SSP1CON1bits.SSPEN = 0;
}

void SPI1_Start(void)
{
    //check if SPI already running
    if(!SSP1CON1bits.SSPEN)
    {
        //Start SPI by setting SSPEN Bit in SSP1CON
        SSP1CON1bits.SSPEN = 1;        
    }    
}

void SPI1_Close(void)
{
    //Stop SPI by resetting SSPEN Bit in SSP1CON
    SSP1CON1bits.SSPEN = 0;
    
}

void SPI1_WriteByte(uint8_t byte)
{
    //put FSYNC Low to activate AD9833
    FSYNC = 0;
    //wait 10us
    __delay_us(10);
    //write data to SSP1BUF register
    SSP1BUF = byte;
    //wait 33us
    __delay_us(33);
    //set FSYNC high to end transmission
    FSYNC = 1; 
}

void SPI1_WriteWord(uint16_t word)
{
    //split data in two byte
    uint8_t bytel = word;
    uint8_t byteh = word >> 8;
    
    //put FSYNC Low to activate AD9833
    FSYNC = 0;
    //wait 10us
    __delay_us(10);
    //write first byte to SSP1BUF register
    SSP1BUF = byteh;
    //wait 33us
    __delay_us(33);
    //write second byte to SSP1BUF
    SSP1BUF = bytel;
    //wait 33us
    __delay_us(33);
    //set FSYNC high to end transmission
    FSYNC = 1;
}
/**
 End of File
*/