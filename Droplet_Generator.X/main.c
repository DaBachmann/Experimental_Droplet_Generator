/**
  Main Source File

  File Name:
    main.c

  Summary:
    This is the main file for the Experimental Droplet Generator using a PIC18F25K40

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
#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */


/*
 *
 *  Defining global Variables 
 *
 */

//Data array for received UART data  
volatile char rx_data[20];
//marker for the end of the data array
volatile uint8_t rx_data_end = 0;

//Flag for checking if 2ms passed after UART data recieved
bool sec = false;

//frequency variable
long frequency = 3000000;

//cycle variable
volatile long cycle = 2;
//copy of the cycle variable for manipulation
volatile long temp_cycle = 2;

//variable for the break time
volatile unsigned int break_duration = 0;
//copy of the break time variable for manipulation
volatile unsigned int temp_break_duration = 0;

//variable for number of packages
volatile unsigned int packages = 1;
//copy of the number of packages variable for manipulation
volatile unsigned int temp_packages = 1;

//variable to save the current state (states are defined in mcc.h)
volatile unsigned int state = CONFIGURE;


void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    //Setting FSYNC High; Idle State
    FSYNC = 1;
    
    //Starting SPI Module
    SPI1_Start();
    __delay_ms(100);
    
    //Initialising the AD9833
    AD9833_Init();
    
    //Disable Gate Driver
    EN = 0;

    // Enable high priority global interrupts
    INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    INTERRUPT_GlobalInterruptLowEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    /*
        while loop 
     */
    while (1)
    {
        //switch case for the different states
        switch(state)
        {
            
            //Configure State
            case CONFIGURE:
                
                //check if 2ms since last recieved UART data
                if(sec == true)
                {
                //Parse UART Data
                Parse_Data();
            
                //Stopping Timer 1 and resetting Flag
                TMR1_StopTimer();
                sec = false;  
                }
                break;
                
            //Pulse State    
            case PULSE:
                               
                break;
                            
        }              
    }
}
/**
 End of File
*/