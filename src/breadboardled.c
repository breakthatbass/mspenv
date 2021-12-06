/**
 * breadboardled.c
 *
 * a simple program that connects the mcu to a breadboard and blinks an LED
 *
 * Taylor Gamache Dec-6-2021
 * */
#include <msp430fr5994.h>

#define BLINK_CYCLES 500000L

void main(void)
{
	// disable watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	// required for changing any pins
	PM5CTL0 &= ~LOCKLPM5;

	P3DIR |= BIT0;
	P3OUT |= BIT0;

	while (1) {
		P3OUT ^= BIT0;
		__delay_cycles(BLINK_CYCLES);
	}
}
