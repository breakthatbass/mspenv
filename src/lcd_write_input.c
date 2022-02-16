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


// backspace: move back one space, print ' ' to erase byte, then move back to that spot.
void backspace(int x, int y)
{
	lcd_goto(x-1, y);
	lcd_putc(' ');
	lcd_goto(x-1, y);
}


void main(void)
{
	// put the dog to sleep
	WDTCTL = WDTPW | WDTHOLD;
	// unlock ports
	PM5CTL0 &= ~LOCKLPM5;

	lcd_init(BLINK_ON);
	uart_init();

	lcd_clear();
	unsigned int c, x, y;

	x = 0;
	y = 0;

	while ((c = uart_getc())) {
		if (c == 0x7f) {
			if (x == 0 && y == 1) {
				x = 15;
				y = 0;
				lcd_goto(x, y);
				continue;
			} else if (x == 0 && y != 1) {
				continue;
			}
			backspace(x, y);
			x--;
			continue;
		}
		else if (c == '\r') {
			if (y == 1) continue;
			y = 1;
			x = 0;
			lcd_goto(x, y);
			continue;
		} else {
			lcd_putc(c);
			x++;
		}
	}

	while (1);
}
