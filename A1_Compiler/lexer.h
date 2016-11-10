//File name: lexer.h
//Author: Daniel Nguyen
//Written on 10/22/2016
//Description: This header file contains the declaration of Lexer class

#ifndef LEXER_H
#define LEXER_H
#pragma once

#include "parser.h"

//Forward declaration of parser Class
class Parser;

class Lexer{
private:
    enum Token { IDENT = 2, INT = 3, FLOAT = 4, STRING = 5, OTHER, SPACE, ERROR = 99 };
    Token lex_type;
    std::string lexeme;
	int token_id;
	Parser A1_parser;
public:
	Parser * get_parser();
	void set_lexeme(std::string);
    bool lex(int, std::string&);
    void look_up_token_id();
    void get_identifier(int& , std::string &);
    void get_float(int&, std::string &);
    void get_int (int &, std::string &);
    void get_operator(int &, std::string &);
    void get_string(int &, std::string&);
	void output(int);

	// Addition by Sae Hun Kim
	void print_pst();
};

#endif