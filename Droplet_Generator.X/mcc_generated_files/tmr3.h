/**
  TMR3 Driver API Header File

  File Name:
    tmr3.h

  Summary:
    This is the header file for the TMR3 driver using a PIC18F25k40.

  Author:
    D.Bachmann
  
  Date:
    11.05.2020
  
  Revision:
    1.0
*/

#ifndef TMR3_H
#define TMR3_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>

#define TMR3_INTERRUPT_TICKER_FACTOR    1

/**
  Section: TMR3 APIs
*/

/**
  @Summary
    Initializes the TMR3

  @Description
    This routine initializes the TMR3.
    This routine must be called before any other TMR3 routine is called.
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
        // Initialize TMR3 module
        TMR3_Initialize();

        // Do something else...
    }
    </code>
*/
void TMR3_Initialize(void);

/**
  @Summary
    This function starts the TMR3.

  @Description
    This function starts the TMR3 operation.
    This function must be called after the initialization of TMR3.

  @Preconditions
    Initialize  the TMR3 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR3 module

    // Start TMR3
    TMR3_StartTimer();

    // Do something else...
    </code>
*/
void TMR3_StartTimer(void);

/**
  @Summary
    This function stops the TMR3.

  @Description
    This function stops the TMR3 operation.
    This function must be called after the start of TMR3.

  @Preconditions
    Initialize  the TMR3 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR3 module

    // Start TMR3
    TMR3_StartTimer();

    // Do something else...

    // Stop TMR3;
    TMR3_StopTimer();
    </code>
*/
void TMR3_StopTimer(void);

/**
  @Summary
    Writes the TMR3 register.

  @Description
    This function writes the TMR3 register.
    This function must be called after the initialization of TMR3.

  @Preconditions
    Initialize  the TMR3 before calling this function.

  @Param
    timerVal - Value to write into TMR3 register.

  @Returns
    None

  @Example
    <code>
    #define PERIOD 0x80
    #define ZERO   0x00

    while(1)
    {
        // Read the TMR3 register
        if(ZERO == TMR3_ReadTimer())
        {
            // Do something else...

            // Write the TMR3 register
            TMR3_WriteTimer(PERIOD);
        }

        // Do something else...
    }
    </code>
*/
void TMR3_WriteTimer(uint16_t timerVal);

/**
  @Summary
    Timer Interrupt Service Routine

  @Description
    Timer Interrupt Service Routine is called by the Interrupt Manager.

  @Preconditions
    Initialize  the TMR3 module with interrupt before calling this ISR.

  @Param
    None

  @Returns
    None
*/
void TMR3_ISR(void);

#endif // TMR3_H
/**
 End of File
*/
