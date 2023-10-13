/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING 
#define _DISABLE_OPENADC10_CONFIGSCAN_WARNING 

/* TODO Application specific user parameters used in user.c may go here */

#define SYS_FREQ     32000000L
#define UART_BAUDRATE   115200

#define I2C_CLOCK_FREQ             100000
#define	GetPeripheralClock()		(SYS_FREQ/(1 << OSCCONbits.PBDIV))
#define	GetInstructionClock()		(SYS_FREQ)
#define DELAY_MS_CLK ((GetInstructionClock()/2)/1000)
#define DELAY_US_CLK ((GetInstructionClock()/2)/1000000)
#define TMP_SENSOR_1 0x49

void i2c_master_setup(UINT16 ADDRESS);
void i2c_master_start();
void i2c_master_restart();
void i2c_master_send(unsigned char byte);
unsigned char i2c_master_receive();
void i2c_master_ack();

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
