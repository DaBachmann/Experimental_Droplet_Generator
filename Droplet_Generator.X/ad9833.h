/**
  AD9833 Header File

  File Name:
    ad9833.h

  Summary:
    This is the header file for the ad9833.c file

  Author:
    D.Bachmann
  
  Date:
    11.05.2020
  
  Revision:
    1.0
*/

#ifndef AD9833_H
#define	AD9833_H
/**
  Section: AD9833 APIs
*/

/**
  @Summary
    Initializes the AD9833.

  @Description
    This function initializes the AD9833 waveform generator.
    This function must be called before any other AD9833 function is called.

  @Preconditions
    None

  @Param
    None

  @Returns
    None
 
*/
void AD9833_Init(void);

/**
  @Summary
    Set the frequency of the AD9833.

  @Description
    This function sets the output frequency of the AD9833 Waveform Generator,
    by writing to the Registers via SPI
    This function must be called before any other AD9833 function is called.

  @Preconditions
    None

  @Param
    frequency - the value of the frequency in Hz

  @Returns
    None
 
*/
void AD9833_SetFrequency(long frequency);


#endif	/* AD9833_H */
/**
 End of File
*/

