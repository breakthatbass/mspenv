#ifndef __UARTIO_H__
#define __UARTIO_H__


// for now, here we define NULL...not really related to UART, but it's useful
// for the string functions.
#define NULL (void *)0

void uartprintf(char *format, ...);
void _puts(char *s);
void _putc(unsigned b);
//void sendByte(unsigned char byte);
unsigned char *uartgets(char *s, unsigned int len);
int _getchar(void);
void uart_init(void);

#endif
