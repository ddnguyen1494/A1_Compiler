//File name:lexer.cpp
//Author: Daniel Nguyen
//Written on 10/22/2016
//Description: This file defines all the functions in Lexer class

#include <string>
#include<unordered_map>
#include<iostream>
#include "lexer.h"
#include "map_storing_token.h"

/****************************************************************************************
*								get_parser()											*
*	Returns the pointer poiting to the parser											*
*****************************************************************************************/
Parser * Lexer::get_parser() {
	return &A1_parser;
}
/******************************************************************************************
*									Lexer::set_lexeme									  *
*	This function receives as string as argument. It is used for the eof string.		  *
*******************************************************************************************/
void Lexer::set_lexeme(std::string lex) {
	lexeme = lex;
}

/********************************************************************************************************
*									Lexer::lex															*
*	This function gets first char and determine the token type. Then use switch statement to call the	*
*	corresponding get function. It then calls the ouput function.										*
*********************************************************************************************************/
bool Lexer::lex(int lineNum, std::string& inputLine){
	int index = 0;
	bool correct_syntax = true;
    for (; index < inputLine.length(); index++)
    {
        //Checking first char's type
        char first_char = inputLine[index];
		if (isspace(first_char))
			continue;
        else if (isalpha(first_char) || first_char == '_') {
            lexeme += first_char;
            lex_type = IDENT;
        }
        else if (isdigit(first_char))
        {
            lexeme += first_char;
            lex_type = INT;
        }
        else
        {
            lexeme += first_char;
            lex_type = OTHER;
        }
        //Switch statement to call approriate get function
        switch (lex_type) {
            case IDENT: get_identifier(++index, inputLine);
                break;
            case INT:  get_int(++index, inputLine);
                break;
            case OTHER:	get_operator(++index, inputLine);
                break;
            default:	break;
        }
        
        //Call ouput function
        if (!isspace(lexeme[0])&&(lexeme != ""))
        {
			look_up_token_id();
			correct_syntax = A1_parser.parse(lexeme, token_id, lineNum);
        }
		if (!correct_syntax) {
			output(lineNum);
			return false;
		}
		else
			lexeme = "";
    }
	return true;
}

/********************************************************************************************************
*                                   Lexer::look_up_token_id                                             *
*	This function uses the lexeme to look up token id. If lex_type is int, float or string, it sets     *
*	token id according to the enum Token. If lexeme is not found, check if lex_type is IDENT, else		*
*	set token_id to ERROR.																				*
*********************************************************************************************************/
void Lexer::look_up_token_id() {
	std::unordered_map<std::string, int>::const_iterator get_token = token_map.find(lexeme);
	if ((lex_type == INT) || (lex_type == FLOAT) || (lex_type == STRING))						//lexeme is one of 3 token types int, float, or string
	{
		token_id = static_cast<int>(lex_type);
	}
	else if (get_token == token_map.end()) {
		if (lex_type == IDENT)																	//Token is an identifier not found in map
			token_id = static_cast<int>(lex_type);

		else																					//Return the ID for error
			token_id = static_cast<int>(ERROR);
	}
	else																						//Found and return token's ID
	{
		token_id = get_token->second;
	}
}

/********************************************************************************************************
*                                      Lexer::get_identifier                                           *
*	This function receives the current index and the input line. It keeps reading characters until		*
*	it encounters an invalid char or the input line's last char.									    *
*********************************************************************************************************/
void Lexer::get_identifier(int &index, std::string & line)
{
	for (; !isspace(line[index]); index++)
	{
		if (isalnum(line[index]) || (line[index] == '_'))								//char is either a letter or an underscore
			lexeme += line[index];

		else {																			//char is invalid , stop getting char
			index--;
			return;
		}

		if (index + 1 == line.length())													//next ch is end of line, stop getting char
			return;
	}
}

/**********************************************************************************************************
*										Lexer::get_float												  *
*	This function receives the input line's index and the input line. First, it changes the token's type  *
*	to float. Then it reads every digit until it encounters a non-digit or the last char of input line.	  *											  *
**********************************************************************************************************/
void Lexer::get_float(int& index, std::string & line) {
	lex_type = FLOAT;
	for (; !isspace(line[index]); index++)
	{
		if (isdigit(line[index]))														//Char is a digit
			lexeme += line[index];

		else {																			//Invalid Char
			index--;
			return;
		}

		if (index + 1 == line.length())													//Encounters last char of line
			return;
	}
}

/***********************************************************************************************************
 *										Lexer::get_int													   *
 *	This function receives the input line and current index. It keeps adding digits to lexeme until it	   *
 *	encounters:																							   *
 *		1. Non-digit or last character of input line-> stop reading										   *
 *		2. Decimal point -> call get_char() function to get all decimal digits							   *
 ************************************************************************************************************/
void Lexer::get_int(int & index, std::string & line)
{
    for (; !isspace(line[index]); index++)
    {
        if (isdigit(line[index]))														//Char is digit
            lexeme += line[index];
        
        else if (line[index] == '.')													//Char is decimal point, call get_char()
        {
            lexeme += line[index];
            get_float(++index, line);
            return;
        }
        
        else {																			//Invalid char
            --index;
            return;
        }
        
        if (index + 1 == line.length())													//Last char of line
            return;
    }
}

/************************************************************************************************************
*										Lexer::get_operator													*
*	This function receives the current index and input line as arguments.									*
*	1.	If lexeme contains a quotation mark -> call get_string()											*
*	2.	Check if the index is at the end of line. If not, add the current char to lexeme					*														*
*		a. if lexeme is // -> ignores all character and set index to end of line							*
*		b. SPECIAL: if lexeme is +/- and next char is digit-> call get_int()								*
*		c. SPECIAL: if lexeme is . and next char is digit -> call get_float()							    *
*		d. add ch to lexeme then look up in map-> if found return else removing current ch and return	    *
*************************************************************************************************************/
void Lexer::get_operator(int & index, std::string &line) {
	if (lexeme == "\"")																	//Getting the string
	{
		lex_type = STRING;
		get_string(index, line);
		return;
	}

	if (index != line.length())															//Check to see if index is end of line
	{
		if (!isspace(line[index])) {														//Make sure char is not whitespace
			lexeme += line[index];
			look_up_token_id();
			if (lexeme == "//")															//Comments
			{
				lexeme = "";
				index = line.length();
				return;
			}

			else if (((line[index - 1] == '+' || line[index-1] == '-')) && (isdigit(line[index])))	// +/- followed by digits, call get_int()
			{
				lexeme = line[index - 1];
				get_int(index, line);
				lex_type = INT;
				return;
			}
			else if ((line[index - 1] == '.') && (isdigit(line[index])))							// . followed by digits, call get_float()
			{
				lexeme = line[index - 1];
				get_float(index, line);
				lex_type = FLOAT;
				return;
			}

			else if (token_id == static_cast<int>(ERROR))									//lexeme is not part of grammar
			{
				lexeme = line[index - 1];
				index--;
				return;
			}
			else																		//Lexeme is part of grammar
			{
				return;
			}
		}
		else
			return;
	}
}

/************************************************************************************************************
*										Lexer::get_string													*
*	This function receive the current index and input line as arguments. It keeps reading the			    *
*	string until the second quotation mark is encountered													*
************************************************************************************************************/
void Lexer::get_string(int & index, std::string &line) {
	for (; line[index] != '"'; ++index) {
		lexeme += line[index];
	}
	lexeme += line[index];
}

/********************************************************************************************************
*											Lexer::output(int)                                          *
*	This function receives the lineNum and prints out line number and the error	token.					*
********************************************************************************************************/
void Lexer::output(int lineNum) {
	std::cout << "Line " << lineNum << " : Unexpected symbol: " << lexeme << std::endl;
}

/********************************************************************************************************
*											Lexer::print_pst()                                          *
*	This function prints the parse tree.                                             					*
********************************************************************************************************/
void Lexer::print_pst() {
	A1_parser.print_pst();
}