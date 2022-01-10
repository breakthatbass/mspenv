/***************************************************************************
 *
 * Author: Taylor Gamache
 * Email: gamache.taylor@gmail.com
 * url: https://github.com/breakthatbass/msp430_lcd_driver
 *
 * Version: 0.0.1
 * License: MIT 2021
 *
 * @name: msp430 LCD device driver
 * @description: a simple API to make use of an LCD with an msp430
 *
 *************************************************************************/
#include "lcd.h"

#define	LOWNIB(x) P3OUT = (P3OUT & 0xF0) + (x & 0x0F)

// flip a switch in the enable bus
static void lcd_trigger_EN(void)
{
	P3OUT |= EN;
	P3OUT &= ~EN;
}


// send a command to RS saying we're about to write data
static void lcd_cmd(unsigned char cmd)
{
	P3OUT &= ~RS;		// set RS to Data
	LOWNIB(cmd >> 4);	// upper nibble
	lcd_trigger_EN();
	LOWNIB(cmd);		// lower nibble
	lcd_trigger_EN();
	delay_ms(5);		// delay about 1.5ms
}


/**
 * lcd_init
 *
 * @desc: initialize LCD driver
 * 
 * @param: `blink_option` - set the cursor blinker on/off. `BLINK_ON` or `BLINK_OFF`.
 * */
void lcd_init(unsigned int blink_option)
{
	delay_ms(100);				// wait for about 100ms after power is applied.

	P3DIR = EN + RS + DATA;		// make pins outputs
	P3OUT = 0x03;				// start LCD (send 0x03)

	lcd_trigger_EN();			// send 0x03 3 times at 5ms then 100 us
	delay_ms(5);
	lcd_trigger_EN();
	delay_ms(5);
	lcd_trigger_EN();
	delay_ms(5);

	P3OUT = 0x02;				// switch to 4-bit mode
	lcd_trigger_EN();
	delay_ms(5);

	lcd_cmd(0x28);				// 4-bit, 2 line, 5x8
	lcd_cmd(0x08);				// instruction flow
	lcd_cmd(CLEAR);				// clear LCD
	lcd_cmd(0x06);				// auto-increment as each char is printed
	lcd_cmd(blink_option);		// set cursor blinking on or off
}


/**
 * lcd_clear();
 *
 * @desc: clear the LCD screen.
 * */
void lcd_clear(void)
{
	lcd_cmd(CLEAR);
}


/**
 * lcd_putc
 * 
 * @desc: print a single byte/char to the LCD screen
 * 
 * @param: `c` - the char to print.
 * */
void lcd_putc(unsigned char c)
{
	P3OUT |= RS;		// set RS to Data
	LOWNIB(c >> 4);		// upper nibble
	lcd_trigger_EN();
	LOWNIB(c);			// lower nibble
	lcd_trigger_EN();
	delay_us(50);		// delay about 47 us
}


/**
 * lcd_puts
 * 
 * @desc: print a string to an LCD and wrap text into the second line.
 * 
 * @param: `s` - the string to print.
 * */
void lcd_puts(char *s)
{
	cursor_p c;
	c.x = 0;
	c.y = 0;

	// start cursor location at the beginning
	int loc = 0;
	loc |= 0x80;
	lcd_cmd(loc);

	while (*s) {
		// if cursor is at last box of first line,
		// move cursor to first box of second line
		if (c.x == 16 && c.y == 0) {
			loc |= 0x40;
			lcd_cmd(loc);
			c.y = 1;
			c.x = 0;
		}
		// if cursor is at last box of second line, stop printing and quit 
		else if (c.x == 16 && c.y == 1) break;

		lcd_putc(*s);
		c.x++;
		s++;
	}
}


/****** helper functions for printf *******/

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
			lcd_putc(c);
		} while (!(d & 1));
	} else
		lcd_putc('0');
}


/**
 * lcd_printf: d, x, u, c, s, f, p
 *
 * @desc: printf function for the LCD
 *
 * */
void lcd_printf(char *fmt, ...)
{
	char *sval;	// for dealing with string values
	int nval;

	va_list ap;
	va_start(ap, fmt);

	char *p = fmt;

	while (*p) {
		if (*p != '%') {
			lcd_putc(*p);
			p++;
			continue;
		}
		switch (*++p) {
		// int
		case 'd':
			nval = va_arg(ap, int);
			xtoa((unsigned) nval, dv+5);
			break;
		// string
		case 's':
			sval = va_arg(ap, char *);
			while (*sval)
				lcd_putc(*sval++);
			break;
		case '%':
			lcd_putc('%');
			break;
		default:
			lcd_putc(*p);
			break;
		}
		p++;
	}
	va_end(ap);
}


/**
 * lcd_put_xy
 *
 * @desc: print a string to the LCD in a specific location.
 *
 * @param: `s` - the string to write.
 * @param: `x` - horizonal placement of cursor (0-15).
 * @param: `y` - vertical placement of cursor (0-1).
 * */
void lcd_print_xy(char *s, int x, int y)
{

	if (x < 16) {
		x |= 0x80; // set LCD for first line write
		switch (y){
		case 1:
			x |= 0x40; // set LCD for second line write
			break;
		case 2:
			x |= 0x60; // set LCD for first line write reverse
			break;
		case 3:
			x |= 0x20; // set LCD for second line write reverse
			break;
		}
	lcd_cmd(x);
	}

	while (*s) {
		lcd_putc(*s);
		s++;
	}
}
