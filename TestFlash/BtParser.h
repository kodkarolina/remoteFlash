/*
 * BtParser.h
 *
 * Created: 01.11.2018 14:41:51
 *  Author: laptmp
 */ 


#ifndef BTPARSER_H_
#define BTPARSER_H_


	extern char btRawData[40];
	extern uint16_t data[]; // uint16_t
	void parse_STypeInput(char *input, uint16_t data[]);
#endif /* BTPARSER_H_ */