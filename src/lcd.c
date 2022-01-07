/**
 * lcd.c - a simple program to make use of the lcd library and print "hello, world"
 *
 * Taylor Gamache
 * Dec 22, 2021
 * */
#include <msp430fr5994.h>
#include "../lib/lcd.h"


void main(void)
{
	// put the dog to sleep
	WDTCTL = WDTPW | WDTHOLD;
	// unlock ports
	PM5CTL0 &= ~LOCKLPM5;

	lcd_init(BLINK_OFF);

	lcd_print_xy("hello world!", 0, 0);
	__bis_SR_register(LPM0_bits);   // Enter Low Power Mode 0 without interrupts
}
