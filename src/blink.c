/**
 * blink.c - a simple program to blink the left LED with about a 1 sec delay
 *
 * Taylor Gamache, 2021-11-10
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
	// start with it off
	P1OUT &= ~BIT0;

	while (1) {
		__delay_cycles(BLINK_CYCLES);
		// toggle
		P1OUT ^= BIT0;
	}
}
