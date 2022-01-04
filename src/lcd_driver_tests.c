/**
 * lcd_driver_tests.c - a program to test different driver functions
 * to interact with an LCD
 *
 * Taylor Gamache
 * Jan 4, 2022
 * */
#include <msp430fr5994.h>
#include "../lib/lcdlib.h"

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;
	PM5CTL0 &= ~LOCKLPM5;

	lcd_init();
	lcd_clear();

	// lcdprint()
	//
	// print 16 characters on first line, then continue on
	// second line to print 16 more. anything beyond doesn't get printed.
	// should look like this
	// _________________________________
	// |h|e|l|l|o|,| |m|y| |n|a|m|e| |i|
	// |s| |t|a|y|l|o|r|.| |w|h|a|t| |i|
	// 
	lcdprint("hello, my name is taylor. what is your name?");
	__delay_cycles(9000000);
	lcd_clear();

	unsigned char *s = "this is a really long string that will scroll";

	lcdprint_banner(s, 40);

	while (1) {}
}
