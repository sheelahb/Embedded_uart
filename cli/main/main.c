//main.c
#include "uart.h"
#include "led.h"
#include "cli.h"

#define RCC_BASE 0x40021000

typedef struct {
	volatile unsigned int CR;
	volatile unsigned int CFGR;
} RCC_TypeDef;

#define RCC ((RCC_TypeDef *)RCC_BASE)

void SystemClock_Config() {
	RCC->CR |= (1 << 0);  // Enable HSI
	while (!(RCC->CR & (1 << 1))); // Wait until HSI is ready
	RCC->CFGR &= ~(3 << 0);  // Select HSI as the system clock
}

int main() {
	SystemClock_Config();
	uart_init();
	led_init();

	char buffer[100];
	unsigned int idx = 0;

	uart_puts("Welcome to LED Controller CLI\n");

	while (1) {
		char c = uart_getc();

		if (c == '\r' || c == '\n') {
			buffer[idx] = '\0'; // Null-terminate the string
			cli_process(buffer); // Process command
			idx = 0; // Reset buffer index
		} else {
			buffer[idx++] = c; // Append character to buffer
			if (idx >= sizeof(buffer)) idx = 0; // Prevent overflow
		}
	}

	return 0;
}
