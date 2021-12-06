 /**
 * uart.c - a simple program to test out the uartprintf() function.
 *
 * an FTDI cable is needed to connect the UART pins to the computer.
 * from there run the command `screen <location-of-device> <baud rate>`
 * and that will open the console.
 *
 * in this case on MacOS I ran:
 *
 * screen /dev/cu.usbserial-AR0JW545 9600
 *
 * */
#include <msp430fr5994.h>
#include "../lib/uartio.h"

#define COUNTER_VALUE 1250


void main(void) {
	WDTCTL = WDTPW | WDTHOLD;   //Stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;


	uart_init();
	unsigned char *s = "Hello, my name is Taylor";
	unsigned int r = 34;

	while (1) {
		uartprintf("%s and I am %u years old\r\n", s, r++);
		
		__delay_cycles(500000L);
	}
}

