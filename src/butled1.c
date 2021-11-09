/**
 * butled1.c	-	press button to light LED
 * single loop with 'if'
 * LED1 active low on P2.3
 * button B1 active low on P2.1
 * from page 82-83 in msp430 microntroller basics
 * Taylor Gamache 2021-11-09
 * */

#include "../../../ti/msp430-gcc/include/msp430fr5994.h"

// pins for LED and button on port 2
#define LED1	BIT3
#define B1		BIT1

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P2OUT |= LED1;					// preload LED1 off (active low)
	P2DIR = LED1;					// set pin with LED1 to output
	for (;;) {
		// is button down? (active low)
		if ((P2IN & B1) == 0) {
			P2OUT &= ~LED1;
		} else {
			// no? turn LED off
			P2OUT |= LED1;
		}
	}
}
