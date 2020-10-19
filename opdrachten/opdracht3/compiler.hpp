#ifndef _COMPILER_HPP_
#define _COMPILER_HPP_

#define HIGH 1
#define LOW 0

#define MAX_NUM_TOKENS	255
#define MAX_TOKEN_SIZE	255
#define NUM_OF_FIELDS	9

#define INVALID_INPUT		0
#define WHITESPACE			0
#define SET_LED_STATMNT		1
#define RETURN_LED_STATMNT	2
#define LED_STATE_EXPR		3
#define RETURN_KNOP_STATMT	4
#define KNOP_STATE_EXPR		5
#define STATEMENT			6
#define EXPRESSION			7
#define WHILE_STATEMENT		8

class COMPILER_CLASS {
	public:
		bool executeInstruction(uint8_t instruction, char *tokens[MAX_NUM_TOKENS]);
		bool ledState;
		uint8_t identifyInput(char *input);
		
	private:
};

#endif