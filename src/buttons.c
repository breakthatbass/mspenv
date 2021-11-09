/**
 * buttons.c - a simple program to make use of the two buttons
 *
 * left button turns on the left LED
 * right button turns on the right LED
 *
 * Taylor Gamache, 2021-11-09
 * */
#include <msp430fr5994.h>

#define BLINK_CYCLES 5000L

void main(void)
{
	// put the dog to sleep
	WDTCTL = WDTPW | WDTHOLD;
	// unlock ports
	PM5CTL0 &= ~LOCKLPM5;

	// set LED pins as output
	P1DIR |= BIT0;
	P1DIR |= BIT1;
	// light it up
	P1OUT |= BIT0;
	P1OUT |= BIT1;

	// button are in port 5 as pins 5 and 6
	// left button in pin 6, right 5
	// set bits 5 and 6 as input
	P5DIR &= ~BIT5;
	P5DIR &= ~BIT6;
	// enable pull-up/down resistor on pins 5.5 and 5.6
	P5REN |= BIT5;
	P5REN |= BIT6;
	// make them pull-ups
	P5OUT |= BIT5;
	P5OUT |= BIT6;

	while (1) {
		__delay_cycles(BLINK_CYCLES);
		// check if left button is pressed
		if (P5IN & BIT6) {
			// light up left LED
			P1OUT |= BIT0;
		
		} else if (P5IN & BIT5) {
			// light up right LED
			P1OUT |= BIT1;
		} else
		P1OUT |= 0x0;
		P1OUT |= 0x0;
	}
}
