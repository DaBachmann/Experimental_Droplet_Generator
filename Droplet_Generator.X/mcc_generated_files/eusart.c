/**
  EUSART Driver File

  File Name:
    eusart.c

  Summary:
    This is the driver implementation file for the EUSART driver using PIC18F25k40
 
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
    Section: Macro Declarations
*/
#define EUSART_TX_BUFFER_SIZE 8
#define EUSART_RX_BUFFER_SIZE 8

/**
    Section: Global Variables defined in main.c
*/
extern volatile char rx_data[10];
extern volatile uint8_t rx_data_end;
extern bool sec;
/**
    Section: File Variables 
*/
//marker for Transmit Data Head
volatile uint8_t eusartTxHead = 0;
//marker for Transmit Data Tail
volatile uint8_t eusartTxTail = 0;
//Transmit Data Buffer
volatile uint8_t eusartTxBuffer[EUSART_TX_BUFFER_SIZE];
//marker for Remaining TX Data to send
volatile uint8_t eusartTxBufferRemaining;

//marker for Recieve Data Head
volatile uint8_t eusartRxHead = 0;
//marker for Recieve Data Tail
volatile uint8_t eusartRxTail = 0;
//Recieve Status Buffer
volatile eusart_status_t eusartRxStatusBuffer[EUSART_RX_BUFFER_SIZE];
//marker for remaining recieved data
volatile uint8_t eusartRxCount;
//UART status variable
volatile eusart_status_t eusartRxLastError;

/**
  Section: EUSART APIs
*/
void (*EUSART_TxDefaultInterruptHandler)(void);
void (*EUSART_RxDefaultInterruptHandler)(void);

void (*EUSART_FramingErrorHandler)(void);
void (*EUSART_OverrunErrorHandler)(void);
void (*EUSART_ErrorHandler)(void);

void EUSART_DefaultFramingErrorHandler(void);
void EUSART_DefaultOverrunErrorHandler(void);
void EUSART_DefaultErrorHandler(void);

void EUSART_Initialize(void)
{
    // disable interrupts before changing states
    PIE3bits.RCIE = 0;
    EUSART_SetRxInterruptHandler(EUSART_Receive_ISR);
    PIE3bits.TXIE = 0;
    EUSART_SetTxInterruptHandler(EUSART_Transmit_ISR);
    

    // ABDOVF no_overflow; SCKP Non-Inverted; BRG16 16bit_generator; WUE disabled; ABDEN disabled; 
    BAUD1CON = 0x08;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RC1STA = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave; 
    TX1STA = 0x24;

    // SP1BRGL 130; 
    SP1BRGL = 0x82;

    // SP1BRGH 6; 
    SP1BRGH = 0x06;

    //setting Error Handlers
    EUSART_SetFramingErrorHandler(EUSART_DefaultFramingErrorHandler);
    EUSART_SetOverrunErrorHandler(EUSART_DefaultOverrunErrorHandler);
    EUSART_SetErrorHandler(EUSART_DefaultErrorHandler);

    //resetting error status
    eusartRxLastError.status = 0;

    // initializing the driver state
    eusartTxHead = 0;
    eusartTxTail = 0;
    eusartTxBufferRemaining = sizeof(eusartTxBuffer);

    eusartRxHead = 0;
    eusartRxTail = 0;
    eusartRxCount = 0;

    // enable receive interrupt
    PIE3bits.RCIE = 1;
}

void EUSART_Write(uint8_t txData)
{
    //check if currently Transmitting
    while(0 == eusartTxBufferRemaining)
    {
    }

    //load Data into Transmit Register if empty
    if(0 == PIE3bits.TXIE)
    {
        TX1REG = txData;
    }
    //if Data is in the Buffer, load Data at the end of the Buffer
    else
    {
        PIE3bits.TXIE = 0;
        eusartTxBuffer[eusartTxHead++] = txData;
        if(sizeof(eusartTxBuffer) <= eusartTxHead)
        {
            eusartTxHead = 0;
        }
        eusartTxBufferRemaining--;
    }
    PIE3bits.TXIE = 1;
}

void EUSART_Write_String(char data[])
{
    //send every Character in array
    uint8_t i = 0;
    while(data[i] != '\0'){
            EUSART_Write(data[i]);
            i++;
        }
    
    //Writing New Line after String
    EUSART_Write(0x0A);
}


void EUSART_Transmit_ISR(void)
{
    //check if data is in TX Buffer
    if(sizeof(eusartTxBuffer) > eusartTxBufferRemaining)
    {
        //load Data in Register
        TX1REG = eusartTxBuffer[eusartTxTail++];
        
        //if Buffer is Empty set TX End to 0
        if(sizeof(eusartTxBuffer) <= eusartTxTail)
        {
            eusartTxTail = 0;
        }
        eusartTxBufferRemaining++;
    }
    else
    {
        //clear Interrupt Flag
        PIE3bits.TXIE = 0;
    }
}

void EUSART_Receive_ISR(void)
{
    //resetting Timer 0 
    TMR1_StopTimer();
    TMR1_WriteTimer(0x00);
    
    //Resetting Recieved Status
    eusartRxStatusBuffer[eusartRxHead].status = 0;

    //Check if Framing Error
    if(RC1STAbits.FERR){
        eusartRxStatusBuffer[eusartRxHead].ferr = 1;
        EUSART_FramingErrorHandler();
    }

    //Check if Overrun Occured
    if(RC1STAbits.OERR){
        eusartRxStatusBuffer[eusartRxHead].oerr = 1;
        EUSART_OverrunErrorHandler();
    }
    
    //check if Error Occured
    if(eusartRxStatusBuffer[eusartRxHead].status){
        EUSART_ErrorHandler();
    } 
    //write Data in Data Array
    else {
        EUSART_RxDataHandler();
        //Start Timer 0 
        //if Timer 0  doesn't get reset during 2ms, the received Data gets Parsed
        TMR1_StartTimer();
        }
    
}

//Putting Recieved Data into Data array
void EUSART_RxDataHandler(void){
    
    if(RC1REG == 0x0D)
    {
     sec = true;   
    }else
    {
    rx_data[rx_data_end++] = RC1REG;
    rx_data[rx_data_end] = '\0';
    }
    
}

void EUSART_DefaultFramingErrorHandler(void){}

void EUSART_DefaultOverrunErrorHandler(void){
    // EUSART error - restart

    RC1STAbits.CREN = 0;
    RC1STAbits.CREN = 1;

}

void EUSART_DefaultErrorHandler(void){
    EUSART_RxDataHandler();
}

void EUSART_SetFramingErrorHandler(void (* interruptHandler)(void)){
    EUSART_FramingErrorHandler = interruptHandler;
}

void EUSART_SetOverrunErrorHandler(void (* interruptHandler)(void)){
    EUSART_OverrunErrorHandler = interruptHandler;
}

void EUSART_SetErrorHandler(void (* interruptHandler)(void)){
    EUSART_ErrorHandler = interruptHandler;
}

void EUSART_SetTxInterruptHandler(void (* interruptHandler)(void)){
    EUSART_TxDefaultInterruptHandler = interruptHandler;
}

void EUSART_SetRxInterruptHandler(void (* interruptHandler)(void)){
    EUSART_RxDefaultInterruptHandler = interruptHandler;
}
/**
  End of File
*/
