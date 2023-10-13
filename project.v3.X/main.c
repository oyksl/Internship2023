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
#include "system.h"         /* System funct/params, like osc/periph config    */
#include "user.h"
#include <stdio.h>
#include <string.h>

#define TMP275_PR 0x00    
unsigned int value;
    
int main(void) {
    /* TODO Add user clock/system configuration code if appropriate.  */
    SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL);
    /* Initialize I/O and Peripherals for application */
    init_GPIO();
    UART_init();
    delay_ms(1000);
    I2C_init(100000);
    
    delay_ms(1000);
    print_uart("\n\r");
    print_uart("*****************************\n\r");
    print_uart("Hello! \n\r");
    print_uart("*****************************\n\r");
    
    while (1)
    {     
        
        TMP275_read(TMP275_PR, &value);
        delay_ms(1000);
        char log[200];
        sprintf(log, "Temperature : %i°C \r\n", value);
        print_uart(log);
        delay_ms(1000);
                      
    }
   
    return 0;
}

