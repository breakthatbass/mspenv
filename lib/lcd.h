#ifndef LCD_H_
#define LCD_H_

#include <msp430fr5994.h>
#include <stdarg.h>

#define delay_ms(x) __delay_cycles((long) x * 1000)
#define delay_us(x) __delay_cycles((long) x)

#define EN		BIT4
#define RS		BIT5
#define DATA	0x0F
#define CLEAR	0x01

// constants to use to turn blinking cursor on or off in lcd_init()
#define BLINK_ON 0xD
#define BLINK_OFF 0x0C

// keep track of cursor position to overflow to the next line
typedef struct cursor_position {
    int x;
    int y;
} cursor_p;

// API
void lcd_init(unsigned int blink_option);        // init
void lcd_clear(void);                            // clear the screen
void lcd_putc(unsigned char c);                  // print a char to LCD at current cursor position
void lcd_puts(char *s);                          // print a string to LCD at current cursor position
void lcd_printf(int x, int y, char *fmt, ...);   // printf for LCD. conversions: x, c, d, s
void lcd_putc_xy(int x, int y, unsigned char c); // print a char to LCV at specific cursor position
void lcd_puts_xy(int x, int y, char *s);         // print a string to LCD at specfifc cursor position
void lcd_goto(int x, int y);                     // move cursor to a specfic position

#endif
