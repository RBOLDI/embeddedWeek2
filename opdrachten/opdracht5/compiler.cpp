#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <fstream>
#include <limits>
#include "compiler.hpp"
#include "parser.hpp"
#include "runtime.hpp"

using namespace std;

PARSER 				parseObjct;
RUNTIME_CLASS 		runtimeObjct;

ifstream file;

void COMPILER_CLASS::getStatements(void){
	statements[SET_LED_STATMNT] 	= setLed_stmnt;
	statements[RETURN_LED_STATMNT] 	= returnLed_stmnt;
	statements[RETURN_KNOP_STATMNT] = returnKnop_stmnt;
	statements[WHILE_STATEMENT] 	= while_stmnt;
}

void COMPILER_CLASS::getExpressions(void){
	expressions[LED_STATE_EXPR] 	= ledState_exp;
	expressions[KNOP_STATE_EXPR] 	= knopState_exp;
	//Starting values:
	expressionValues[LED_STATE_EXPR] 	= ledState_value;
	expressionValues[KNOP_STATE_EXPR] 	= knopState_value;
}

void COMPILER_CLASS::compilerInit(void){
	getStatements();
	getExpressions();
}

uint16_t COMPILER_CLASS::instructionIndex(char *input){
	for(uint8_t i = 0; i < sizeof statements; i++){
		if(statements[i] == NULL)
			return INVALID_INPUT;
		if(!strcmp(input, statements[i]))
			return i;
	}
	return INVALID_INPUT;
}

uint16_t COMPILER_CLASS::expressionIndex(char *input){
	for(uint8_t i =0; i < MAX_NUM_TOKENS; i++){
		if(expressions[i] == NULL)
			return INVALID_INPUT;
		if(!strcmp(input, expressions[i]))
			return i;
	}
	return INVALID_INPUT;
}

bool COMPILER_CLASS::executeSetLed(char *tokens[MAX_NUM_TOKENS]){
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

bool COMPILER_CLASS::executeReturnLed(char *tokens[MAX_NUM_TOKENS]){
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

bool COMPILER_CLASS::executeReturnKnop(char *tokens[MAX_NUM_TOKENS]){
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

bool COMPILER_CLASS::executeWhile(char *tokens[], uint16_t lineNumber){
	//uint16_t lineNumber_cpy = lineNumber;
	checkWhileConditions(tokens[1], tokens[2], tokens[3], lineNumber);
	return false;
}

bool COMPILER_CLASS::checkWhileConditions(char *expression, char *relationOperator, char *desiredState, uint16_t lineNumber){
	uint16_t expIndex = expressionIndex(expression);
	if(!strcmp(relationOperator, "==")){
		if(!strcmp(expressionValues[expIndex], desiredState)){
			cout<<"Expression is the desired state! (==)"<<endl;
			return true;
		}
		else return false;
	}
	if(!strcmp(relationOperator, "!=")){
		if(strcmp(expressionValues[expIndex], desiredState)){
			cout<<"Expression is not the desired state! (!=)"<<endl;
			return true;
		}
		else return false;
	}
	//If expression should (not) be the same as desired state, just compare them as strings, else convert them to intergers for computing
	int currentState_int = atoi(expressionValues[expIndex]);
	int desiredState_int = atoi(desiredState);
	if(!strcmp(relationOperator, "<=")){
		if(currentState_int <= desiredState_int){
			cout<<"expression is smaller than or equal to desired state! (<=)"<<endl;
			return true;
		}
		else return false;
	}
	if(!strcmp(relationOperator, ">=")){
		if(currentState_int >= desiredState_int){
			cout<<"expression is bigger than or equal to desired state! (>=)"<<endl;
			return true;
		}
		else return false;
	}
	if(!strcmp(relationOperator, "<")){
		if(currentState_int < desiredState_int){
			cout<<"expression is smaller than desired state! (<)"<<endl;
			return true;
		}
		else return false;
	}
	if(!strcmp(relationOperator, ">")){
		if(currentState_int > desiredState_int){
			cout<<"expression is bigger than desired state! (>)"<<endl;
			return true;
		}
		else return false;
	}
	cout << "incorrect usage of while on line: " << (unsigned)lineNumber<< endl;
	return false;
}

bool COMPILER_CLASS::executeInstruction(char *tokens[MAX_NUM_TOKENS], uint16_t lineNumber){
	uint16_t instruction = instructionIndex(tokens[0]);
	if(instruction == INVALID_INPUT){
		cout<<"Error...No valid input, check line: "<<(unsigned) lineNumber<<endl;
		return false;
	}
	if(instruction == SET_LED_STATMNT){
		if(tokens[1] == NULL){
			cout<<"Error...Check line: "<<(unsigned) lineNumber<<endl;
			return false;
		}
		executeSetLed(tokens);
		return true;
	}
	if(instruction == RETURN_LED_STATMNT){
		if(tokens[1] == NULL){
			cout<<"Error...Check line: "<<(unsigned) lineNumber<<endl;
			return false;
		}
		executeReturnLed(tokens);
		return true;
	}
	if(instruction == RETURN_KNOP_STATMNT){
		if(tokens[1] == NULL){
			cout<<"Error...Check line: "<<(unsigned) lineNumber<<endl;
			return false;
		}
		executeReturnKnop(tokens);
		return true;
	}
	if(instruction == WHILE_STATEMENT){
		if(tokens[1] == NULL){
			cout<<"Error...Check line: "<<(unsigned) lineNumber<<endl;
			return false;
		}
		executeWhile(tokens, lineNumber);
		return true;
	}
	return false;
}

COMPILER_CLASS compObjct;



void skipToLine(char *input, uint16_t lineNumber){
	for(uint16_t i = 0; i <= lineNumber; i++)
		file.getline(input, sizeof input);
}

int main() {
	uint16_t lineNumber = 0;
	file.open("program.txt");
	runtimeObjct.initBcm();
	compObjct.compilerInit();
	char *tokens[MAX_NUM_TOKENS];
	char input[MAX_TOKEN_SIZE];
	//read program file
	file.getline(input, sizeof input);
	lineNumber++;
	while(parseObjct.tokenizer(input, tokens)){
		compObjct.executeInstruction(tokens, lineNumber);
		file.getline(input, sizeof input);
		lineNumber++;
	}
	runtimeObjct.closeBcm();
}