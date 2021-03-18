/**
  External Interrupt Driver File

  File Name:
    ext_int.c

  Summary:
    This is the driver implementation file for the EXT_INT driver using PIC18F25k40
 
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
extern volatile unsigned int cycle_done;
extern volatile long cycle;
extern volatile long temp_cycle;
extern volatile unsigned int state;
extern volatile unsigned int temp_packages;
extern volatile unsigned int break_duration;
extern volatile unsigned int temp_break_duration;
extern volatile unsigned int packages;


/**
  Section: external Interrupt APIs
*/
void INT0_ISR(void)
{
    //clearing interrupt flag
    EXT_INT0_InterruptFlagClear();
    //disabling interrupt
    EXT_INT0_InterruptDisable();
    //Disable UART
    PIE3bits.RCIE = 0;
    PIE3bits.TXIE = 0;
    //Close SPI
    SPI1_Close();
    //change state to PULSE
    state = PULSE;
    //setting copies
    temp_packages = packages;
    temp_break_duration = break_duration;
    //reload frequency counter
    TMR0_Reload();
    //start frequency counter
    TMR0_StartTimer();  
}
    
void EXT_INT_Initialize(void)
{
    
    // Clear the interrupt flag
    EXT_INT0_InterruptFlagClear();   
    // Set the external interrupt edge detect
    EXT_INT0_risingEdgeSet();    
    // Set Default Interrupt Handler
    //EXT_INT0_InterruptEnable();      

}
/**
 End of File
*/

