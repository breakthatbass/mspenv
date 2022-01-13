/**
 * uartgets.c - read in an entire line at a time
 *
 * Taylor Gamache
 * 12/14/21
 * */
#include <msp430.h>
#include "../lib/uartio.h"

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;   //Stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;

	uart_init();

	char b[200] = {0};

	while (1) {
		uartprintf("what is your name?\n\r");
		uart_gets(b, 20);
		__delay_cycles(10000);
		uartprintf("\n\rhello, %s\n\r", b);
	}
}
