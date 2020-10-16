#ifndef _COMPILER_HPP_
#define _COMPILER_HPP_

#define HIGH 1
#define LOW 0

#define MAX_NUM_TOKENS	255
#define MAX_TOKEN_SIZE	255

//Statement indexes:
#define SET_LED_STATMNT		0
#define RETURN_LED_STATMNT	1
#define RETURN_KNOP_STATMNT	2
#define WHILE_STATEMENT		3
//Expression indexes:
#define LED_STATE_EXPR		0
#define KNOP_STATE_EXPR		1
//Invalid input index:
#define INVALID_INPUT		999


class COMPILER_CLASS {
	public:
		void compilerInit(void);
		bool executeInstruction(char *tokens[MAX_NUM_TOKENS], uint16_t lineNumber);
		bool ledState;
		
		
	private:
	//execute instruxtion function:
		bool executeReturnKnop(char *tokens[MAX_NUM_TOKENS]);
		bool executeReturnLed(char *tokens[MAX_NUM_TOKENS]);
		bool executeSetLed(char *tokens[MAX_NUM_TOKENS]);
		//while:
		bool executeWhile(char *tokens[], uint16_t lineNumber);
		bool checkWhileConditions(char *expression, char *relationOperator, char *desiredState, uint16_t lineNumber);
	//Statements:
		uint16_t instructionIndex(char *input);
		void getStatements(void);
		char *statements[MAX_NUM_TOKENS];
		char setLed_stmnt[MAX_TOKEN_SIZE] = "setLed";
		char returnLed_stmnt[MAX_TOKEN_SIZE] = "returnLed";
		char returnKnop_stmnt[MAX_TOKEN_SIZE] = "returnKnop";
		char while_stmnt[MAX_TOKEN_SIZE] = "while{";
	//Epressions:
		uint16_t expressionIndex(char *input);
		void getExpressions(void);
		char *expressions[MAX_NUM_TOKENS];
		char *expressionValues[MAX_NUM_TOKENS];
		char ledState_exp[MAX_TOKEN_SIZE] = "led-state"; char ledState_value[MAX_TOKEN_SIZE] = "LOW";
		char knopState_exp[MAX_TOKEN_SIZE] = "knop-state"; char knopState_value[MAX_TOKEN_SIZE] = "LOW";
};

#endif