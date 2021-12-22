#ifndef LCDLIB_H_
#define LCDLIB_H_

#include <msp430.h>
#include <stdio.h>

// Delay Functions
#define delay_ms(x)		__delay_cycles((long) x* 1000)
#define delay_us(x)		__delay_cycles((long) x)

#define EN		BIT4
#define RS		BIT5
#define DATA	0x0F
#define CLEAR	0x01


void lcd_init(void);									// Initialize LCD
void lcd_clear();								// Clear LCD
void lcdprint(char * text, int x, int y);		// Write string
void lcdSetInt(int val, int x, int y);			// Write integer
void lcdsetchar(unsigned char c);


void lcdgoto(int x);

#endif /* LCDLIB_H_ */
