/**
  Parsing C File

  File Name:
    parse.c

  Summary:
    This file implemnets a parsing function of UART Data for the experimental 
    droplet generator

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

/**
    Section: Global Variables defined in main.c
*/
extern volatile char rx_data[20];
extern volatile uint8_t rx_data_end;
extern long frequency;
extern volatile long cycle;
extern volatile long temp_cycle;
extern volatile unsigned int temp_packages;
extern volatile unsigned int break_duration;
extern volatile unsigned int temp_break_duration;
extern volatile unsigned int packages;

/**
    Section: File Variables 
*/
//array to save UART output
volatile char output[50];
//copy of the frequency to manipulate
long temp_frequency;

/**
  Section: parsing APIs
*/
void Parse_Data(){
    
    //writing the input back, to show it in the serial monitor
    EUSART_Write_String(rx_data);
    
    //check if input is in viable form (no other character after command character)
    for(int i = 1; rx_data[i] != '\0'; i++)
    {
        if((rx_data[i] < '0' && rx_data[i] > ' ') || rx_data[i] > '9' || rx_data[i] < ' ')
        {            
            //Error message for invalid character
            sprintf(output, "Unexpected Character %c on Position %i", rx_data[i], i+1);
            EUSART_Write_String(output);
            output[0] = '\0';
            rx_data_end = 0; 
            return;
        }
    }
    
    //data parsing for "f" command    
    if(rx_data[0] == 'f' || rx_data[0] == 'F')
    {
        //delete "f" from string beginning
        rx_data[0] = ' ';
        
        //convert string in long
        temp_frequency = atol(rx_data);
        
        //check if frequency is lower than 1MHz
        if(temp_frequency < 1000000)
        {
            //Error message if frequency is too low
            sprintf(output, "Error! Minimum Frequency 1000000 Hz");
            EUSART_Write_String(output);
            output[0] = '\0';
            rx_data_end = 0;
            
        //check if frequency is higher than 5MHz
        }else if(temp_frequency > 5000000)
        {   
            //Error Message if frequency is too high
            sprintf(output, "Error! Maximum Frequency 5000000 Hz");
            EUSART_Write_String(output);
            output[0] = '\0';
            rx_data_end = 0;
        }else
        {
            //set the frequency to the input frequency
            frequency = temp_frequency;
            //set the frequency of the AD9833
            AD9833_SetFrequency(frequency);
            
            //confirm message
            sprintf(output, "Frequency changed to %ld Hz", frequency);
            EUSART_Write_String(output);
            output[0] = '\0';
            rx_data_end = 0;
        }
    
    //data parsing for "c" command
    }else if(rx_data[0] == 'c' || rx_data[0] == 'C')
    {
        //delete "c" from string beginning
        rx_data[0] = ' ';
        
        //convert string in long
        temp_cycle = atol(rx_data);
        
        //check if cycle is lower than 2 cycles
        if(temp_cycle < 2)
        {
            //Error message if cycle is too low
            sprintf(output, "Error! Minimum Cycle count 2");
            EUSART_Write_String(output);
            output[0] = '\0';
            rx_data_end = 0;
            
        //check if cycle is higher than 32000 cycles
        }else if(temp_cycle > 32000)
        {
            //Error message if cycle is too high
            sprintf(output, "Error! Maximum Cycle count 32000");
            EUSART_Write_String(output);
            output[0] = '\0';
            rx_data_end = 0;
        }else
        {
            //set cycle to input cycles           
            cycle = temp_cycle;
            
            //confirm message
            sprintf(output, "Cycle changed to %ld Cycles", cycle);
            EUSART_Write_String(output);
            output[0] = '\0';
            rx_data_end = 0;
        }
        
    //data parsing for "b" command
    }else if(rx_data[0] == 'B' || rx_data[0] == 'b')
    {
        //delete "b" from string beginning
        rx_data[0] = ' ';
        
        //convert string in int
        temp_break_duration = atoi(rx_data);
        
        //check if break duration is higher than 256ms
        if(temp_break_duration > 256)
        {
            //Error message if break duration to long
            sprintf(output, "Error! Maximum Break Duration 256 ms");
            EUSART_Write_String(output);
            output[0] = '\0';
            rx_data_end = 0;
        }else
        {
            //set break duration to input break duration 
            break_duration = temp_break_duration;
            
            //confrim message
            sprintf(output, "Break Duration changed to %u ms", break_duration);
            EUSART_Write_String(output);
            output[0] = '\0';
            rx_data_end = 0;
        }
        
    //data parsing for "n" command   
    }else if(rx_data[0] == 'N' || rx_data[0] == 'n')
    {
        //delete "n" from string beginning
        rx_data[0] = ' ';
        
        //convert string in int
        temp_packages = atoi(rx_data);
        
        //check if packages is lower than 1
        if(temp_packages < 1)
        {
            //Error message if packages too low
            sprintf(output, "Error! Minimum Packages count 1");
            EUSART_Write_String(output);
            output[0] = '\0';
            rx_data_end = 0;
            
        //check if packages is higher than 256
        }else if(temp_packages > 256)
        {
            //Error message if packages is too high
            sprintf(output, "Error! Maximum Packages count 256");
            EUSART_Write_String(output);
            output[0] = '\0';
            rx_data_end = 0;            
        }else
        {
            //set peckages to input packages
            packages = temp_packages;
            
            //confirm message
            sprintf(output, "Number of Packages changed to %u Packages", packages);
            EUSART_Write_String(output);
            output[0] = '\0';
            rx_data_end = 0;
        }
        
    //data parsing for "i" command 
    }else if(rx_data[0] == 'I' || rx_data[0] == 'i')
    {
        //Output current frequency
        sprintf(output, "Frequency = %ld Hz", frequency);
        EUSART_Write_String(output);
        
        //Output current cycles
        sprintf(output, "Cycles = %ld", cycle);
        EUSART_Write_String(output);
        
        //Output current break duration
        sprintf(output, "Break Duration = %u ms", break_duration);
        EUSART_Write_String(output);
        
        //Output current number of packages
        sprintf(output, "Number of Packages = %u", packages);
        EUSART_Write_String(output);
        output[0] = '\0';
        rx_data_end = 0;
        
    //unknown command    
    }else
    {
        //Error message for unknown command
         sprintf(output, "Unknown Command %c", rx_data[0]);
         EUSART_Write_String(output);
         output[0] = '\0';
         rx_data_end = 0; 
        } 
    
}
/**
 End of File
*/