/**
  SPI1 Driver API Header File

  File Name:
    spi1.h

  Summary:
    This is the header file for the SPI1 driver using a PIC18F25k40.

  Author:
    D.Bachmann
  
  Date:
    11.05.2020
  
  Revision:
    1.0
*/

#ifndef SPI1_H
#define SPI1_H

/**
  Section: Included Files
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
  Section: SPI interfaces 
*/
typedef enum { 
    SPI1_DEFAULT
} spi1_modes_t;

/**
  Section: TMR3 APIs
*/

/**
  @Summary
    Initializes the SPI Module

  @Description
    This routine initializes the SPI.
    This routine must be called before any other SPI routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    

  @Example
    <code>
    main()
    {
        // Initialize SPI module
        SPI1_Initialize();

        // Do something else...
    }
    </code>
*/
void SPI1_Initialize(void);

/**
  @Summary
    Starts the SPI Module

  @Description
    This routine starts the SPI Module and make it ready for data transmission.

  @Preconditions
   SPI1_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if transmitter is not busy before calling this function.

  @Param
    None

  @Returns
    None
*/
void SPI1_Start(void);

/**
  @Summary
    Stops the SPI Module

  @Description
    This routine stops the SPI Module. It will no longer recieve or transmit data

  @Preconditions
   SPI1_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if transmitter is not busy before calling this function.

  @Param
    None

  @Returns
    None
*/
void SPI1_Close(void);

/**
  @Summary
    write a byte via SPI

  @Description
    This routine writes a Byte via SPI Module and sets the FSYNC Pin for transmission
    with the AD9833.

  @Preconditions
   SPI1_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if transmitter is not busy before calling this function.

  @Param
    None

  @Returns
    None
*/
void SPI1_WriteByte(uint8_t byte);

/**
  @Summary
    write a 2 bytes via SPI

  @Description
    This routine writes a 2 bytes or 1 word via SPI Module and sets the FSYNC Pin for transmission
    with the AD9833.

  @Preconditions
   SPI1_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if transmitter is not busy before calling this function.

  @Param
    None

  @Returns
    None
*/
void SPI1_WriteWord(uint16_t word);
#endif //SPI1_H
/**
 End of File
*/
