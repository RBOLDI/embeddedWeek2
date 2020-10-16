#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "parser.hpp"

using namespace std;

PARSER parseObjct;

int main() {
	char str[MAX_TOKEN_SIZE];
	parseObjct.tokenizerInit();
	
    cout << "Give input:" << endl;
	cin.getline(str, MAX_TOKEN_SIZE);
	while(parseObjct.tokenizer(str)){
		cout << "Give input:" << endl;
		cin.getline(str, MAX_TOKEN_SIZE);
	}
	cout << "no input" << endl;
    return 0;
}