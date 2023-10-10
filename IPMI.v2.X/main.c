/***********************************************************************
 * PIC32 I2C Slave Code                
 ***********************************************************************/

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
#include "user.h"
#include "i2c2_ipmi.h"


#define SYSCLK	(32000000)
#define PBCLK  (SYSCLK)


/*Configuration Bits*/


#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_16         // PLL Multiplier (16x Multiplier)
#pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider (PLL Divide by 2)

 
// DEVCFG1
#pragma config FNOSC = FRCPLL              // Oscillator Selection Bits (Fast RC Osc (FRC))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/2)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
//#pragma config WINDIS = OFF             // Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
//#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window Size is 25%)

// DEVCFG0
//#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx1        // ICE/ICD Comm Channel Select (Communicate on PGEC1/PGED1)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

///////////////////////////////////////////////////////////////////
//
//	main routine
// 
//	This code demonstrates using the PIC32 as an I2C slave
//	
//
///////////////////////////////////////////////////////////////////
int main (void)
{
	// set for 32MHz operation
	SYSTEMConfigPerformance(SYSCLK);
	// set the Pbus to be 16000000
	mOSCSetPBDIV(OSC_PB_DIV_2);
	// disable the JTAG port
	mJTAGPortEnable(0);
	// enable interrupts
	INTEnableSystemMultiVectoredInt(); // interrupt routine kodu ipmi.c dosyas?nda var fakat ?u anda aktif olarak interrupt kullan?lm?yor main.c'de
    
    init_GPIO(); // initialize GPIO
    UART_init(); // initialize UART
    I2C_init(I2C_CLOCK_FREQ); // initialize I2C5 for temperature sensor
	InitI2C(I2C_CLOCK_FREQ); // initialize I2C2 for IPMI
    delay_ms(1000);
    
    print_uart("\n\r");
    print_uart("*****************************\n\r");
    print_uart("Hello! \n\r");
    print_uart("*****************************\n\r");
    
//    unsigned int value; TMP275_read(TMP275_PR, &value);
//    char log[200];
//    sprintf(log, "Temperature : %i°C \r\n", value); print_uart(log);
//    
//    unsigned char dataread; dataread = SlaveReadI2C2();
//    char log[200];
//    sprintf(log, "Data : %i°C \r\n", dataread); print_uart(log);
//    print_uart("Hello! \n\r");
    
    while(1){
        BYTE data = 0;
        BOOL IsRecAv = I2CReceivedDataIsAvailable(I2C2);
        
        /*If a data is received the following code piece works:*/
        if (IsRecAv){
        data = I2CGetByte(I2C2); // tha data in the receive buffer is fetched
        char log[200];
        sprintf(log, "Address with R/W bit: 0x%x \r\n", data); print_uart(log); /* diolan controlpanel üzerinden gelen read write 
                                                                                 * komutuna göre pic'in fetch etti?i data de?erini printler*/
        
        delay_ms(1000);
        
        if(data == SLAV_ADDRESS_W){
            
            print_uart("Correct Address Received with Write Bit\r\n"); /* Write komutu geldi*/
            I2CAcknowledgeByte(I2C2, TRUE); /* diolan üzerinden komut gönderince arkada dönen sequence'? bilmedi?imiz için ack sinyali 
                                             gönderio göndermememiz gerekti?ini incelemek laz?m*/
            print_uart("ACK sent\r\n");
        }
        else if(data == SLAV_ADDRESS_R){
            
            print_uart("Correct Address Received with Read Bit\r\n"); /* Read komutu geldi*/
            I2CAcknowledgeByte(I2C2, TRUE);
            print_uart("ACK sent\r\n");
            
            BYTE response = 0x1;
            I2CSendByte(I2C2, response); /*herhangi bir response göndermesini denedim ama öncesindeki sequence'da bir s?k?nt? oldu?undan dolay? receive buffer'? bo?alm?yor diye
                                          dü?ünüyorum. normalde otomatik bo?almal?yd?.*/
            print_uart("Data sent\r\n");    
        }
        else print_uart("Wrong address received!\r\n");
        I2C2RCV = 0; 

    }   
    }
}
    



