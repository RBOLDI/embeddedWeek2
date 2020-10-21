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
#define DELAY_STATEMENT		4
//Expression indexes:
#define LED1_STATE_EXPR		0
#define LED2_STATE_EXPR		1
#define LED3_STATE_EXPR		2
#define KNOP1_STATE_EXPR	3
#define KNOP2_STATE_EXPR	4
#define KNOP3_STATE_EXPR	5
#define KNOP4_STATE_EXPR	6
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
		bool executeDelay(char *tokens[MAX_NUM_TOKENS]);
		//while:
		bool executeWhile(char *tokens[], uint16_t lineNumber);
		bool checkWhileConditions(char *expression, char *relationOperator, char *desiredState, uint16_t lineNumber);
		void skipToLine(uint16_t lineNumber);
		bool executeLoop_flag = false;
	//Statements:
		uint16_t instructionIndex(char *input);
		void getStatements(void);
		char *statements[MAX_NUM_TOKENS];
		char setLed_stmnt[MAX_TOKEN_SIZE] = "setLed";
		char returnLed_stmnt[MAX_TOKEN_SIZE] = "returnLed";
		char returnKnop_stmnt[MAX_TOKEN_SIZE] = "returnKnop";
		char while_stmnt[MAX_TOKEN_SIZE] = "while{";
		char delay_stmnt[MAX_TOKEN_SIZE] = "delay";
	//Epressions:
		uint16_t expressionIndex(char *input);
		void getExpressions(void);
		char *expressions[MAX_NUM_TOKENS];
		char *expressionValues[MAX_NUM_TOKENS];
		char led1State_exp[MAX_TOKEN_SIZE] = "led1-state"; char led1State_value[MAX_TOKEN_SIZE] = "LOW";
		char led2State_exp[MAX_TOKEN_SIZE] = "led2-state"; char led2State_value[MAX_TOKEN_SIZE] = "LOW";
		char led3State_exp[MAX_TOKEN_SIZE] = "led3-state"; char led3State_value[MAX_TOKEN_SIZE] = "LOW";
		char knop1State_exp[MAX_TOKEN_SIZE] = "knop1-state"; char knop1State_value[MAX_TOKEN_SIZE] = "LOW";
		char knop2State_exp[MAX_TOKEN_SIZE] = "knop2-state"; char knop2State_value[MAX_TOKEN_SIZE] = "LOW";
		char knop3State_exp[MAX_TOKEN_SIZE] = "knop3-state"; char knop3State_value[MAX_TOKEN_SIZE] = "LOW";
		char knop4State_exp[MAX_TOKEN_SIZE] = "knop4-state"; char knop4State_value[MAX_TOKEN_SIZE] = "LOW";
};

#endif