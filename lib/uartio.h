#ifndef __UARTIO_H__
#define __UARTIO_H__

// printf but for the msp430 and UART
void uartprintf(char *format, ...);

// push byte to transfer register 
void uart_putc(unsigned char byte);

// recieve byte frim recieve register
unsigned char uart_getc(void);

// print all bytes in a string to transfer register
void uart_puts(char *s);

// get string from user and push all bytes to recieve register
char *uart_gets(char *buf, int limit);

// set up port/pins for uart communication
void uart_init(void);

#endif
