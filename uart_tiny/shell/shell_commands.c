#include "cli.h"
#include "led.h"
#include "uart.h"

int cmd_led_on(int argc, char *argv[]) {
     (void)argc;
     (void)argv;
    led_on();
    console_puts("LED is ON\n");
    return 0;
}

int cmd_led_off(int argc, char *argv[]) {
	  (void)argc;
	  (void)argv;
    led_off();
    console_puts("LED is OFF\n");
    return 0;
}

int cmd_led_toggle(int argc, char *argv[]) {
	 (void)argc;
	  (void)argv;
    led_toggle();
    console_puts("LED toggled\n");
    return 0;
}

int cmd_led_pattern(int argc, char *argv[]) {
	 (void)argc;
	  (void)argv;
    led_pattern();
    console_puts("LED pattern activated\n");
    return 0;
}

int cmd_help(int argc, char *argv[]) {
	  (void)argc;
	  (void)argv;
    cli_list_commands();
    return 0;
}

// Register commands
void register_commands() {
	//cli_register_command("ledpattern", "Activate an LED pattern", cmd_led_pattern);
    cli_register_command("ledon", "Turn the LED on", cmd_led_on);
    cli_register_command("ledoff", "Turn the LED off", cmd_led_off);
    cli_register_command("ledtoggle", "Toggle the LED state", cmd_led_toggle);
    //cli_register_command("ledpattern", "Activate an LED pattern", cmd_led_pattern);
    cli_register_command("help", "List all commands", cmd_help);
}
