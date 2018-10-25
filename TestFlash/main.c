/*
 * TestFlash.c
 *
 * Created: 08.10.2018 19:20:57
 * Author : kodka
 */ 

#define F_CPU 4000000UL

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <string.h>
#include "UART.h"

void led_init(void){
	DDRC |= (1<<PORTC3);
	PORTC &= ~(1<<PORTC3);
}

void led_on(void){
	PORTC |= (1<<PORTC3);
}
//--------------------------------------------------------------

void led_off(void){
	PORTC &= ~(1<<PORTC3);
}
//--------------------------------------------------------------

int main(void)
{
	led_init();
	usart_init(); //initiate USART module (RS-232)
	sei();        //switch on global interruption
	
	
	while(1){
		
		if (FRAME_is_RDY){
			led_on();
			send_message(*buffer);
			FRAME_is_RDY = false;
			}
			
			else{
			led_off();
			
			
		}
			
	}
}
