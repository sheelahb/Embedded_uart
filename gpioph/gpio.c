//gpio.c
#include "gpio.h"

#define RCC_BASE 0x40021000
#define GPIOA_BASE 0x40010800

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

void delay(unsigned int value) {
	for (volatile unsigned int i = 0; i < value; i++);
}

void gpio_init() {
	RCC_APB2ENR |= (1 << 2); // Enable GPIOA clock

	GPIOA->CRL &= ~(0xFFFF); // Clear PA0 configuration
	GPIOA->CRL |= (0x3333);  // Set PA0 to general-purpose output, 50 MHz
}

void gpio_set() {
	GPIOA->ODR |= (1 << 0);
}

void gpio_clear() {
	GPIOA->ODR &= ~(1 << 0);
}

void gpio_toggle(){
	GPIOA->ODR ^= (1<<0);
}

unsigned int counter = 0;

void gpio_pattern(){

	GPIOA->ODR &= ~(0xF); // Clear all LEDs
			      //	for(int i=0; i<4; i++){
			      //icounter<4){
	while(1){
		GPIOA->ODR |= (1<<counter);
		delay(700000); // Add delay for visible pattern (adjust as needed)
		GPIOA->ODR &= ~(1<<counter);
		//delay(700000);
		//counter= counter+1;
		counter = (counter+1)%4;

	}
	//GPIOA->ODR &= ~(1<<counter);
	//counter = (counter+1) % 4;


	/*for(int i=0; i<3;i++)
	  {
	  GPIOA->ODR |= (1<<i);
	  delay(700000);
	  GPIOA->ODR &= ~(1<<i);
	  delay(700000);
	  }*/
}
