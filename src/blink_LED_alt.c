/**
 * blink_LED_alt.c - blink both LEDs alternately.
 * if one is on, the other is off...and alternate
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

	// set both LEDs to output (pins 1.0 & 1.1)
	P1DIR |= 0x3;
	
	P1OUT |= BIT0;		// set LED 1 on to start
	P1OUT &= ~BIT1;		// set LED 2 off to start

	while (1) {
		__delay_cycles(BLINK_CYCLES);
		P1OUT ^= 0x3;
	}
}
