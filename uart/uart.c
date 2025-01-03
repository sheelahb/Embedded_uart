//uart.c
#include "uart.h"

#define RCC_BASE 0x40021000
#define GPIOA_BASE 0x40010800
#define USART1_BASE 0x40013800

typedef struct {
	volatile unsigned int SR;
	volatile unsigned int DR;
	volatile unsigned int BRR;
	volatile unsigned int CR1;
	volatile unsigned int CR2;
	volatile unsigned int CR3;
	volatile unsigned int GTPR;
} USART_TypeDef;

typedef struct {
	volatile unsigned int CRL;
	volatile unsigned int CRH;
	volatile unsigned int IDR;
	volatile unsigned int ODR;
	volatile unsigned int BSRR;
	volatile unsigned int BRR;
	volatile unsigned int LCKR;
} GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)
#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + 0x18))
#define USART1 ((USART_TypeDef *)USART1_BASE)

void uart_init() {
	void SystemClock_Config(void);
	// Enable USART1 and GPIOA clocks
	RCC_APB2ENR |= (1 << 14) | (1 << 2);

	// Configure PA9 (TX) as alternate function push-pull
	GPIOA->CRH &= ~0xF0;    // Clear PA9 configuration
	GPIOA->CRH |= (0xB << 4); // Set PA9 to AF push-pull (TX)

	// Configure PA10 (RX) as input floating
	GPIOA->CRH &= ~0xF00;   // Clear PA10 configuration
	GPIOA->CRH |= (0x4 << 8); // Set PA10 to floating input (RX)

	// Configure USART1: 9600 baud, 8N1
	USART1->BRR = 8000000 / 9600; // Baud rate calculation for 8 MHz clock
	USART1->CR1 |= (1 << 13) | (1 << 3) | (1 << 2); // Enable USART, TX, and RX
}

void uart_putc(char c) {
	while (!(USART1->SR & (1 << 7))); // Wait for TXE
	USART1->DR = c;
}

char uart_getc() {
	while (!(USART1->SR & (1 << 5))); // Wait for RXNE
	return USART1->DR & 0xFF;
}

void uart_puts(const char *str) {
	while (*str) {
		uart_putc(*str++);
	}
}
