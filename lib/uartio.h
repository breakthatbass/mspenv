#ifndef __UARTIO_H__
#define __UARTIO_H__

#include <msp430.h>
#include "stdarg.h"

void uart_init(void);                   // set up pins for uart connection

void uart_printf(char *format, ...);    // printf but for the msp430

void uart_putc(unsigned char byte);     // send a byte through TX register

unsigned char uart_getc(void);          // receive a byte from RX register

void uart_puts(char *s);                // send all bytes in a string through TX

char *uart_gets(char *buf, int limit);  // receive all bytes from a user through RX

#endif