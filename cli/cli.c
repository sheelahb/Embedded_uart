//cli.c
//#include <string.h>
#include "led.h"
#include "uart.h"

// Custom strcmp implementation (as described above)
int my_strcmp(const char *str1, const char *str2) {
	while (*str1 != '\0' && *str2 != '\0') {
		if (*str1 != *str2) {
			return *str1 - *str2;
		}
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

void cli_process(const char *command) {
	if (my_strcmp(command, "ledon") == 0) {
		led_on(); // No arguments required
		uart_puts("LED ON\n");
	} else if (my_strcmp(command, "ledoff") == 0) {
		led_off(); // No arguments required
		uart_puts("LED OFF\n");
	} else if (my_strcmp(command, "pa") == 0) {
		led_pattern(); // Trigger LED pattern
		uart_puts("LED Pattern Activated\n");
	}else if (my_strcmp(command, "t") == 0){
		led_toggle();
		uart_puts("LED Toggled\n");
	}
	else {
		uart_puts("Invalid Command\n");
	}
}
