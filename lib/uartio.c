 /**
 * UARTprintf.c - printf for the MSP430FR5994 to send to uart
 * the function sendByte() is what directs it to UART. Otherwise, it's
 * pretty much the same as the normal printf.

 *
 * Taylor Gamache, 2021-11-10
 *
 * about 98% of this code comes from here:
 * https://gist.github.com/nicholasjconn/2896369#file-printf-c
 * */

#include <msp430.h>
#include "stdarg.h"
#include "uartio.h"

void _putc(unsigned);
void _puts(char *);

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
		1, // +9
		};


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
			_putc(c);
		} while (!(d & 1));
	} else
		_putc('0');
}


static void puth(unsigned n) {
	static const char hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
			'9', 'A', 'B', 'C', 'D', 'E', 'F' };
	_putc(hex[n & 15]);
}


void uartprintf(char *format, ...)
{
	char c;
	int i;
	long n;

	va_list a;
	va_start(a, format);
	while(c = *format++) {
		if(c == '%') {
			switch(c = *format++) {
				case 's': // String
					_puts(va_arg(a, char*));
					break;
				case 'c':// Char
					_putc(va_arg(a, int));
				break;
				case 'i':// 16 bit Integer
				case 'u':// 16 bit Unsigned
					i = va_arg(a, int);
					if(c == 'i' && i < 0) i = -i, _putc('-');
					xtoa((unsigned)i, dv + 5);
				break;
				case 'l':// 32 bit Long
				case 'n':// 32 bit uNsigned loNg
					n = va_arg(a, long);
					if(c == 'l' && n < 0) n = -n, _putc('-');
					xtoa((unsigned long)n, dv);
				break;
				case 'x':// 16 bit heXadecimal
					i = va_arg(a, int);
					puth(i >> 12);
					puth(i >> 8);
					puth(i >> 4);
					puth(i);
				break;
				case 0: return;
				default: goto bad_fmt;
			}
		} else
			bad_fmt: _putc(c);
	}
	va_end(a);
}

/**
 * puts() is used by printf() to display or send a string.. This function
 *     determines where printf prints to. For this case it sends a string
 *     out over UART, another option could be to display the string on an
 *     LCD display.
 **/
void _puts(char *s) {
	char c;

	// Loops through each character in string 's'
	while (c = *s++) {
		sendByte(c);
	}
}
/**
 * puts() is used by printf() to display or send a character. This function
 *     determines where printf prints to. For this case it sends a character
 *     out over UART.
 **/
void _putc(unsigned b) {
	sendByte(b);
}

/**
 * Sends a single byte out through UART
 **/
void sendByte(unsigned char byte)
{
	// USCI_A0 TX buffer ready?
    while(!(UCA1IFG&UCTXIFG));
	UCA1TXBUF = byte;			// TX -> RXed character
}


/*****************************************************************
*
*   gets() fucntion --> buggy 
******************************************************************/


static unsigned char recvbyte(void)
{
    unsigned char c;
    while(!(UCA1IFG&UCTXIFG));
    while(!UCA1RXBUF);
    c = UCA1RXBUF;
    return c;
}


unsigned char *_gets(unsigned char *s, unsigned int len)
{
    unsigned int i = 0;
    unsigned char c;
    while ((c = recvbyte()) && i < len) {
        *s = c;
        s++;
        i++;
    }
    *s = '\0';
    return s;
}
