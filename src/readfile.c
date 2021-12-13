/**
 * readfile.c - open a uart connection to the PC and use the script
 * `mspsend' to send a file to this MCU. Read the file line by line
 * while printing out each line
 *
 * 12/12/21
 * */
#include <msp430.h>
#include "../lib/uartio.h"

#define MAXLINE 100

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;
	PM5CTL0 &= ~LOCKLPM5;

	char buf[MAXLINE];

	uart_init();

	while (1) {
		while (uartgets(buf, MAXLINE)) {
			uartprintf("%s\n", buf);
		}
	}
}
