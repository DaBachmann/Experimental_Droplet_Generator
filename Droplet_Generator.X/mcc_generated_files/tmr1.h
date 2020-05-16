/**
  TMR1 Driver API Header File

  File Name:
    tmr1.h

  Summary:
    This is the header file for the TMR1 driver using a PIC18F25k40.

  Author:
    D.Bachmann
  
  Date:
    11.05.2020
  
  Revision:
    1.0
*/

#ifndef TMR1_H
#define TMR1_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>

/**
  Section: TMR1 APIs
*/

/**
  @Summary
    Initializes the TMR1

  @Description
    This routine initializes the TMR1.
    This routine must be called before any other TMR1 routine is called.
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
        // Initialize TMR1 module
        TMR1_Initialize();

        // Do something else...
    }
    </code>
*/
void TMR1_Initialize(void);

/**
  @Summary
    This function starts the TMR1.

  @Description
    This function starts the TMR1 operation.
    This function must be called after the initialization of TMR1.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR1 module

    // Start TMR1
    TMR1_StartTimer();

    // Do something else...
    </code>
*/
void TMR1_StartTimer(void);

/**
  @Summary
    This function stops the TMR1.

  @Description
    This function stops the TMR1 operation.
    This function must be called after the start of TMR1.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR1 module

    // Start TMR1
    TMR1_StartTimer();

    // Do something else...

    // Stop TMR1;
    TMR1_StopTimer();
    </code>
*/
void TMR1_StopTimer(void);

/**
  @Summary
    Writes the TMR1 register.

  @Description
    This function writes the TMR1 register.
    This function must be called after the initialization of TMR1.

  @Preconditions
    Initialize  the TMR1 before calling this function.

  @Param
    timerVal - Value to write into TMR1 register.

  @Returns
    None

  @Example
    <code>
    #define PERIOD 0x80
    #define ZERO   0x00

    while(1)
    {
        // Read the TMR1 register
        if(ZERO == TMR1_ReadTimer())
        {
            // Do something else...

            // Write the TMR1 register
            TMR1_WriteTimer(PERIOD);
        }

        // Do something else...
    }
    </code>
*/
void TMR1_WriteTimer(uint16_t timerVal);

/**
  @Summary
    Timer Interrupt Service Routine

  @Description
    Timer Interrupt Service Routine is called by the Interrupt Manager.

  @Preconditions
    Initialize  the TMR1 module with interrupt before calling this ISR.

  @Param
    None

  @Returns
    None
*/
void TMR1_ISR(void);

#endif // TMR1_H
/**
 End of File
*/
