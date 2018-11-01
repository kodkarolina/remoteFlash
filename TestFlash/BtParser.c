#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dtmsplit(char *str, const char *delim, char ***array, uint16_t *length) {
	uint16_t i = 0;
	char *token;
	char **res = (char **)malloc(0 * sizeof(char *));
	
	token = strtok(str, delim);
	while (token != NULL)
	{
		res = (char **)realloc(res, (i + 1) * sizeof(char *));
		res[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	*array = res;
	*length = i;
}



char * getAllButFirstAndLast(char *input)
{
	uint16_t len = strlen(input);
	if (len > 0)
	input++;//Go past the first char
	if (len > 1)
	input[len - 2] = '\0';//Replace the last char with a null termination
	return input;
}


void parse_STypeInput(char *input, uint16_t data[7]){
	uint32_t preskalerData; 

	char **messageSplited = NULL;
	char **tmp = NULL;
	uint16_t count = 0;
	char *pMod = getAllButFirstAndLast(input);
	dtmsplit(pMod, "_", &messageSplited, &count);

	uint16_t overFlowCounter = 0;
	dtmsplit(messageSplited[0], ",", &tmp, &count);
	preskalerData = atol(tmp[0]);
	if (preskalerData > 65535){
		while (preskalerData > 65535){
			preskalerData = preskalerData - 65335;
			overFlowCounter++;
		}
	}
	data[0] = (uint16_t)preskalerData;
	data[1] = overFlowCounter;
	data[2] = atoi(tmp[1]);
	overFlowCounter = 0;
	dtmsplit(messageSplited[1], ",", &tmp, &count);
	preskalerData = atol(tmp[0]);
	if (preskalerData > 65535){
		while (preskalerData > 65535){
			preskalerData = preskalerData - 65335;
			overFlowCounter++;
		}
	}
	data[3] = (uint16_t)preskalerData;
	data[4] = overFlowCounter;
	data[5] = atoi(tmp[1]);
	data[6] = atoi(messageSplited[2]);


}
/*
uint16_t parse()
{
	char btRawData[40] = "s911164,1024_92768,1_30_o";
	uint16_t data[7]; // uint16_t
	parse_STypeInput(btRawData, data);
	uint16_t i;
	for (i = 0; i < 7; i++)
	printf("data #%d: %d\n", i, data[i]);

	return(0);
}
*/