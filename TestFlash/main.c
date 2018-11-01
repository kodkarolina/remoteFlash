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
#include "BtParser.h"

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
	
	uint16_t timerSettings[7];//0-counter settings for photo 1-timer overflow counter 2-prescaler settings__3,4,5-same but for delay__6- amount of photos.
	
	while(1){
		if (FRAME_is_RDY){
			led_on();
			if(buffer[0]==0x73)
			parse_STypeInput(buffer,timerSettings);//buffer present?
			send_message(buffer);// buffer will be corrupted after parsing
			FRAME_is_RDY = false;
			}
			
			else{
			led_off();
			
			
		}
			
	}
}
