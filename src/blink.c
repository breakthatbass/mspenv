/**
 * buttons.c - a simple program to make use of the two buttons
 *
 * left button turns on the left LED
 * right button turns on the right LED
 *
 * Taylor Gamache, 2021-11-09
 * */
#include <msp430fr5994.h>

#define BLINK_CYCLES 500000L

void main(void)
{
	// put the dog to sleep
	WDTCTL = WDTPW | WDTHOLD;
	// unlock ports
	PM5CTL0 &= ~LOCKLPM5;

	// set LED pins as output
	P1DIR |= BIT0;
	// light it up
	P1OUT &= ~BIT0;

	while (1) {
		__delay_cycles(BLINK_CYCLES);
		P1OUT ^= BIT0;
	}
}
