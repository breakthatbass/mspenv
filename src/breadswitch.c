/**
 * breadboardled.c
 *
 * a simple program that connects the mcu to a breadboard and lights
 * up and LED. If the button is down, instead, blink the LED.
 *
 * This requires setting up another port to read in data from a switch.
 * Like sending power to the LED, it doesn't really matter what port and
 * pin is used, just any that are currently unused and available on the board.
 *
 * Taylor Gamache Dec-6-2021
 * */
#include <msp430fr5994.h>

#define BLINK_CYCLES 50000L

void main(void)
{
	// disable watchdog timer
	WDTCTL = WDTPW | WDTHOLD;
	// required for changing any pins
	PM5CTL0 &= ~LOCKLPM5;

	// port 3 pin 0 to light up the LED
	P3DIR |= BIT0;
	P3OUT |= BIT0;

	// set port 6 pin 1 as input (button)
	P6DIR &= ~BIT1;

	// enable pull up and pull down
	P6REN |= BIT1;
	P6OUT &= ~BIT1;

	while (1) {

		if ((P6IN & BIT1)) {
			P3OUT ^= BIT0;
			__delay_cycles(BLINK_CYCLES);
		} else {
			P3OUT = BIT0;
		}
	}
}
