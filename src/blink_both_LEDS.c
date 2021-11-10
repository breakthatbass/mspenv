/**
 * blink_both_LEDS.c - blink both LEDs
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

	// set LED 1 (pin 1.0) as output
	P1DIR |= BIT0;
	// set LED 1 off (low)
	P1OUT &= ~BIT0; 

	// set LED 2 (pin 1.1) as output
	P1DIR |= BIT1;
	// set LED 2 off (low)
	P1OUT &= ~BIT1;

	while (1) {
		__delay_cycles(BLINK_CYCLES);
		// if on, turn off, if off, tuen on
		P1OUT ^= BIT0;
		P1OUT ^= BIT1;
	}
}
