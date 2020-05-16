/**
  TMR0 Driver API Header File

  File Name:
    tmr0.h

  Summary:
    This is the header file for the TMR0 driver using a PIC18F25k40.

  Author:
    D.Bachmann
  
  Date:
    11.05.2020
  
  Revision:
    1.0
*/

#ifndef TMR0_H
#define TMR0_H

/**
  Section: Included Files
*/

#include <stdint.h>
#include <stdbool.h>

/**
  Section: TMR0 APIs
*/

/**
  @Summary
    Initializes the TMR0.

  @Description
    This function initializes the TMR0 Registers.
    This function must be called before any other TMR0 function is called.

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
        // Initialize TMR0 module
        TMR0_Initialize();

        // Do something else...
    }
    </code>
*/
void TMR0_Initialize(void);

/**
  @Summary
    This function starts the TMR0.

  @Description
    This function starts the TMR0 operation.
    This function must be called after the initialization of TMR0.

  @Preconditions
    Initialize  the TMR0 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR0 module

    // Start TMR0
    TMR0_StartTimer();

    // Do something else...
    </code>
*/
void TMR0_StartTimer(void);

/**
  @Summary
    This function stops the TMR0.

  @Description
    This function stops the TMR0 operation.
    This function must be called after the start of TMR0.

  @Preconditions
    Initialize  the TMR0 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    // Initialize TMR0 module

    // Start TMR0
    TMR0_StartTimer();

    // Do something else...

    // Stop TMR0;
    TMR0_StopTimer();
    </code>
*/
void TMR0_StopTimer(void);

/**
  @Summary
    Writes the 16 bits value to TMR0 register.

  @Description
    This function writes the 16 bits value to TMR0 register.
    This function must be called after the initialization of TMR0.

  @Preconditions
    Initialize  the TMR0 before calling this function.

  @Param
    timerVal - Value to write into TMR0 register.

  @Returns
    None

  @Example
    <code>
    #define PERIOD 0x8000
    #define ZERO   0x0000

    while(1)
    {
        //Read the TMR0 register
        if(ZERO == TMR0_ReadTimer())
        {
            // Do something else...

            // Write the TMR0 register
            TMR0_WriteTimer(PERIOD);
        }

        // Do something else...
    }
    </code>
*/
void TMR0_WriteTimer(uint16_t timerVal);

/**
  @Summary
    Reload the 16 bits value to TMR0 register.

  @Description
    This function reloads the 16 bit value to TMR0 register.
    This function must be called to write initial value into TMR0 register.

  @Preconditions
    Initialize  the TMR0 before calling this function.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    while(1)
    {
        if(TMR0IF)
        {
            // Do something else...

            // clear the TMR0 interrupt flag
            TMR0IF = 0;

            // Reload the initial value of TMR0
            TMR0_Reload();
        }
    }
    </code>
*/
void TMR0_Reload(void);

#endif // TMR0_H
/**
 End of File
*/