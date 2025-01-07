#ifndef UART_H
#define UART_H

void uart_init();
//void uart_putc(char c);
void console_putc(char c);
char uart_getc();
//void uart_puts(const char *str);
//void uart_puts(const char *s);
int console_gets(char *s, int len);
void console_puts(const char *s);
//void console_puts(char *s);

#endif
