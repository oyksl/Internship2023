#define _SUPPRESS_PLIB_WARNING
/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/
#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif


#include <plib.h>           /* Include to use PIC32 peripheral libraries      */
#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */
#include <stdio.h>
#include <string.h>
#include "GenericTypeDefs.h"
#include "user.h"
#include "i2c2_ipmi.h"

#define SYSCLK	(32000000)
#define PBCLK  (SYSCLK)



// volatile variables to hold the switch
volatile unsigned char dataRead = 0;

///////////////////////////////////////////////////////////////////
//
//	InitI2C
//
// 	Perform initialisation of the I2C module to operate as a slave
//
///////////////////////////////////////////////////////////////////
void InitI2C(double freq)
{
    double BRG_VAL;
    BRG_VAL = (1/(2*freq))-0.000000104;
    BRG_VAL *= (SYSCLK/2)-2; 
	
	// Enable the I2C module with clock stretching enabled
	OpenI2C2(I2C_ON | I2C_7BIT_ADD | I2C_STR_EN, BRG_VAL);
	
	// set the address of the slave module, address matching is with bits
	// 7:1 of the message compared with bits 6:0 of the ADD SFR so we
	// need to shift the desired address 1 bit. 
	I2C2ADD = SLAVE_ADDRESS; // >> 1;
	I2C2MSK = 0; 

    I2C2TRN = 0;
    I2C2RCV = 0;
}
