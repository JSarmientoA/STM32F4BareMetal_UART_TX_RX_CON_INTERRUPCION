#include <stdint.h>
#include <stdio.h> // Para poder usar printf()
#include "stm32f4xx.h"
#include "uart.h"

#define GPIOAEN		(1U<<0)// Escribir un uno(1) en el bit cero(0).
#define PIN5		(1U<<5)// Escribir un uno(1) en el bit 5.
#define	LED_PIN		PIN5

char daTo;

static void usart_callback(void);
int main(void)
{

	/*Habilitación del reoj para el puerto GPIOA*/
	RCC->AHB1ENR  |= 	GPIOAEN;//|=, es asignación con OR binario

	/*Estableser el pin PA5 como salida*/
	GPIOA->MODER  |= 	(1U<<10);//Coloca el bit 10 a 1
	GPIOA->MODER  &=~ 	(1U<<11);// Coloca   el bit 11 a 0, donde &=~ es Asignación con AND binario con complemto de uno

	uart2_rx_tx_interrupcion_init();
	while(1)
	{

	}
}

static void usart_callback(void) {

	daTo = USART2->DR;

	if (daTo == '1') { //^= LED_PIN; dato == '1'  USART2->SR & SR_RXNE
		GPIOA->ODR |= LED_PIN;
		printf("Dato rcorrecto......\n\r");
		printf("led on......\n\r");
	} else {
		GPIOA->ODR &= ~LED_PIN;
		printf("Dato inrcorrecto......\n\r");
		printf("Intente de nuevo......\n\r");
	}
}

void USART2_IRQHandler(void){
	/*Chequee si el bit RXNE esta seteado*/
	if(USART2->SR & SR_RXNE){
		usart_callback();
		}
	}

