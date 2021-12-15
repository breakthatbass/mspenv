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


void _putc(unsigned);
void _puts(char *);
void sendByte(unsigned char byte);
char recvbyte(void);


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
			uartputc(c);
		} while (!(d & 1));
	} else
		uartputc('0');
}


// print a hex char
static void puth(unsigned n) {
	static const char hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
			'9', 'A', 'B', 'C', 'D', 'E', 'F' };
	uartputc(hex[n & 15]);
}

/****
 *
 * uartio API
 *
 ****/

/**
 * uartprintf
 *
 * @desc: printf but for the msp430 MCU to print to UART. Requires uart_init()`.
 * 
 * @todo: make int capability. for now, it requires unsigned.
 * */
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
					uartputs(va_arg(a, char*));
					break;
				case 'c':// Char
					uartputc(va_arg(a, int));
				break;
				case 'i':// 16 bit Integer
				case 'u':// 16 bit Unsigned
					i = va_arg(a, int);
					if (c == 'i' && i < 0) {
						i = -i;
						uartputc('-');
					}
					xtoa((unsigned)i, dv + 5);
				break;
				case 'l':// 32 bit Long
				case 'n':// 32 bit uNsigned loNg
					n = va_arg(a, long);
					if (c == 'l' && n < 0) {
						n = -n; 
						uartputc('-');
					}
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
			bad_fmt: uartputc(c);
	}
	va_end(a);
}


/**
 * uartputs
 *
 * @desc: print a string through UART
 *
 * @param: `s` - print each `char` in `s` to an open UART console.
 * */
void uartputs(char *s) {
	char c;

	while (c = *s++) {
		uartputc(c);
	}
}


/**
 * uartputc
 *
 * @desc: Send a single byte to the transmit buffer register.
 *
 * @param: `byte` - byte to send to transmit buffer register.
 * */
void uartputc(unsigned char byte)
{
	// USCI_A0 TX buffer ready?
    while(!(UCA1IFG & UCTXIFG));
	// write bite into transmit buffer register
	UCA1TXBUF = byte;
}


/**
 * uartgetc
 *
 * @desc: attempt to read a byte stored in the recieve buffer register.
 *
 * @return: if a byte is found, return byte, else return `-1`.
 * */
int uartgetc(void)
{
    int c = -1;
    while(!(UCA1IFG & UCRXIFG));
    while(!UCA1RXBUF);
    c = UCA1RXBUF;
    return c;
}


/**
 * uartgets
 *
 * @desc: read an entire line/string into `buf`.
 *
 * @param: `buf` - the buffer to read the bytes into.
 * @param: `limit` - the limit of bytes to read into `buf`.
 *
 * @return: `buf` with the bytes stored in its memory space.
 * */
char *uartgets(char *buf, int limit)
{
	int c, i;
	i = 0;
	while ((c = uartgetc()) && --limit) {
		if (c == '\r') break;
		uartputc(c);
		buf[i++] = c;
		if (c == '\n') buf[i++] = '\r';
	}
	buf[i] = '\0';
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
