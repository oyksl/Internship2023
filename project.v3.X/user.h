/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING 
#define _DISABLE_OPENADC10_CONFIGSCAN_WARNING 

/* TODO Application specific user parameters used in user.c may go here */

#define SYS_FREQ     32000000L          //!!! eger system frekansi degistirilirse bu deger de degismeli !!!!
#define UART_BAUDRATE   115200
// #define UART_PIC_INTERFACE UART3

#define I2C_CLOCK_FREQ             100000
#define	GetPeripheralClock()		(SYS_FREQ/(1 << OSCCONbits.PBDIV))
#define	GetInstructionClock()		(SYS_FREQ)
#define DELAY_MS_CLK ((GetInstructionClock()/2)/1000)
#define DELAY_US_CLK ((GetInstructionClock()/2)/1000000)
#define TMP_SENSOR_1 0x49


/*
 * Add delay for each pin assignment for overcoming Read-Modify-Write Issue
 */
// Port A
#define	VPX_GA3	PORTAbits.RA0          // -   PIC_JTAG_TMS
#define	VPX_GA4	PORTAbits.RA1         //  -   PIC_JTAG_TCK
#define	PIC_IPMI_SCL0 PORTAbits.RA2
#define	PIC_IPMI_SDA0 PORTAbits.RA3
#define	VPX_GAP PORTAbits.RA4         //  -   PIC_JTAG_TDI
#define	BATLOW_N PORTAbits.RA5        //  -   PIC_JTAG_TDO
#define	EN_P0V92 PORTAbits.RA6
#define	EN_DDR_VREF	PORTAbits.RA7
#define	PIC_SERIRQ PORTAbits.RA14
#define	SUS_STAT_N PORTAbits.RA15

// Port B
#define	PIC_PROG_SDA	PORTBbits.RB0
#define	PIC_PROG_SCL	PORTBbits.RB1
#define	PGOOD_RAIL0	PORTBbits.RB2
#define	PGOOD_RAIL1	PORTBbits.RB3
#define	PGOOD_RAIL2	PORTBbits.RB4
#define	EN_PVCCCORE	PORTBbits.RB5
#define	EN_PVCCSA	PORTBbits.RB6
#define	EN_PVCCGT	PORTBbits.RB7
#define	EN_VDDQ_VTT	PORTBbits.RB8
#define	EN_PVCCIO	PORTBbits.RB9
#define	EN_PVCCPRIM_1P05	PORTBbits.RB10
#define	EN_PVPP	PORTBbits.RB11
#define	P0V92_PIC_ADC	PORTBbits.RB12
#define	P3V3_PIC_ADC	PORTBbits.RB13
#define	P5V0_PIC_ADC	PORTBbits.RB14
#define	P12V_PIC_ADC	PORTBbits.RB15

// Port C
#define	SYS_RESET_N	PORTCbits.RC1
#define	GDISCRETE	PORTCbits.RC2
#define	PIC_IO	PORTCbits.RC3
#define	PIC_SPI0_MISO	PORTCbits.RC4
#define	XL710_PWR_OK	PORTCbits.RC12
#define	CB_RESET_N	PORTCbits.RC13
#define	SYS_nCONT	PORTCbits.RC14
#define	XL710_AUX_PWR	PORTCbits.RC15

// Port D
#define	PIC_SPI0_MOSI	PORTDbits.RD0
#define	PLT_RST_N	PORTDbits.RD1
#define	PM_SLP_M_N	PORTDbits.RD2
#define	PM_SLP_S0_N	PORTDbits.RD3
#define	PM_SLP_S3_N	PORTDbits.RD4
#define	PM_SLP_S4_N	PORTDbits.RD5
#define	PM_SLP_S5_N	PORTDbits.RD6
#define	PCH_DPWROK	PORTDbits.RD7
#define	PM_PWRBTN_N	PORTDbits.RD8
#define	PIC_SPI0_CS0_N	PORTDbits.RD9
#define	PIC_SPI0_CLK	PORTDbits.RD10
#define	SYS_PWROK	PORTDbits.RD11
#define	PM_RSMRST_N	PORTDbits.RD12
#define	PM_PCH_PWROK	PORTDbits.RD13
#define	H_VCCST_PWRGD_PIC	PORTDbits.RD14
#define	EN_P5V0	PORTDbits.RD15

// Port E
#define	PGOOD_P5V0	PORTEbits.RE0
#define	PGOOD_P0V92	PORTEbits.RE1
#define	PGOOD_PVCCIO	PORTEbits.RE2
#define	PGOOD_PVCCPRIM_1P05	PORTEbits.RE3
#define	PGOOD_PVDDQ_PVTT	PORTEbits.RE4
#define	VPX_GA0	PORTEbits.RE5
#define	VPX_GA1	PORTEbits.RE6
#define	VPX_GA2	PORTEbits.RE7
#define	VPX_nRESET_OUT	PORTEbits.RE8
#define	UNIQUE_ID	PORTEbits.RE9
// Port F
#define	PM_SLP_SUS_N	PORTFbits.RF0
#define	CPU_C10_GATE_N_PIC	PORTFbits.RF1
#define	PIC_IPMI_SDA1	PORTFbits.RF2
#define	MASKABLE_nRST	PORTFbits.RF3
#define	PIC_SDA	PORTFbits.RF4
#define	PIC_SCL	PORTFbits.RF5
#define	PIC_IPMI_SCL1	PORTFbits.RF8
#define	VPX_nRESET_IN	PORTFbits.RF12
#define	CAN1_nIRQ	PORTFbits.RF13

// Port G
#define	SW_SELECT_UART  PORTGbits.RG0
#define	SW_SELECT_SPI 	PORTGbits.RG1
#define	EN_P3V3  PORTGbits.RG2
#define	VCCSTG_EN_PIC   PORTGbits.RG3
#define	THRMTRIP_N	PORTGbits.RG6
#define	PIC_UART_RX	PORTGbits.RG7
#define	PIC_UART_TX	PORTGbits.RG8
#define	VR_FAULT	PORTGbits.RG9
#define	H_PROCHOT_N_PIC PORTGbits.RG12
#define	H_CATERR_N_PIC	PORTGbits.RG13
#define	CAN1_nRESET	PORTGbits.RG14
#define	PIC_TIMER_RST	PORTGbits.RG15


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
