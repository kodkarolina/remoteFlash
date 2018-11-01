/*
 * UART.h
 *
 * Created: 10.10.2018 14:43:42
 *  Author: kodka
 */ 


#ifndef UART_H_
#define UART_H_

//#include "UART.c"

// definitions 
#define start_sign 0x28
#define stop_sign 0x29

#define start_cmd 1
#define stop_cmd 2
#define status_cmd 3
#define frame_length 10//??

//receiving data variables 
extern volatile bool FRAME_is_RDY; //Inform if frame is ready to reading
extern char buffer[]; //receiving buffer
extern char *toSend;

volatile bool reciving;
volatile bool new_message;

//sending data variables

extern char bufferToSend[];
extern volatile bool is_sending_end;
extern volatile bool ready_to_send;

void usart_init(void);
void send_message(char *buf_to_send);

#endif /* UART_H_ */