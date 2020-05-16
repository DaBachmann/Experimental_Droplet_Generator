/**
  Microchip Code Pin Manager File

  File Name:
    pin_manager.c

  Summary:
    This is the Microchip Pin Manager file for initialising every Pin 
 
  Author:
    D.Bachmann
  
  Date:
    11.05.2020
  
  Revision:
    1.0
*/

#include "pin_manager.h"





void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISA = 0xFF;
    TRISB = 0xF6;
    TRISC = 0xF8;

    /**
    ANSELx registers
    */
    ANSELC = 0x78;
    ANSELB = 0xF5;
    ANSELA = 0x4F;

    /**
    WPUx registers
    */
    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    /**
    ODx registers
    */
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;

    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLE = 0x08;





   
    
	
    RXPPS = 0x09;   //RB1->EUSART:RX;    
    SSP1CLKPPS = 0x11;   //RC1->MSSP1:SCK1;    
    INT0PPS = 0x04;   //RA4->EXT_INT:INT0;    
    RB0PPS = 0x09;   //RB0->EUSART:TX;    
    RC1PPS = 0x0D;   //RC1->MSSP1:SCK1;    
    RC2PPS = 0x0E;   //RC2->MSSP1:SDO1;    
    T0CKIPPS = 0x05;   //RA5->TMR0:T0CKI;    
    SSP1DATPPS = 0x17;   //RC7->MSSP1:SDI1;    
}
  

/**
 End of File
*/