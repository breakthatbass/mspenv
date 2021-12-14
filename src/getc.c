/**
 * uartgetc.c - read in a string one byte at a time, then print it out
 *
 * Taylor Gamache
 * 12/14/21
 * */

#include <msp430fr5994.h>
#include "../lib/uartio.h"


void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;
	PM5CTL0 &= ~LOCKLPM5;

	uart_init();

	char buf[40] = {0};
	int c, i;
	while (1) {
		i = 0;
		while ((c = uartgetc())) {
			if (c == '\r') break;
			uartputc(c);
			buf[i++] = c;
		}
		buf[i] = '\0';
		uartprintf("\n\r%s\n\r", buf);
	}
}
