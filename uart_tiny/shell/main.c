#include "cli.h"
#include "led.h"
#include "uart.h"

#define RCC_BASE 0x40021000

typedef struct {
    volatile unsigned int CR;
    volatile unsigned int CFGR;
} RCC_TypeDef;

#define RCC ((RCC_TypeDef *)RCC_BASE)

// Declare the function prototype for register_commands
void register_commands();

void SystemClock_Config() {
    RCC->CR |= (1 << 0);  // Enable HSI
    while (!(RCC->CR & (1 << 1))); // Wait until HSI is ready
    RCC->CFGR &= ~(3 << 0);  // Select HSI as the system clock
}

int main() {
    SystemClock_Config();
    uart_init();
    led_init();

    cli_init();              // Initialize CLI
    register_commands();     // Register all commands

    char buffer[CLI_INPUT_BUFFER_SIZE];

    console_puts("Welcome to Tiny CLI for LED Controller\n");
    console_puts("Type 'help' to see available commands\n");

       while (1) {
        console_gets(buffer, CLI_INPUT_BUFFER_SIZE);  // Get and process input from UART
        cli_process_input(buffer);  // Process the input
    }

    return 0;
}
