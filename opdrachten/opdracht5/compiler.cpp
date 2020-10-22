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
/*
	initializes all statement instructions known to the program
	to their own index in an array of pointers.
*/
void COMPILER_CLASS::getStatements(void){
	statements[SET_LED_STATMNT] 	= setLed_stmnt;
	statements[RETURN_LED_STATMNT] 	= returnLed_stmnt;
	statements[RETURN_KNOP_STATMNT] = returnKnop_stmnt;
	statements[WHILE_STATEMENT] 	= while_stmnt;
	statements[DELAY_STATEMENT]		= delay_stmnt;
}
/*
	initializes all expressions and their values known to the program
	to their own index in an array of pointers.
*/
void COMPILER_CLASS::getExpressions(void){
	expressions[LED1_STATE_EXPR] 	= led1State_exp;
	expressions[LED2_STATE_EXPR] 	= led2State_exp;
	expressions[LED3_STATE_EXPR] 	= led3State_exp;
	expressions[KNOP1_STATE_EXPR] 	= knop1State_exp;
	expressions[KNOP2_STATE_EXPR] 	= knop2State_exp;
	expressions[KNOP3_STATE_EXPR] 	= knop3State_exp;
	expressions[KNOP4_STATE_EXPR] 	= knop4State_exp;
	//Starting values:
	expressionValues[LED1_STATE_EXPR] 	= led1State_value;
	expressionValues[LED2_STATE_EXPR] 	= led2State_value;
	expressionValues[LED3_STATE_EXPR] 	= led3State_value;
	expressionValues[KNOP1_STATE_EXPR] 	= knop1State_value;
	expressionValues[KNOP2_STATE_EXPR] 	= knop2State_value;
	expressionValues[KNOP3_STATE_EXPR] 	= knop3State_value;
	expressionValues[KNOP4_STATE_EXPR] 	= knop4State_value;
}
/*
	Initializes all statement instructions and expression known to the program
*/
void COMPILER_CLASS::compilerInit(void){
	getStatements();
	getExpressions();
}
/*
	Loops through the array of pointers to statements and compares them to the program input.
	If there is a match, it returns the index of the place where the statement is stored
*/
uint16_t COMPILER_CLASS::instructionIndex(char *input){
	for(uint8_t i = 0; i < sizeof statements; i++){
		if(statements[i] == NULL)
			return INVALID_INPUT;
		if(!strcmp(input, statements[i]))
			return i;
	}
	return INVALID_INPUT;
}
/*
	Loops through the array of pointers to expressions and compares them to the program input.
	If there is a match, it returns the index of the place where the statement is stored
*/
uint16_t COMPILER_CLASS::expressionIndex(char *input){
	for(uint8_t i =0; i < MAX_NUM_TOKENS; i++){
		if(expressions[i] == NULL)
			return INVALID_INPUT;
		if(!strcmp(input, expressions[i]))
			return i;
	}
	return INVALID_INPUT;
}
/*
	Executes the setLed statement.
	BNF: <set-led-statement> ::= setLed <led-num> <led-state-exp>
	Example: setLed 1 HIGH
	this will turn on Led 1
*/
bool COMPILER_CLASS::executeSetLed(char *tokens[MAX_NUM_TOKENS]){
	uint8_t ledGPIO;
	uint8_t ledIndex;
	int state;
	//determine led hardware
	if (!strcmp(tokens[1], "1"))
		ledGPIO = LED1;
	else if (!strcmp(tokens[1], "2"))
		ledGPIO = LED2;
	else if (!strcmp(tokens[1], "3"))
		ledGPIO = LED3;
	else{
		cout<<"Undefined led...\n"<<endl;
		return false;
	}
	ledIndex = atoi(tokens[1]) - 1;
	//determine desired state
	if (!strcmp(tokens[2], "HIGH")){
		state = HIGH;
		strcpy(expressionValues[ledIndex], "HIGH");
	}
	else if(!strcmp(tokens[2], "LOW")){
		state = LOW;
		strcpy(expressionValues[ledIndex], "LOW");
	}
	else{
		cout<<"not a valid led-state...\n"<<endl;
		return false;
	}
	runtimeObjct.setLed(ledGPIO, state);
	return true;
}
/*
	Executes the returnLed statement.
	BNF: <return-led-statement> ::= returnLed <led-num>
	Example: returnLed 2
	Returns the state of led 2, HIGH if it's turned on, LOW if it's turned off.
*/
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
/*
	Executes the returnKnop statement.
	BNF: <return-knop-statement> ::= returnKnop <knop-num>
	Example: returnKnop 4
	Returns the state of knop 4, HIGH if it's pressed in, LOW if not.
*/
bool COMPILER_CLASS::executeReturnKnop(char *tokens[MAX_NUM_TOKENS]){
	uint8_t buttonGPIO;
	uint8_t buttonIndex;
	uint8_t state;
	//determine knop hardware
	if (!strcmp(tokens[1], "1"))
		buttonGPIO = BUTTON1;
	else if (!strcmp(tokens[1], "2"))
		buttonGPIO = BUTTON2;
	else if (!strcmp(tokens[1], "3"))
		buttonGPIO = BUTTON3;
	else if (!strcmp(tokens[1], "4"))
		buttonGPIO = BUTTON4;
	else{
		cout<<"Undefined knop...\n"<<endl;
		return false;
	}
	buttonIndex = atoi(tokens[1])+2;
	state = runtimeObjct.pollButton(buttonGPIO);
	if(state == HIGH)
		strcpy(expressionValues[buttonIndex], "HIGH");
	else
		strcpy(expressionValues[buttonIndex], "LOW");
	return true;
}
/*
	Executes the while statement. 
	BNF: 	<while-statement> ::= while{ <expression> <relation-operators> <desired-state> do
			<statement> 
			}
	first it checks if the conditions set for the loop are true. If they are it'll loop
	through the program till it sees the end of while character '}' then it checks if the conditions
	are still true, if they are it repeats the loop.
*/
bool COMPILER_CLASS::executeWhile(char *tokens[], uint16_t lineNumber){
	char input[MAX_TOKEN_SIZE];
	char while_expression[MAX_TOKEN_SIZE];
	char while_relationOperator[MAX_TOKEN_SIZE];
	char while_desiredState[MAX_TOKEN_SIZE];
	strcpy(while_expression, tokens[1]);
	strcpy(while_relationOperator, tokens[2]);
	strcpy(while_desiredState, tokens[3]);
	uint16_t lineNumber_cpy = lineNumber;
	
	if(checkWhileConditions(while_expression, while_relationOperator, while_desiredState, lineNumber))
		executeLoop_flag = true;
	
	while(executeLoop_flag == true){
		file.getline(input, sizeof input);
		lineNumber_cpy++;
		if(parseObjct.tokenizer(input, tokens)){
			if(!strcmp(tokens[0], "}")){
				if(!checkWhileConditions(while_expression, while_relationOperator, while_desiredState, lineNumber))
					executeLoop_flag = false;
				else{
					lineNumber_cpy = lineNumber;
					skipToLine(lineNumber);
				}
			}
			else
				executeInstruction(tokens, lineNumber_cpy);
		}
	}
	cout<<"End of while!"<<endl;
	skipToLine(lineNumber_cpy);
	return true;
}
/*
	Checks if the conditions set for the while loop are true. 
	BNF: 	<while-statement> ::= while{ <expression> <relation-operators> <desired-state> do
			<statement> 
			}
	First it finds out what statement it has to compare. then it finds out how to compare it through
	the relation operator. Then it compares the expression acording to the relation operator to the 
	desired state
*/
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
/*
	Executes delay statement
	BNF: <delay-statemnt> ::> delay <miliseconds>
	delays program with certain amount of miliseconds
*/
bool COMPILER_CLASS::executeDelay(char *tokens[]){
	uint16_t ms = atoi(tokens[1]);
	runtimeObjct.delayRPI(ms);
	return true;
}
/*
	Executes the input of the program.
	First it finds out which statement it has to execute. Then it checks if it has 
	the right amount of arguments en gives error messages if not.
*/
bool COMPILER_CLASS::executeInstruction(char *tokens[MAX_NUM_TOKENS],uint16_t lineNumber){
	uint16_t instruction = instructionIndex(tokens[0]);
	if(!strcmp(tokens[0], "}")){
		cout<<"Error... unexpected end of while function, check line: "<<(unsigned) lineNumber<<endl;
		return false;
	}
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
	if(instruction == DELAY_STATEMENT){
		if(tokens[1] == NULL){
			cout<<"Error...no time to delay, check line: "<<(unsigned) lineNumber<<endl;
			return false;
		}
		executeDelay(tokens);
		return true;
	}
	return false;
}

COMPILER_CLASS compObjct;

/*
	Goes to a line in the program
*/
void COMPILER_CLASS::skipToLine(uint16_t lineNumber){
	char input[MAX_TOKEN_SIZE];
	file.close();
	file.open("program.txt");
	for(uint16_t i = 0; i < lineNumber; i++)
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