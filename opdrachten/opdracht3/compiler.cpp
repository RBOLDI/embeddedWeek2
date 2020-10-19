#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <fstream>
#include "compiler.hpp"
#include "parser.hpp"
#include "runtime.hpp"

using namespace std;

PARSER 				parseObjct;
RUNTIME_CLASS 		runtimeObjct;

uint16_t lineNumber = 0;

uint8_t COMPILER_CLASS::identifyInput(char *input){
	if(!strcmp(input, "setLed"))
		return SET_LED_STATMNT;
	if(!strcmp(input, "returnLed"))
		return RETURN_LED_STATMNT;
	if(!strcmp(input, "returnKnop"))
		return RETURN_KNOP_STATMT;
	else return 0;
}

bool executeSetLed(char *tokens[MAX_NUM_TOKENS]){
	uint8_t led;
	int state;
	//determine led hardware
	if (!strcmp(tokens[1], "1"))
		led = LED1;
	else if (!strcmp(tokens[1], "2"))
		led = LED2;
	else if (!strcmp(tokens[1], "3"))
		led = LED3;
	else{
		cout<<"Undefined led...\n"<<endl;
		return false;
	}
	//determine desired state
	if (!strcmp(tokens[2], "HIGH"))
		state = HIGH;
	else if(!strcmp(tokens[2], "LOW"))
		state = LOW;
	else{
		cout<<"not a valid led-state...\n"<<endl;
		return false;
	}
	runtimeObjct.setLed(led, state);
	return true;
}

bool executeReturnLed(char *tokens[MAX_NUM_TOKENS]){
	uint8_t led;
	//determine led hardware
	if (!strcmp(tokens[1], "1"))
		led = LED1;
	else if (!strcmp(tokens[1], "2"))
		led = LED2;
	else if (!strcmp(tokens[1], "3"))
		led = LED3;
	else{
		cout<<"Undefined led...\n"<<endl;
		return false;
	}
	runtimeObjct.pollLed(led);
	return true;
}

bool executeReturnKnop(char *tokens[MAX_NUM_TOKENS]){
	uint8_t button;
	//determine knop hardware
	if (!strcmp(tokens[1], "1"))
		button = BUTTON1;
	else if (!strcmp(tokens[1], "2"))
		button = BUTTON2;
	else if (!strcmp(tokens[1], "3"))
		button = BUTTON3;
	else if (!strcmp(tokens[1], "4"))
		button = BUTTON4;
	else{
		cout<<"Undefined knop...\n"<<endl;
		return false;
	}
	runtimeObjct.pollButton(button);
	return true;
}

bool COMPILER_CLASS::executeInstruction(uint8_t instruction, char *tokens[MAX_NUM_TOKENS]){
	if(instruction == INVALID_INPUT){
		cout<<"No valid input...\n"<<endl;
		return false;
	}
	if(instruction == SET_LED_STATMNT){
		executeSetLed(tokens);
		return true;
	}
	if(instruction == RETURN_LED_STATMNT){
		executeReturnLed(tokens);
		return true;
	}
	if(instruction == RETURN_KNOP_STATMT){
		executeReturnKnop(tokens);
		return true;
	}
	return false;
}

COMPILER_CLASS compObjct;

int main() {
	ifstream file;
	file.open("program.txt");
	runtimeObjct.initBcm();
	char *tokens[MAX_NUM_TOKENS];
	char input[MAX_TOKEN_SIZE];
	//read program file
	file.getline(input, sizeof input);
	while(parseObjct.tokenizer(input, tokens)){
		compObjct.executeInstruction(compObjct.identifyInput(input), tokens);
		file.getline(input, sizeof input);
	}
	runtimeObjct.closeBcm();
}