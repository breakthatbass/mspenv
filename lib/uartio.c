/******************************************************************************
*
*   Author: Taylor Gamache
*   Email: gamache.taylor@gmail.com
*   
*   about 60% or so of this code comes from:
*	https://gist.github.com/nicholasjconn/2896369#file-printf-c
*
*   @name: uartio
*   @description: a handful of basic functions to read and write to UART for the msp430 MCU.
*
******************************************************************************/

#include <msp430.h>
#include "stdarg.h"
#include "uartio.h"
#include "stddef.h"  // for NULL



static const unsigned long dv[] = {
//  4294967296      // 32 bit unsigned max
		1000000000,// +0
		100000000, // +1
		10000000, // +2
		1000000, // +3
		100000, // +4
//       65535      // 16 bit unsigned max
		10000, // +5
		1000, // +6
		100, // +7
		10, // +8
		1 // +9
};


// convert hex to int
static void xtoa(unsigned long x, const unsigned long *dp) {
	char c;
	unsigned long d;
	if (x) {
		while (x < *dp)
			++dp;
		do {
			d = *dp++;
			c = '0';
			while (x >= d)
				++c, x -= d;
			uart_putc(c);
		} while (!(d & 1));
	} else
		uart_putc('0');
}


// print a hex char
static void puth(unsigned n) {
	static const char hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
			'9', 'A', 'B', 'C', 'D', 'E', 'F' };
	uart_putc(hex[n & 15]);
}


/**
 * uartprintf
 *
 * @desc: printf but for the msp430 MCU to print to UART.
 * 
 * @param: `fmt` - the string to print.
 * @param: `...` - the list of variables to fill in.
 * */
void uartprintf(char *fmt, ...)
{
	char *s;	// for dealing with string values
	int n;
	float f;

	va_list ap;
	va_start(ap, fmt);

	char *p = fmt;

	while (*p) {
		
		if (*p != '%') {
			uart_putc(*p);
			p++;
			continue;
		}

		switch (*++p) {
		// char
		case 'c':
			n = va_arg(ap, int);
			uart_putc(n);
			break;
		// int
		case 'd':
			n = va_arg(ap, int);
			if (n  < 0) {
				n = -n;
				uart_putc('-');
			}
			xtoa((unsigned) n, dv+5);
			break;
		// string
		case 's':
			s = va_arg(ap, char *);
			while (*s)
				uart_putc(*s++);
			break;

		// hex
		case 'x':
			n = va_arg(ap, int);
			puth(n >> 12); 
			puth(n >> 8);
			puth(n >> 4);
			puth(n);
			break;
		case '%':
			uart_putc('%');
			break;
		default:
			uart_putc(*p);
			break;
		}
		p++;
	}
	uart_putc('\r');
	va_end(ap);
}


/**
 * uart_puts
 *
 * @desc: print a string through UART
 *
 * @param: `s` - print each `char` in `s` to an open UART console.
 * */
void uart_puts(char *s) {
	while (*s) {
		if (*s == '\n') {
			uart_putc('\n');
			uart_putc('\r');
		} else uart_putc(*s);
		s++;
	}
	uart_putc('\n');
	uart_putc('\r');
}


/**
 * uart_putc
 *
 * @desc: Send a single byte to the transmit buffer register.
 *
 * @param: `byte` - byte to send to transmit buffer register.
 * */
void uart_putc(unsigned char byte)
{
	// USCI_A0 TX buffer ready?
    while(!(UCA1IFG & UCTXIFG));
	// write bite into transmit buffer register
	UCA1TXBUF = byte;
}


/**
 * uart_getc
 *
 * @desc: attempt to read a byte stored in the recieve buffer register.
 *
 * @return: if a byte is found, return byte, else return `-1`.
 * */
unsigned char uart_getc(void)
{
    int c = -1;
    while(!(UCA1IFG & UCRXIFG));
    while(!UCA1RXBUF);
	// wait here for user input
	while (c == -1)
    	c = UCA1RXBUF;
    return c;
}


/**
 * uart_gets
 *
 * @desc: read an entire line/string into `buf`.
 *
 * @param: `buf` - the buffer to read the bytes into.
 * @param: `limit` - the limit of bytes to read into `buf`.
 *
 * @return: `buf` with the bytes stored in its memory space.
 * */
char *uart_gets(char *buf, int limit)
{
	unsigned char c;
	int i;

	i = 0;

	while (--limit) {
		c = uart_getc();
		if (c == '\r') {
			uart_putc('\n');
            uart_putc('\r');
			break;
		} else if (c == 0x7f) {
			uart_putc('\b');
            uart_putc(' ');
            uart_putc('\b');
			buf[--i] = 0;
			limit++;
		} else {
			uart_putc(c);
			buf[i++] = c;
		}
	}
	buf[i] = 0;
	return buf;
}


/**
 * uart_init
 *
 * @desc: quickly set up a UART connection on port 2 pins 5 and 6.
 **/
void uart_init(void)
{
    P2SEL1 |= BIT5 + BIT6;              //Activate Pin for UART use
    P2SEL0 &= ~BIT5 + ~BIT6;            //Activate Pin for UART use

    UCA1CTLW0 |= UCSSEL_2;              //Select clock SMCLK

    UCA1BRW = 0x6;                      //Set Baud rate 9600 : UCA1BRW = INT(F_CPU/BAUD_soll) =         INT(1MHz/9600) = 104 with oversampling: 6
    UCA1MCTLW |= UCBRS5 + UCOS16 + UCBRF3;     //Modulation according to datasheet table: UCBRS = 0x20 = b100000 and UCOS16 = 1 and UCBRF = 8 = 0x8 = b1000

    UCA1CTLW0 &= ~UCSWRST;				//Reset UART module
 }
