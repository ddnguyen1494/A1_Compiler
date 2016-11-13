//File name: main.cpp
//Author: Daniel Nguyen
//CWID: 891794570
//Written on 9/23/2016
//File descriptions: Main function that gets every line of input and passes it to Lexer's lex()
//and manually parser the "eof"

#include <string>
#include <vector>
#include <iostream>
#include "map_storing_token.h"
#include "lexer.h"

using namespace std;

int main() {
	string inputLine;
	int lineNum = 0;
	bool correct_syntax;
	Lexer A1_lexer;

	//Getting every line of input and passing to A1_lexer's lex function
	while (getline(cin, inputLine)) {
		lineNum++;
		correct_syntax = A1_lexer.lex(lineNum, inputLine);
		if (!correct_syntax) {
			return 1;
		}
		A1_lexer.get_parser()->set_tokenPosition(0);
	}

	//EOF encountered. Call Lexer::set_lexeme() and Lexer::output
	A1_lexer.get_parser()->parse("eof", 0, lineNum);
	cout << "----------Parse Successfully------------" << endl;

	A1_lexer.print_pst();
    
    cout << "----------Parse tree built successfully----------" << endl;
    cout << endl;
    A1_lexer.convert_print_ast();
	system("pause");
	return 0;

	
}

