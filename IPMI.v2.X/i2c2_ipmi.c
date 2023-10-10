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
    BRG_VAL *= (SYSCLK/2)-2; /*Baud rate generator register'? icin*/
	
	// Enable the I2C module with clock stretching enabled
	OpenI2C2(I2C_ON | I2C_7BIT_ADD | I2C_STR_EN, BRG_VAL);
	
	// set the address of the slave module, address matching is with bits
	// 7:1 of the message compared with bits 6:0 of the ADD SFR so we
	// need to shift the desired address 1 bit. 
	I2C2ADD = SLAVE_ADDRESS; // >> 1;
	I2C2MSK = 0; // address register?ndaki masklenmesi istenen bitler için
	
	// configure the interrupt priority for the I2C peripheral
	//mI2C2SetIntPriority(I2C_INT_PRI_3 | I2C_INT_SLAVE);

	// clear pending interrupts and enable I2C interrupts
//	mI2C2SClearIntFlag();
//	EnableIntSI2C2;
    
    /*Interruptlar kapat?ld?!*/
    I2C2TRN = 0;
    I2C2RCV = 0;
}


///////////////////////////////////////////////////////////////////
//
// Slave I2C interrupt handler
// This handler is called when a qualifying I2C events occurs
// this means that as well as Slave events 
// Master and Bus Collision events will also trigger this handler.
//
///////////////////////////////////////////////////////////////////
//
//void __ISR(_I2C_1_VECTOR, IPL3AUTO) _SlaveI2CHandler(void)
//{
//	unsigned char temp;
//	static unsigned int dIndex;
//	
//	// check for MASTER and Bus events and respond accordingly
//	if (IFS1bits.I2C2MIF == 1) {
//		mI2C2MClearIntFlag();
//		return;		
//	}
//	if (IFS1bits.I2C2BIF == 1) {
//		mI2C2BClearIntFlag();
//		return;
//	}
//
//	
//	// handle the incoming message
//	if ((I2C2STATbits.R_W == 0) && (I2C2STATbits.D_A == 0)) {
//		// R/W bit = 0 --> indicates data transfer is input to slave
//		// D/A bit = 0 --> indicates last byte was address  
//		
//		// reset any state variables needed by a message sequence	
//		// perform a dummy read of the address
//		temp = SlaveReadI2C2();
//        print_uart("input to slave & last byte was address\r\n");
//        
//        I2C2CONbits.ACKDT = 0; // Set hardware to send ACK bit
//        I2C2CONbits.ACKEN = 1; // Send ACK bit, will be automatically cleared by hardware when sent  
//        while(I2C2CONbits.ACKEN); // Wait until ACKEN bit is cleared, meaning ACK bit has been sent
//    
//    
//
//		// release the clock to restart I2C
//		I2C2CONbits.SCLREL = 1; // release the clock
//
//	} else if ((I2C2STATbits.R_W == 0) && (I2C2STATbits.D_A == 1)) {
//		// R/W bit = 0 --> indicates data transfer is input to slave
//		// D/A bit = 1 --> indicates last byte was data
//		
//		// writing data to our module, just store it in adcSample
//		dataRead = SlaveReadI2C2();
//		print_uart("input to slave & last byte was data\r\n");
//        
//        I2C2CONbits.ACKDT = 0; // Set hardware to send ACK bit
//        I2C2CONbits.ACKEN = 1; // Send ACK bit, will be automatically cleared by hardware when sent  
//        while(I2C2CONbits.ACKEN); // Wait until ACKEN bit is cleared, meaning ACK bit has been sent
//        
//		// release the clock to restart I2C
//		I2C2CONbits.SCLREL = 1; // release clock stretch bit
//
//	} else if ((I2C2STATbits.R_W == 1) && (I2C2STATbits.D_A == 0)) {
//		// R/W bit = 1 --> indicates data transfer is output from slave
//		// D/A bit = 0 --> indicates last byte was address
//	
//		// read of the slave device, read the address 
//		temp = SlaveReadI2C2();
//		dIndex = 0;
//		SlaveWriteI2C2(dataRead);
//	} else if ((I2C2STATbits.R_W == 1) && (I2C2STATbits.D_A == 1)) {
//		// R/W bit = 1 --> indicates data transfer is output from slave
//		// D/A bit = 1 --> indicates last byte was data
//	
//		
//		// output the data until the MASTER terminates the
//		// transfer with a NACK, continuing reads return 0
//		if (dIndex == 0) {
//			SlaveWriteI2C2(dataRead);
//			dIndex++;
//		} else
//			SlaveWriteI2C2(0);
//	}
//	
//	// finally clear the slave interrupt flag
//	mI2C2SClearIntFlag();		
//}