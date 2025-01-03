//led.c
#include "led.h"
#include "gpio.h"

void led_init() {
    gpio_init(); // Initialize PA0 for LED
}

void led_on() {
    gpio_set();
}

void led_off() {
    gpio_clear();
}

void led_pattern(){
	gpio_pattern();
}

void led_toggle(){
	gpio_toggle();
}

