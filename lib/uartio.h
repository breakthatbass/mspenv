#ifndef __UARTIO_H__
#define __UARTIO_H__

void uartprintf(char *format, ...);
void _puts(char *s);
void _putc(unsigned b);
void sendByte(unsigned char byte);
unsigned char *_gets(unsigned char *s, unsigned int len);
int _getchar(void);
void uart_init(void);

#endif
