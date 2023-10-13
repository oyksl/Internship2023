/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
#define _SUPPRESS_PLIB_WARNING

#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

#include <plib.h>            /* Include to use PIC32 peripheral libraries     */
#include <stdint.h>           /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */
#include <string.h>

#define TMP275_ADDRESS_W 0x92
#define TMP275_ADDRESS_R 0x93

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

void UART_init() {   
    UARTConfigure(UART3, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetLineControl(UART3, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(UART3, GetPeripheralClock(), UART_BAUDRATE);
    UARTEnable(UART3, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

}


void UART_SendDataBuffer(UART_MODULE UART_MODULE_ID, const char *buffer, UINT32 size) {
while(size)
    {
        while(!UARTTransmitterIsReady(UART_MODULE_ID))
            ;

        UARTSendDataByte(UART_MODULE_ID, *buffer);

        buffer++;
        size--;
    }

    while(!UARTTransmissionHasCompleted(UART_MODULE_ID))
        ;
}

void print_uart(char log[150]) {
        UART_SendDataBuffer(UART3,log, strlen(log));
}

void delay_ms(int ms)
{
    int startTime, delayCount;
    startTime = ReadCoreTimer();
    delayCount = ms * DELAY_MS_CLK;
    while(ReadCoreTimer() - startTime < delayCount)
    {
        ;
    }
}

void delay_us(int us)
{
    int startTime, delayCount;
    startTime = ReadCoreTimer();
    delayCount = us * DELAY_US_CLK;
    while(ReadCoreTimer() - startTime < delayCount)
    {
        ;
    }
}

void I2C_init(double freq){
    double BRG;
    
    I2C5CON = 0; // turn off i2c5
    I2C5CONbits.DISSLW = 1; // disable slew rate
    
    BRG = (1/(2*freq))-0.000000104;
    BRG *= (SYS_FREQ/2)-2;
    
    I2C5BRG = (int)BRG;
    I2CSetFrequency(I2C5,SYS_FREQ, I2C_CLOCK_FREQ);
    I2C5CONbits.A10M = 0;
    I2C5CONbits.ON = 1; // turn on i2c5
    
}
 
void I2C_wait_for_idle(void)
{
    while(I2C5CON & 0x1F); // Acknowledge sequence not in progress
                                // Receive sequence not in progress
                                // Stop condition not in progress
                                // Repeated Start condition not in progress
                                // Start condition not in progress
    while(I2C5STATbits.TRSTAT); // Bit = 0 ? Master transmit is not in progress
}

// I2C_start() sends a start condition  
void I2C_start()
{
    I2C_wait_for_idle();
    I2C5CONbits.SEN = 1;
    while (I2C5CONbits.SEN == 1);
}


// I2C_stop() sends a stop condition  
void I2C_stop()
{
    I2C_wait_for_idle();
    I2C5CONbits.PEN = 1;
}

// I2C_restart() sends a repeated start/restart condition
void I2C_restart()
{
    I2C_wait_for_idle();
    I2C5CONbits.RSEN = 1;
    while (I2C5CONbits.RSEN == 1);
}

// I2C_ack() sends an ACK condition
void I2C_ack(void)
{
    I2C_wait_for_idle();
    I2C5CONbits.ACKDT = 0; // Set hardware to send ACK bit
    I2C5CONbits.ACKEN = 1; // Send ACK bit, will be automatically cleared by hardware when sent  
    while(I2C5CONbits.ACKEN); // Wait until ACKEN bit is cleared, meaning ACK bit has been sent
}

// I2C2_ack() sends an ACK condition
void I2C2_ack(void)
{
    I2C2CONbits.ACKDT = 0; // Set hardware to send ACK bit
    I2C2CONbits.ACKEN = 1; // Send ACK bit, will be automatically cleared by hardware when sent  
    while(I2C2CONbits.ACKEN); // Wait until ACKEN bit is cleared, meaning ACK bit has been sent
}

// I2C_nack() sends a NACK condition
void I2C_nack(void) // Acknowledge Data bit
{
    I2C_wait_for_idle();
    I2C5CONbits.ACKDT = 1; // Set hardware to send NACK bit
    I2C5CONbits.ACKEN = 1; // Send NACK bit, will be automatically cleared by hardware when sent  
    while(I2C5CONbits.ACKEN); // Wait until ACKEN bit is cleared, meaning NACK bit has been sent
}

// I2C2_nack() sends a NACK condition
void I2C2_nack(void) // Acknowledge Data bit
{
    I2C2CONbits.ACKDT = 1; // Set hardware to send NACK bit
    I2C2CONbits.ACKEN = 1; // Send NACK bit, will be automatically cleared by hardware when sent  
    while(I2C2CONbits.ACKEN); // Wait until ACKEN bit is cleared, meaning NACK bit has been sent
}

// address is I2C slave address, set wait_ack to 1 to wait for ACK bit or anything else to skip ACK checking  
void I2C_write(unsigned char address, char wait_ack)
{
    I2C5TRN = address;// | 0;              // Send slave address with Read/Write bit cleared
    while (I2C5STATbits.TBF == 1);      // Wait until transmit buffer is empty
    I2C_wait_for_idle();                // Wait until I2C bus is idle
}

// value is the value of the data we want to send, set ack_nack to 0 to send an ACK or anything else to send a NACK  
void I2C_read(unsigned int *value, char ack_nack)
{
    I2C5CONbits.RCEN = 1;               // Receive enable
    while (I2C5CONbits.RCEN);           // Wait until RCEN is cleared (automatic) 
    while (!I2C5STATbits.RBF);          // Wait until Receive Buffer is Full (RBF flag)  
    *value = I2C5RCV ;                   // Retrieve value from I2C5RCV

    if (ack_nack)                      // Do we need to send an ACK or a NACK?  
        I2C_ack();                      // Send ACK  
    else
        I2C_nack();                     // Send NACK  
}

// Read a byte from register at reg_address and return in *value
void TMP275_read(unsigned char reg_address, unsigned int *value)
{
    I2C_start();                        /* Send start condition */  
    I2C_write(TMP275_ADDRESS_W, 1);
    I2C_write(reg_address, 1);          /* Send the register address (RA) */  
    I2C_stop();
    I2C_start();
    I2C_write(TMP275_ADDRESS_R, 1);
    I2C_read(value, 1);                 /* Read value from the I2C bus */  
    I2C_stop();                         /* Send stop condition */  
}
