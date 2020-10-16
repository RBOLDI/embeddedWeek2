#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "parser.hpp"
#include "compiler.hpp"

using namespace std;

bool PARSER::tokenizer(char *input, char *tokens[]) {
	for(uint8_t index = 0; index < MAX_NUM_TOKENS; index++){
		tokens[index] = NULL;
	}
	int i = 0;
	if(*input == '\0' || *input == '\r' || *input == ' ' || *input == '\n')
		return false;
	tokens[i] = strtok(input, " ");
	while(tokens[i] != NULL){
		tokens[++i] = strtok(NULL, " ");
	}
	uint8_t j = 0;
	for(uint8_t index = 0; index < MAX_NUM_TOKENS; index++){
		if(tokens[index] != NULL){
			while(tokens[index][j] != '\0' && tokens[index][j] != '\r' && tokens[index][j] != '\n')
				j++;
			tokens[index][j] = '\0';
			j=0;
		}
	}
	return true;
}
