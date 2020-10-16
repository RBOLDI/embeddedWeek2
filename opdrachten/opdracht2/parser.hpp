#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#define MAX_TOKEN_SIZE	255
#define MAX_NUM_TOKENS	255
#define WS_LIST_SIZE 6

class PARSER {
	public:
		void tokenizerInit(void);	
		bool tokenizer(char *input);	
		
	private:
		char *tokens[MAX_NUM_TOKENS];
		char whitespace[WS_LIST_SIZE];
};

#endif