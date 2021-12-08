#include <msp430fr5994.h>
#include "../lib/lcdlib.h"

/*
void lcd_init(void)
{
	__delay_cycles(10000);
	// lcd is connect to port 3 pins 0 - 5
	// make pins outputs
	P3DIR |= 0x1f;
	P2OUT |= 0x03;
	
}
*/
void main(void)
{
	// put the dog to sleep
	WDTCTL = WDTPW | WDTHOLD;
	// unlock ports
	PM5CTL0 &= ~LOCKLPM5;

	lcdInit();
	lcdSetText("Go ", 0, 0);

	lcdSetText("Miners! ", 0,1);

//	__bis_SR_register(LPM0_bits);   // Enter Low Power Mode 0 without interrupts
	while(1);
}
