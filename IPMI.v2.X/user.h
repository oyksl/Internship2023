/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING 
#define _DISABLE_OPENADC10_CONFIGSCAN_WARNING 

/* TODO Application specific user parameters used in user.c may go here */

#define SYS_FREQ     32000000L          
#define UART_BAUDRATE   115200
// #define UART_PIC_INTERFACE UART3

#define I2C_CLOCK_FREQ             10000
#define	GetPeripheralClock()		(SYS_FREQ/(1 << OSCCONbits.PBDIV))
#define	GetInstructionClock()		(SYS_FREQ)
#define DELAY_MS_CLK ((GetInstructionClock()/2)/1000)
#define DELAY_US_CLK ((GetInstructionClock()/2)/1000000)

#define TMP_SENSOR_1 0x49
#define TMP275_PR 0x00

void init_GPIO();
void UART_init();
void UART_SendDataBuffer(UART_MODULE UART_MODULE_ID, const char *buffer, UINT32 size);
void print_uart(char log[150]);
void delay_ms(int ms);
void delay_us(int us);

void I2C_init(double freq);
void I2C_wait_for_idle(void);
void I2C_start();
void I2C_stop();
void I2C_restart();
void I2C_ack(void);
void I2C_nack(void);
void I2C_write(unsigned char address, char wait_ack);
void I2C_read(unsigned int*value, char ack_nack);
void TMP275_read(unsigned char reg_address, unsigned int *value);
