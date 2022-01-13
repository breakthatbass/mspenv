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
#include "../lib/lcd.h"
#include "../lib/uartio.h"

/*
// backspace: move back one space, print ' ' to erase byte, then move back to that spot.
	void backspace(void)
	{
		lcd_goto(0x10);
		lcd_putc(' ');
		lcd_goto(0x10);
	}

*/
void main(void)
{
	// put the dog to sleep
	WDTCTL = WDTPW | WDTHOLD;
	// unlock ports
	PM5CTL0 &= ~LOCKLPM5;

	lcd_init(BLINK_ON);
	uart_init();

	lcd_clear();
	int c;
	int i = 0;
	while (1) {
		//i = 0;
		while ((c = uart_getc())) {
			if (i == 16) {
				do {
				
				
				//	lcd_goto(0x14);
					i++;
				} while (i < 25);
			}

			if (c == 0x7F) {
				if (i == 0) continue;
				//backspace();
				i--;
				continue;
			} else if (c == '\r') {
				//lcd_goto(0x14);
				i++;
				continue;
			}
			lcd_putc(c);
			i++;
		}
	}
}
