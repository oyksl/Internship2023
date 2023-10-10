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

#define SYSCLK	(32000000)
#define PBCLK  (SYSCLK)

//  Slave Address parameters
#define SLAVE_ADDRESS 0x30
#define SLAV_ADDRESS_R ((int) SLAVE_ADDRESS)*2 + 1
#define SLAV_ADDRESS_W ((int) SLAVE_ADDRESS)*2

// memory address
#define MEMORY_ADDRESS 0x01



void InitI2C(double freq);
//void __ISR(_I2C_1_VECTOR, IPL3AUTO) _SlaveI2CHandler(void);
