/*
 * uart.c
 *
 *  Created on: Dec 30, 2016
 *      Author: rada
 */

#include "uart.h"
#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>

#define RX_SIZE 		(16)
#define IDX_MASK		(RX_SIZE - 1)

uint8_t rxQueue[RX_SIZE];
volatile uint8_t wrIdx, rdIdx;

#define getRxCount()		((wrIdx - rdIdx) & IDX_MASK)
#define queueIsNotFull()	(getRxCount() < RX_SIZE)


ISR(USART_RX_vect) {
	uint8_t temp = UDR0;

	if(queueIsNotFull()){
		rxQueue[wrIdx & IDX_MASK] = temp;
		wrIdx++;
	}
}

void uart_init(void){
	DDRD |= (1 << PD1);
	UBRR0L = (unsigned char)BAUD_PRESCALE;
	UBRR0H = (BAUD_PRESCALE >> 8);
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   /* 8 data bits, 1 stop bit */
}


void uart_print(uint8_t* data, uint8_t len)
{
	uint8_t i = 0;

	if(len > 32){
		len = 32;
	}

	while(i < len){
		uart_printByte(data[i]);
		i++;
	}
}

void uart_printStr(char* data)
{
	uint8_t i = 0;
	char c = 1;

	while((i < 0xff) && (c != 0)){
		c = (uint8_t)data[i];
		uart_printByte(c);
		i++;
	}
}



bool uart_readMsg( uint8_t* data, uint8_t len)
{
	uint8_t i = 0;
	volatile uint16_t timeout = 500;

	while(getRxCount() < len){
		_delay_ms(1);
		timeout--;
		if(timeout == 0){
			/* communication failed */
			return false;
		}
	}

	for(i = 0; i < len; i++){
		data[i] = rxQueue[rdIdx & IDX_MASK];
		rdIdx++;
	}

	return true;
}

void uart_printDec(uint16_t number){
	uint16_t value = number;
	char snum[6] = {0};
	uint8_t i = 0;
	uint8_t digit;
	uint16_t divider = 10000;

	if(number == 0){
		snum[0] = '0';
	}else{
		while(divider > 0){
			digit = value / divider;
			if((i > 0) || (digit > 0)){
				snum[i] = digit + '0';
				i++;
			}
			value = value % divider;
			divider = divider / 10;
		}
	}

	uart_printStr(snum);

}

void uart_printHex(uint16_t number){
	uint16_t value = number;
	char snum[5] = {'0', '0', '0', '0', 0};
	uint8_t digit;
	uint8_t i;

	for(i=0; i<4; i++){
		digit = (value >> (i * 4)) & 0xf;

		if(digit < 10){
			snum[3 - i] = '0' + digit;
		}else{
			snum[3 - i] = 'A' + digit - 10;
		}
	}

	uart_printStr(snum);
}
