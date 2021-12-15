/**
 * readfile.c - read a file line by line through the UART
 * console and print put each line. This requires some script
 * or something to open the file and read it and send each line.
 *
 * see mcusend script in scripts directory.
 *
 * Taylor Gamache
 * 12/14/21
 * */
#include <msp430.h>
#include <string.h>
#include "../lib/uartio.h"

#define MAXLINE 50

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;   //Stop watchdog timer
	PM5CTL0 &= ~LOCKLPM5;

	uart_init();

	char line[MAXLINE] = {0};

	while (1) {
		while (uartgets(line, MAXLINE)) {
			uartprintf("line: %s\n\r", line);
			memset(line, 0, MAXLINE);
		}
	}
}
