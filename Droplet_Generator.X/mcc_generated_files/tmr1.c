/**
  TMR1 Driver File

  File Name:
    tmr1.c

  Summary:
    This is the driver implementation file for the TMR1 driver using PIC18F25k40.
    TMR1 is used as a 2ms Timer to check if the UART module is no longer receiving data
 
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

#include <xc.h>
#include "tmr1.h"

/**
    Section: Global Variables defined in main.c
*/
extern bool sec;

/**
    Section: File Variables 
*/
volatile uint16_t timer1ReloadVal;


/**
  Section: TMR1 APIs
*/

void TMR1_Initialize(void)
{
    //Set the Timer to the options selected in the GUI

    //T1GE disabled; T1GTM disabled; T1GPOL low; T1GGO done; T1GSPM disabled; 
    T1GCON = 0x00;

    //GSS T1G_pin; 
    T1GATE = 0x00;

    //CS FOSC/4; 
    T1CLK = 0x01;

    //TMR1H 193; 
    TMR1H = 0xC1;

    //TMR1L 128; 
    TMR1L = 0x80;

    // Clearing IF flag before enabling the interrupt.
    PIR4bits.TMR1IF = 0;

    // Load the TMR value (2 ms) to reload variable
    timer1ReloadVal=(uint16_t)((TMR1H << 8) | TMR1L);

    // Enabling TMR1 interrupt.
    PIE4bits.TMR1IE = 1;


    // CKPS 1:2; nT1SYNC synchronize; TMR1ON enabled; T1RD16 disabled; 
    T1CON = 0x11;
}

void TMR1_StartTimer(void)
{
    // Start the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 1;
}

void TMR1_StopTimer(void)
{
    // Stop the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 0;
}

void TMR1_WriteTimer(uint16_t timerVal)
{
    if (T1CONbits.nT1SYNC == 1)
    {
        // Stop the Timer by writing to TMRxON bit
        T1CONbits.TMR1ON = 0;

        // Write to the Timer1 register
        TMR1H = (timerVal >> 8);
        TMR1L = timerVal;

        // Start the Timer after writing to the register
        T1CONbits.TMR1ON =1;
    }
    else
    {
        // Write to the Timer1 register
        TMR1H = (timerVal >> 8);
        TMR1L = timerVal;
    }
}

void TMR1_ISR(void)
{

    // Clear the TMR1 interrupt flag
    PIR4bits.TMR1IF = 0;
    TMR1_WriteTimer(timer1ReloadVal);

    //set 2ms delay for UART true
    sec = true;
}


/**
  End of File
*/
