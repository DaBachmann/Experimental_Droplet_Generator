/**
  TMR3 Driver File

  File Name:
    tmr3.c

  Summary:
    This is the driver implementation file for the TMR3 driver using PIC18F25k40
    TMR3 is used as a 1ms Timer to generate the break duration between two Packages
 
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

/**
    Section: Global Variables defined in main.c
*/
extern volatile unsigned int temp_break_duration;;

/**
    Section: File Variables 
*/
volatile uint16_t timer3ReloadVal;


/**
  Section: TMR3 APIs
*/

void TMR3_Initialize(void)
{
    //Set the Timer to the options selected in the GUI

    //T3GE disabled; T3GTM disabled; T3GPOL low; T3GGO done; T3GSPM disabled; 
    T3GCON = 0x00;

    //GSS T3G_pin; 
    T3GATE = 0x00;

    //CS FOSC; 
    T3CLK = 0x02;

    //TMR3H 6; 
    TMR3H = 0x06;

    //TMR3L 0; 
    TMR3L = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR4bits.TMR3IF = 0;

    // Load the TMR value (1ms) to reload variable
    timer3ReloadVal=(uint16_t)((TMR3H << 8) | TMR3L);

    // Enabling TMR3 interrupt.
    PIE4bits.TMR3IE = 1;

    // CKPS 1:1; nT3SYNC synchronize; TMR3ON enabled; T3RD16 disabled; 
    T3CON = 0x01;
}

void TMR3_StartTimer(void)
{
    TMR3_WriteTimer(timer3ReloadVal);
    // Start the Timer by writing to TMRxON bit
    T3CONbits.TMR3ON = 1;
}

void TMR3_StopTimer(void)
{
    // Stop the Timer by writing to TMRxON bit
    T3CONbits.TMR3ON = 0;
}

void TMR3_WriteTimer(uint16_t timerVal)
{
    if (T3CONbits.nT3SYNC == 1)
    {
        // Stop the Timer by writing to TMRxON bit
        T3CONbits.TMR3ON = 0;

        // Write to the Timer3 register
        TMR3H = (timerVal >> 8);
        TMR3L = timerVal;

        // Start the Timer after writing to the register
        T3CONbits.TMR3ON =1;
    }
    else
    {
        // Write to the Timer3 register
        TMR3H = (timerVal >> 8);
        TMR3L = timerVal;
    }
}

void TMR3_ISR(void)
{
    //Stop Timer 3
    TMR3_StopTimer();
    // Clear the TMR3 interrupt flag
    PIR4bits.TMR3IF = 0;
    //Reload Timer 3
    TMR3_WriteTimer(timer3ReloadVal);
    //decrease break duration
    temp_break_duration--;
    //check if break duration is not zero
    if(temp_break_duration > 0){
        //start Timer 3
        TMR3_StartTimer();
    }else{
        //Start frequency counting
        TMR0_StartTimer();        
    }
}

/**
  End of File
*/
