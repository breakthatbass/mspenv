/**
 * buttons.c - a simple program to make use of the two buttons
 *
 * left button turns on the left LED
 * right button turns on the right LED
 *
 * Taylor Gamache, 2021-11-09
 * */
#include <msp430fr5994.h>

void main(void)
{
	// put the dog to sleep
	WDTCTL = WDTPW | WDTHOLD;
	// unlock ports
	PM5CTL0 &= ~LOCKLPM5;

	//led 1
	P1DIR |= BIT0;
	P1OUT &= ~BIT0;

	// led 2
	P1DIR |= BIT1;
	P1OUT &= ~BIT1;

	// buttons are in port 5 as pins 5 and 6
	// left button in pin 6, right 5
	// set bits 5 and 6 as input
	P5DIR &= ~BIT6;
	P5DIR &= ~BIT5;
	// enable pull-up/down resistor on pins 5.5 and 5.6
	P5REN |= BIT6;
	P5REN |= BIT5;
	// make them pull-ups
	P5OUT |= BIT6;
	P5OUT |= BIT5;

	while (1) {
		// check if left button is pressed
		if ((P5IN & BIT6) == 0) {
			// light up left LED
			P1OUT |= BIT0;

		// check if right button is pressed
		} else if ((P5IN & BIT5) == 0) {
			// light up right LED
			P1OUT |= BIT1;
		} else {
			// turn both LEDS off
			P1OUT &= ~BIT0;
			P1OUT &= ~BIT1;
		}
	}
}
