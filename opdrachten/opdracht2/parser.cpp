#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "parser.hpp"

using namespace std;

void PARSER::tokenizerInit(void){
	whitespace[0] = 0x20;
	whitespace[1] = 0x0C;
	whitespace[2] = 0x0A; 
	whitespace[3] = 0x0D;
	whitespace[4] = 0x09; 
	whitespace[5] = 0x0B;
}

bool PARSER::tokenizer(char *input) {
	for(uint8_t index = 0; index < MAX_NUM_TOKENS; index++){
		tokens[index] = NULL;
	}
	int i = 0;
	if(*input == '\0' || *input == '\r' || *input == ' ')
		return false;
	
	tokens[i] = strtok(input, " ");
	
	while(tokens[i] != NULL){
		tokens[++i] = strtok(NULL, " ");
	}
	
	for(uint8_t index = 0; index < MAX_NUM_TOKENS; index++){
		if(tokens[index] != NULL)
			cout << "token " << unsigned(index) << ": " << tokens[index] << endl;
	}
	return true;
}
