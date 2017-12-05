/*
 * uart.h
 *
 *  Created on: Dec 30, 2016
 *      Author: rada
 */

#ifndef UART_H_
#define UART_H_

#include <stdbool.h>
#include <stdint.h>

#define USART_BAUDRATE 	(9600)
#define BAUD_PRESCALE 	(((( F_CPU / 16) + ( USART_BAUDRATE / 2) ) / ( USART_BAUDRATE ) ) - 1)
#define waitTxReady()	while (( UCSR0A & (1 << UDRE0 ) ) == 0)

extern volatile uint8_t wrIdx;
extern volatile uint8_t rdIdx;

#define uart_queueHasMsg()		(wrIdx != rdIdx)
#define uart_queueClear()		(rdIdx = wrIdx)
#define uart_printByte(data)	do{	waitTxReady();	UDR0 = data;}while(0)



void uart_print(uint8_t* data, uint8_t len);
bool uart_readMsg( uint8_t* data, uint8_t len);
void uart_init(void);
void uart_printStr(char* data);
void uart_printDec(uint16_t number);
void uart_printHex(uint16_t number);

#endif /* UART_H_ */
