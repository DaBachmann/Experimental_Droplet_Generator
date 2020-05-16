/**
  TMR0 Driver File

  File Name:
    tmr0.c

  Summary:
    This is the driver implementation file for the TMR0 driver using PIC18F25k40
    TMR0 is used as a counter to count Pulses of a Square Wave 
 
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
extern volatile unsigned int state;
extern volatile long temp_cycle;
extern volatile long cycle;
extern volatile unsigned int temp_packages;
extern volatile unsigned int break_duration;

/**
    Section: File Variables 
*/
volatile uint16_t timer0ReloadVal16bit;

/**
  Section: TMR0 APIs
*/
void TMR0_Initialize(void)
{

    // T0CS T0CKI_PIN; T0CKPS 1:1; T0ASYNC not_synchronised; 
    T0CON1 = 0x10;

    // TMR0H 254; 
    TMR0H = 0xFE;

    // TMR0L 0; 
    TMR0L = 0x00;

    // Load TMR0 value to the 16-bit reload variable
    timer0ReloadVal16bit = (TMR0H << 8) | TMR0L;

    // Clear Interrupt flag before enabling the interrupt
    PIR0bits.TMR0IF = 0;

    // Enabling TMR0 interrupt.
    PIE0bits.TMR0IE = 1;


    // T0OUTPS 1:1; T0EN enabled; T016BIT 16-bit; 
    T0CON0 = 0x90;
}

void TMR0_StartTimer(void)
{
    //start Timer by falling edge
    while(PORTAbits.RA7 == 0);
    while(PORTAbits.RA7 == 1);
    
    // Start the Timer by writing to TMR0ON bit
    T0CON0bits.T0EN = 1;
    //enable gate driver
    EN = 1;
}

void TMR0_StopTimer(void)
{
    // Stop the Timer by writing to TMR0ON bit    
    T0CON0bits.T0EN = 0;
    
}

void TMR0_WriteTimer(uint16_t timerVal)
{
    // Write to the Timer0 register
    TMR0H = timerVal >> 8;
    TMR0L = (uint8_t) timerVal;
}

void TMR0_Reload(void)
{
    // Write to the Timer0 register the cycle value + 1 to compensate the turn off delay
    temp_cycle = cycle - 1;
    TMR0_WriteTimer((0xFFFF - temp_cycle)+1);    
}

/**
  End of File
*/