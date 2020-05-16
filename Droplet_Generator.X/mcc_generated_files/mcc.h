/**
  Microchip Code Configurator Header File

  File Name:
    mcc.h

  Summary:
    This is the Microchip Code Configurator header file to link every files 
    and impelement global defines

  Author:
    D.Bachmann
  
  Date:
    11.05.2020
  
  Revision:
    1.0
*/


#ifndef MCC_H
#define	MCC_H
#include <xc.h>
#include "device_config.h"
#include "pin_manager.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "interrupt_manager.h"
#include "spi1.h"
#include "tmr3.h"
#include "ext_int.h"
#include "tmr1.h"
#include "tmr0.h"
#include "eusart.h"
#include "../parse.h"
#include "../ad9833.h"

#define FSYNC PORTCbits.RC0
#define EN PORTBbits.RB3
#define CONFIGURE 1
#define PULSE 2


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the device to the default states configured in the
 *                  MCC GUI
 * @Example
    SYSTEM_Initialize(void);
 */
void SYSTEM_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the oscillator to the default states configured in the
 *                  MCC GUI
 * @Example
    OSCILLATOR_Initialize(void);
 */
void OSCILLATOR_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Initializes the PMD module to the default states configured in the
 *                  MCC GUI
 * @Example
    PMD_Initialize(void);
 */
void PMD_Initialize(void);


#endif	/* MCC_H */
/**
 End of File
*/