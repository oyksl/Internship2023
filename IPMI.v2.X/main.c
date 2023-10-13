/***********************************************************************
 * PIC32 I2C Slave Code                
 ***********************************************************************/

#define _SUPPRESS_PLIB_WARNING
/******************************************************************************/
/*  Files to Include                                                          */
/******************************************************************************/
#ifdef __XC32
    #include <xc.h>          /* Defines special function registers, CP0 regs  */
#endif


#include <plib.h>           /* Include to use PIC32 peripheral libraries      */
#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */
#include <stdio.h>
#include <string.h>
#include "user.h"
#include "i2c2_ipmi.h"


#define SYSCLK	(32000000)
#define PBCLK  (SYSCLK)

int main (void)
{
	// set for 32MHz operation
	SYSTEMConfigPerformance(SYSCLK);
	// set the Pbus to be 16000000
	mOSCSetPBDIV(OSC_PB_DIV_2);
	// disable the JTAG port
	mJTAGPortEnable(0);
	// enable interrupts
	INTEnableSystemMultiVectoredInt();
    
    init_GPIO(); // initialize GPIO
    UART_init(); // initialize UART
    I2C_init(I2C_CLOCK_FREQ); // initialize I2C5 for temperature sensor
	InitI2C(I2C_CLOCK_FREQ); // initialize I2C2 for IPMI
    delay_ms(1000);
    
    print_uart("\n\r");
    print_uart("*****************************\n\r");
    print_uart("Hello! \n\r");
    print_uart("*****************************\n\r");
    
    while(1){
        BYTE data = 0;
        BOOL IsRecAv = I2CReceivedDataIsAvailable(I2C2);
        
        /*If a data is received the following code piece works:*/
        if (IsRecAv){
        data = I2CGetByte(I2C2); // tha data in the receive buffer is fetched
        char log[200];
        sprintf(log, "Address with R/W bit: 0x%x \r\n", data); print_uart(log);/
        
        delay_ms(1000);
        
        if(data == SLAV_ADDRESS_W){
            
            print_uart("Correct Address Received with Write Bit\r\n"); /* Write*/
            I2CAcknowledgeByte(I2C2, TRUE); 
            print_uart("ACK sent\r\n");
        }
        else if(data == SLAV_ADDRESS_R){
            
            print_uart("Correct Address Received with Read Bit\r\n"); /* Read*/
            I2CAcknowledgeByte(I2C2, TRUE);
            print_uart("ACK sent\r\n");
            
            BYTE response = 0x1;
            I2CSendByte(I2C2, response); 
            print_uart("Data sent\r\n");    
        }
        else print_uart("Wrong address received!\r\n");
        I2C2RCV = 0; 

    }   
    }
}
    



