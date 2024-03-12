

#ifndef UART_H_
#define UART_H_
#include <stdio.h> // Para poder usar printf()
#include "stm32f4xx.h"
void uart2_rx_tx_interrupcion_init(void);
void uart2_rx_tx_init(void);
char uart2_read(void);
#define SR_RXNE			(1U<<5)
#endif /* UART_H_ */
