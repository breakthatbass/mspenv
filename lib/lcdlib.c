#include "lcdlib.h"

#define	LOWNIB(x)	P3OUT = (P3OUT & 0xF0) + (x & 0x0F)

// flip a switch in the enable bus
static void lcd_trigger_EN(void) {
	P3OUT |= EN;
	P3OUT &= ~EN;
}


// write a single byte to the lcd
void lcdsetchar(unsigned char c) {
	P3OUT |= RS; // Set RS to Data
	LOWNIB(c >> 4); // Upper nibble
	lcd_trigger_EN();
	LOWNIB(c); // Lower nibble
	lcd_trigger_EN();
	delay_us(50); // Delay > 47 us
}


// send a command to RS saying we're about to write data
static void lcdwritecmd(unsigned char cmd) {
	P3OUT &= ~RS; // Set RS to Data
	LOWNIB(cmd >> 4); // Upper nibble
	lcd_trigger_EN();
	LOWNIB(cmd); // Lower nibble
	lcd_trigger_EN();
	delay_ms(5); // Delay > 1.5ms
}

void lcdgoto(int x)
{
	//lcdwritecmd(0x14); // move cursor one spot right
	//lcdwritecmd(0x10);  // move cursor one spot right
	lcdwritecmd(x);
}

/**
 * lcd_init
 *
 * @desc: initialize LCD driver
 * */
void lcd_init(void) {
	delay_ms(100);
	// Wait for 100ms after power is applied.

	P3DIR = EN + RS + DATA;  // Make pins outputs
	P3OUT = 0x03;  // Start LCD (send 0x03)

	lcd_trigger_EN(); // Send 0x03 3 times at 5ms then 100 us
	delay_ms(5);
	lcd_trigger_EN();
	delay_ms(5);
	lcd_trigger_EN();
	delay_ms(5);

	P3OUT = 0x02; // Switch to 4-bit mode
	lcd_trigger_EN();
	delay_ms(5);

	lcdwritecmd(0x28); // 4-bit, 2 line, 5x8
	lcdwritecmd(0x08); // Instruction Flow
	lcdwritecmd(0x01); // Clear LCD
	lcdwritecmd(0x06); // Auto-Increment
	//lcdwritecmd(0x0C); // Display On, No blink
	lcdwritecmd(0xD); // Display On, No blink
}


/**
 * lcdprint
 *
 * @desc: print a string to the LCD
 *
 * @param: `char *s` - the string to write.
 * @param: `int x` - horizonal placement of cursor (0-15).
 * @param: `int y` - vertical placement of cursor (0-1).
 * */
void lcdprint(char *s, int x, int y) {
	int i;
	
	if (x < 16) {
		x |= 0x80; // Set LCD for first line write
		switch (y){
		case 1:
			x |= 0x40; // Set LCD for second line write
			break;
		case 2:
			x |= 0x60; // Set LCD for first line write reverse
			break;
		case 3:
			x |= 0x20; // Set LCD for second line write reverse
			break;
		}
	lcdwritecmd(x);
	}
	i = 0;

	while (*s) {
		lcdsetchar(*s);
		s++;
	}
}


/**
 * lcdprint_int
 *
 * @desc: convert and int to a string and print it to the LCD.
 *
 * @param: `int val` - the number to print.
 * @param: `int x` - horizonal placement of cursor (0-15).
 * @param: `int y` - vertical placement of cursor (0-1).
 * */ 
void lcdprint_int(int val, int x, int y){
	char number_string[16] = {0};
	sprintf(number_string, "%d", val); // Convert the integer to character string
	lcdprint(number_string, x, y);
}


/**
 * lcd_clear();
 *
 * @desc: clear the LCD screen.
 * */
void lcd_clear(void) {
	lcdwritecmd(CLEAR);
}
