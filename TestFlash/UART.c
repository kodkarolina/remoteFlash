/*
 * UART.c
 *
 * Created: 10.10.2018 14:43:55
 *  Author: kodka
 */ 

#define F_CPU 1000000UL

//#include <stddef.h>
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <string.h>
#include "UART.h"

//receiving data variables 
volatile uint8_t recived_buffer_ind=0; //Number of received buffer sings 
volatile bool FRAME_is_RDY = false; //Inform if frame is ready to reading
char buffer[frame_length];
char *toSend = NULL;

volatile bool reciving = false;
volatile bool new_message = false;

//sending data variables
volatile uint8_t sended = 0;
char bufferToSend[40];// cant? get size defined in header
volatile bool is_sending_end = true;
volatile bool ready_to_send = false;

void usart_init(void)
{
	/*
	parameters definition of transmission with macro included in head file setbaud.h  
	choosing a bad rating generate warning "Baud rate achieved is higher than allowed"
	*/
	#define BAUD 9600        //transmission speed
	#include <util/setbaud.h> //link to head file	
	
	//set values calculated in macro
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	#if USE_2X
	UCSRA |=  (1<<U2X);
	#else
	UCSRA &= ~(1<<U2X);
	#endif
	
	
	/* 
	Setting up other USART parameters
	 WARINING !!!
	http://mikrokontrolery.blogspot.com/2011/04/avr-czyhajace-pulapki.html
	*/
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);  
	/*
	data bits	: 8
	stop bit:  1
	odd bits:  none
	switch on transmitter and receiver and receiver interruption 
	*/
	UCSRB = (1<<TXEN) | (1<<RXEN) | (1<<RXCIE);
}

//--------------------------------------------------------------


ISR(USART_RXC_vect)
{
	//interruption generate after bait receiving
	char received = UDR;
	
	if(reciving){
		new_message = false;
		if(received == stop_sign){
			FRAME_is_RDY = true;
		}
		else{
			buffer[recived_buffer_ind++]=received;
			FRAME_is_RDY = false;
		}
	}
	else{
		if(received == start_sign){
			buffer[recived_buffer_ind++] = received;
			reciving = true;
			new_message = true;
		}
			
	}
	
}


//--------------------------------------------------------------

ISR(USART_UDRE_vect){
	
	/* 
	interruption generated after sending buffer became empty,
	send all sings from table 
	*/
	if(sended<frame_length){
		sended++;
		UDR = *toSend++;
		
		}else{
		is_sending_end= true;
		sended=0;
		//achieved table end
		UCSRB &= ~(1<<UDRIE); //turn off empty buffer interruption
	}
}
//--------------------------------------------------

void send_message(char *buf_to_send){
	
	/*
	function starts sending first sing, rest is sended in interruption, 
	automatically called after sending each sign 
	*/
	
	while (!is_sending_end);
	toSend = buf_to_send;
	if (toSend != NULL)
	{
		//wait until buffer is empty
		while (!(UCSRA & (1<<UDRE)));
		is_sending_end = false;
		
		recived_buffer_ind = 0;
		/*
		if buffer is empty, sending is allowed, switch on empty buffer interruption
		what cause starting a transmission actual buffer content 
		*/
		UCSRB |= (1<<UDRIE);
	}
}
