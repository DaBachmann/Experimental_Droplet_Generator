/**
  Interrupt Manager File

  File Name:
    interrupt_manager.c

  Summary:
    This is the Interrupt Manager file using PIC18F25k40
 
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
#include "interrupt_manager.h"
#include "mcc.h"

/**
    Section: Global Variables defined in main.c
*/
extern volatile unsigned int state;
extern volatile unsigned int temp_packages;
extern volatile unsigned int break_duration;
extern volatile unsigned int temp_break_duration;

/**
  Section: external Interrupt APIs
*/
void  INTERRUPT_Initialize (void)
{
    // Enable Interrupt Priority Vectors
    INTCONbits.IPEN = 1;

    // Assign peripheral interrupt priority vectors

    // TMRI - high priority
    IPR0bits.TMR0IP = 1;

    // INT0I - low priority
    IPR0bits.INT0IP = 0;

    // TMRI - low priority
    IPR4bits.TMR1IP = 0;    

    // TXI - low priority
    IPR3bits.TXIP = 0;    

    // RCI - low priority
    IPR3bits.RCIP = 0;    

    // TMRI - low priority
    IPR4bits.TMR3IP = 0;    

}

void __interrupt() INTERRUPT_InterruptManagerHigh (void)
{
    /*
        instead of calling the Interrupt Routine, the Routine is impelemented
        directly in the interrupt manager to save time 
     */
    //disable Gate Driver
    EN = 0;
    //Stop frequency counting
    TMR0_StopTimer();
    //decrease packages
    temp_packages--;    
    // clear the TMR0 interrupt flag
    PIR0bits.TMR0IF = 0;
    //reload frequency counting
    TMR0_Reload();
    
    //check if all packages are sent
    if(temp_packages < 1)
    {
        //enable external interrupt
        EXT_INT0_InterruptEnable();
        //enable UART
        PIE3bits.RCIE = 1;
        PIE3bits.TXIE = 1;
        //Start SPI module
        SPI1_Start();
        //change state to CONFIGURE
        state = CONFIGURE;
    }else
    {        
        //copy break duration
        temp_break_duration = break_duration;
        //check if break duration is set
        if(temp_break_duration > 0)
        {
            //Start break duration
            TMR3_StartTimer();
        }else{
            //start frequency counting
            TMR0_StartTimer();
        }
        
    }
  
}

void __interrupt(low_priority) INTERRUPT_InterruptManagerLow (void)
{
    // interrupt handler
    if(PIE4bits.TMR3IE == 1 && PIR4bits.TMR3IF == 1)
    {
        //Timer 3 interrupt handler
        TMR3_ISR();
    }  
    else if(PIE4bits.TMR1IE == 1 && PIR4bits.TMR1IF == 1)
    {
        //Timer 1 interrupt handler
        TMR1_ISR();
    }
    else if(PIE3bits.TXIE == 1 && PIR3bits.TXIF == 1)
    {
        //UART transmit interrupt handler
        EUSART_TxDefaultInterruptHandler();
    }
    else if(PIE3bits.RCIE == 1 && PIR3bits.RCIF == 1)
    {
        //UART receive interrupt handler
        EUSART_RxDefaultInterruptHandler();
    }
    else if(PIE0bits.INT0IE == 1 && PIR0bits.INT0IF == 1)
    {
        //external interrupt handler
        INT0_ISR();
    }else 
    {
        
    }
}
/**
 End of File
*/
