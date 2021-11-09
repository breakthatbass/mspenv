/**
 * ledson.c - a simple program to light up both LEDs
 * and do nothing
 * 
 * Taylor Gamache 2021-11-09
 * */
#include <msp430fr5994.h>

void main(void)
{
	// disable watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	
	// required for changing any pins
	PM5CTL0 &= ~LOCKLPM5;

	// the LEDs are in port 1
	// left LED is pin 0 (P1.0)
	// right LED is pin 1 (p1.1)
	// set port 1 pins 1 and 0 as output (just sets them as 1)
	P1DIR |= BIT0;		// pin 0 - left
	P1DIR |= BIT1;		// pin 1 - right
	// above could also have been done as
	// P1DIR |= 0x3  --> 0b00000011
	
	// clear the pins (make them low) makes them light up
	P1OUT |= BIT0;
	P1OUT |= BIT1;
	// like the above, this could have been done as
	// P1OUT |= 0x3; --> 0b00000011

	while (1) {
		// do nothing forever
	}
}
