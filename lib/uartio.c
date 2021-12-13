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
 * _puts
 *
 * @desc: print a string through UART
 *
 * @param: `s` - print each `char` in `s` to an open UART console.
 * */
void _puts(char *s) {
	char c;

	while (c = *s++) {
		sendByte(c);
	}
}
/**
 * _putc
 *
 * @desc: send a `char` to an open UART console.
 *
 * @param: `b` - the `char` to print.
 * */
void _putc(unsigned b) {
	sendByte(b);
}


// aends a single byte out through UART
void sendByte(unsigned char byte)
{
	// USCI_A0 TX buffer ready?
    while(!(UCA1IFG&UCTXIFG));
	UCA1TXBUF = byte;			// TX -> RXed character
}



char recvbyte(void)
{
    char c;
    while(!(UCA1IFG&UCRXIFG));
    while(!UCA1RXBUF);
    c = UCA1RXBUF;
    return c;
}


/**
 * _getchar
 *
 * @desc: attempt to recheive a `char` from an open UART console.
 *
 * @return: the `char` recieved, else `-1`.
 * */
int _getchar(void)
{
	int c;
	c = -1;
		c = recvbyte();
	return c;	
}

/**
 * gets
 *
 * buggy
 * */
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

unsigned char *uartgets(char *s, unsigned int len)
{
	unsigned int i = 0;
	unsigned char c;

	while ((c = _getchar())) {
		if (c == -1) continue;

		s[i++] = c;
		if (c == '\r') break;
	}
	s[i] = '\0';
	return s;
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

    UCA1CTLW0 &= ~UCSWRST;  //Reset UART module
 }
