/**
 * uart_tests.c - a program to test the uart_getc() function from uartio.c
 * 
 * Taylor Gamache
 * Jan 13, 2022
 * */
#include <msp430fr5994.h>
#include <lib/uartio.h>


void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;
	PM5CTL0 &= ~LOCKLPM5;

    char c;

	uart_init();
    uart_puts("\nuart_getc() tests\n");

	while (1) {

        // read char from stdin
        c = uart_getc();

        if (c == '\r') {
            // if enter, go to beginning of next line
            uart_putc('\n');
            uart_putc('\r');

        /**
         * reading in chars doesn't detect backspace as '\b'
         * but instead as 0x7f. '\b' can be printed to move the
         * cursor back one spot though.
         * */
        } else if (c == 0x7f) {
            uart_putc('\b');
            uart_putc(' ');
            uart_putc('\b');

        } else uart_putc(c);
    }
}