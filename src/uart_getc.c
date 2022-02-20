/**
 * uart_tests.c - a program to test the uart_getc() function from uartio.c
 * 
 * Taylor Gamache
 * Jan 13, 2022
 * */
#include <msp430fr5994.h>
#include <lib/uartio.h>

#define BACKSPACE 0x7f


void backspace(void)
{
    uart_putc('\b');
    uart_putc(' ');
    uart_putc('\b');
}


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

        } else if (c == BACKSPACE) {
            backspace();

        } else uart_putc(c);
    }
}