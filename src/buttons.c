/**
 * buttons.c - a simple program to make use of the two buttons
 *
 * left button turns on the left LED
 * right button turns on the right LED
 *
 * Taylor Gamache, 2021-11-09
 * */
#include <msp430fr4559.h>

void main(void)
{
	// put the dog to sleep
	WDTCTL = WDTPW | WDTHOLD;
	// make pins changable
	PM5CTL0 &= ~LOCKLPM5;

	// set LED pins as output
	P1DIR |= 0x3;

	// button are in port 5 as pins 5 and 6
	// left button in pin 6, right 5
	// set bits 5 and 6 as input
	P5DIR &= ~0x30;
	// enable pull-up/down resistor on pins 5.5 and 5.6
	P5REN |= 0x30;
	// make them pull-ups
	P5OUT |= 0x30;

	while (1) {

		// check if left button is pressed
		if (P5IN & BIT6) {
			// light up left LED
			P1OUT = BIT0;
		} else if (P5IN & BIT5) {
			// light up right LED
			P1OUT = BIT1
		} else {
			P1OUT = 0x0;
		}

	}
}
