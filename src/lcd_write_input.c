/**
 * lcd_write_input.c
 *
 * read from UART stdin using the uartio lib from this repo
 * print each char to the LCD. Using backpace will move the cursor
 * back one space and delete the char in that position.
 *
 * Taylor Gamache
 * Dec 22, 2021
 * */
#include <msp430.h>
#include "../lib/lcdlib.h"
#include "../lib/uartio.h"


void main(void)
{
	// put the dog to sleep
	WDTCTL = WDTPW | WDTHOLD;
	// unlock ports
	PM5CTL0 &= ~LOCKLPM5;

	lcd_init();
	uart_init();

	void backspace(void)
	{
		lcdgoto(0x10);
		lcdsetchar(' ');
		lcdgoto(0x10);
	}

	lcd_clear();
	int c;
	while (1) {
		i = 0;
		while ((c = uartgetc())) {
			if (c == 0x7F) {
				backspace();
				continue;
			}
			lcdsetchar(c);
		}
	}
}
