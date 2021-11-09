/**
 * ledson.c - a simple program to light LEDs
 * Sets pins to output, lights pattern of LEDs, then loops forever
 * from page 71
 * */

#include "../../../ti/msp430-gcc/include/msp430fr5994.h"

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// disable watchdog timer
	P2DIR = 0x18;	// set pins with LEDs to output
	P2OUT = 0x08;	// LED 2 on, LED1 off

	while (1) {
		P2OUT ^= 0x08;	// LED 2 on, LED1 off
	}
}
