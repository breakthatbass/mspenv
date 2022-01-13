/**
 * uart_gets.c - a program to test the uart_gets() function from uartio.c
 * 
 * Taylor Gamache
 * Jan 13, 2022
 * */
#include <msp430fr5994.h>
#include <lib/uartio.h>

#define MAXLINE 20

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;
	PM5CTL0 &= ~LOCKLPM5;

    // buffer to hold the input
    char buf[MAXLINE] = {0};

	uart_init();
    uartputs("\nuart_gets() tests\n");

	while (1) {
        // read in a line to buf[]
        uart_gets(buf, MAXLINE);
        uartputs(buf);
    }
}