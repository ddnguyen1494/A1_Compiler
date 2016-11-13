//File name: parser.cpp
//Author: Daniel Nguyen
//Written on 10/23/2016
//Description: This file defines all parser class's functions
//Modified by Sae Hun Kim and Anthony Nguyen

#include <iostream>
#include <iomanip>
#include "parser.h"
#include "parser-matrix.h"
#include "map_storing_token.h"
#include "map_storing_abbreviation.h"

// Additions by Sae Hun Kim and Anthony Nguyen
#include "Node.h"
#include "pst.h"

/****************************************************************************
*						Parser()											*
*	Constructor which pushes eof and Pgm Non-Terminal onto the stack		*
*	              Modified by Sae Hun for refractoring		                *
*****************************************************************************/
Parser::Parser() {
	//add token_position because his output wants token position in line
	token_position = 0;
	// Push eof unto stack
	// PST does not require an eof so it needs no uplink
	stack.push_back(new Node("eof", nullptr, 0, -1, -1, -1));

	// Push Pgm unto stack
	Node * root = new Node("Pgm", pst.get_root(), 0, 1, -1, -1);
	stack.push_back(root);

	// Set PST's fixed header node's only child as Pgm
	pst.set_root(root);
}

/****************************************************************************
*					output_token_an_stack_contents(int)						*
*	Ouput stack contents using abbreviations and the token's information	*
*	next to it.																*
*****************************************************************************/
void Parser::output_token_and_stack_contents(int lineNum) {
	for (int i = 0; i < stack.size(); i++)
		std::cout << getAbbreviation(stack[i]->get_symbol()) ; // get abbreviation from symbol from pst node
	std::cout << "\t\t(Tok: id= " << std::setw(3) << std::left << front_id 
		<< "line= " << std::setw(3)<< std::left << lineNum 
		<< "str= \"" << front << "\"";

	if (front_id == 2)
		std::cout << " int= " << front << ")";

	else if (front_id == 4)
		std::cout << " float= " << front << ")";

	else
		std::cout << std::setw(10) << std::left << ")";
	
	std::cout << std::endl;
}

/****************************************************************************
*						parse(std::string, int, int)						*
*	This function receives the token, its id and the lineNum as arguments.	*
*	It returns bool indicating whether the parsing is successfull.			*
*****************************************************************************/
bool Parser::parse(std::string token, int token_id, int lineNum)
{
	token_position++;
	front = token;
	front_id = token_id;
	const bool FAIL = false;
	const bool SUCCESSFULL = true;
	while (!stack.empty())
	{
		output_token_and_stack_contents(lineNum);
		top = stack.back();
		if (check_fatom_opadd_opmul(front_id, front) == true) {
			top->set_terminal(token);
			top->set_lineNum(lineNum);
			top->set_tokenPosition(token_position);
			return SUCCESSFULL;
		}
		else if (top->get_symbol() == front)
		{
			stack.pop_back();
			return SUCCESSFULL;
		}

		else if (is_top_token())					//add in a way to signal error and stop everything
			return FAIL;

		else{
			find_rule();
			if (rule[0] == "error")								//error
				return FAIL;
			else {
				stack.pop_back();
				top->set_ruleId(rule_id);
				if (rule[0] == "eps") {
					Node * node = new Node("eps", top, 1, -1, -1, -1);
					top->set_kid(node);
					continue;				//Do nothing
				}
				else {
					for (int index = rule.size() - 1, pos = 0; index >= 0; index--, pos++) {
						// Create a new pst node
						Node * node = new Node(rule[index], top, pos, 99, lineNum, find_tokenId(rule[index]));

						// Add node to parent
						top->set_kid(node);

						// Add node to stack
						stack.push_back(node);

						// Check if node is an identifier
						if (node->get_tokenId() == 2) {
							std::cout << "\ttoken id = " << node->get_tokenId() << std::endl;
							// contstruct a new Node for symbol table
							Node* id = new Node(rule[index], top, index, 99 , lineNum, find_tokenId(rule[index]));
							id->set_terminal(token);
							id->set_tokenPosition(token_position);
							// if the id is already in the symbol table
							if (symtab.find(id->get_terminal()) != symtab.end()) {
								std::cout << "\t\t" << id->get_terminal() << " is inside already" << std::endl;
								std::vector<Node*> occurrences = symtab[id->get_terminal()];
								occurrences.push_back(id);
								std::cout << "\t\toccureences.size() " << occurrences.size() << std::endl;
								symtab[id->get_terminal()] = occurrences;
							}
							// if the id is not in the symbol table
							else {
								std::cout << "\t\t" << id->get_terminal() << " is NOT inside already" << std::endl;
								// create vector to store id occurences
								std::vector<Node*> occurrences;
								occurrences.push_back(id);

								// insert new key,value pair in to symtab
								symtab[id->get_terminal()] = occurrences;
							}
						}
					}
				}
			}
		}
	}
	return SUCCESSFULL;
}

/************************************************************************
*						find_rule()										*
*	This function uses the token's id and top of the stack to look		*
*	up the corresponding rules according to the parser matrix			*
*************************************************************************/
void Parser::find_rule() {
	rule.clear();
	Key key(front_id, top->get_symbol());
	std::unordered_map<Key, int , hash_key>::const_iterator get_matrix = parser_matrix.find(key);
	if (get_matrix == parser_matrix.end()) {
		rule_id = 26;
		rule.push_back("error");
	}
	else {
		rule_id = get_matrix->second;
		rule_list.get_rule(&rule, rule_id);
	}
}

/************************************************************************
*							is_top_token()								*
*	Use map_storing_token to check whether top of the stack is a token	*
*************************************************************************/
bool Parser::is_top_token() {
	std::unordered_map<std::string, int>::const_iterator get_token = token_map.find(top->get_symbol());
	if (get_token == token_map.end())
		return false;
	else
		return true;
}

/************************************************************************
*				check_fatom_opadd_opmul(int,std::string)				*
*	Use token's id to compare between top of the stack and the token.	*
*	This is only used to check for id, int ,float, string, +, -, *,		*
*	and ^.																*
*************************************************************************/
bool Parser::check_fatom_opadd_opmul(int token_id, std::string token) {
	switch (token_id) {
	case 2: if (top->get_symbol() == "id") {
		stack.pop_back();
		return true;
		break;
	}
	case 3: if (top->get_symbol() == "int") {
		stack.pop_back();
		return true;
		break;
	}
	case 4: if (top->get_symbol() == "float") {
		stack.pop_back();
		return true;
		break;
	}
	case 5: if (top->get_symbol() == "string") {
		stack.pop_back();
		return true;
		break;
	}
	case 46: if (top->get_symbol() == "-") {
		stack.pop_back();
		return true;
		break;
	}
	case 47: if (top->get_symbol() == "+") {
		stack.pop_back();
		return true;
		break;
	}
	case 41: if (top->get_symbol() == "*") {
		stack.pop_back();
		return true;
		break;
	}
	case 42: if (top->get_symbol() == "^") {
		stack.pop_back();
		return true;
		break;
	}
	case 48: if (top->get_symbol() == "/") {
		stack.pop_back();
		return true;
		break;
	}
	}
	return false;
}

std::string Parser::getAbbreviation(std::string stack_content) {
	std::unordered_map<std::string, std::string>::const_iterator getAb = abbre_map.find(stack_content);
	return getAb->second;
}

/********************************************************************************************************
*											Parser::print_pst()                                          *
*	This function prints the parse tree.                                             					*
********************************************************************************************************/
void Parser::print_pst() {
	pst.print_preorder(pst.get_root());
}

void Parser::set_tokenPosition(int pos) {
	token_position = pos;
}

int Parser::get_tokenPosition() {
	return token_position;
}

int Parser::find_tokenId(std::string token) {
	std::unordered_map<std::string, int>::const_iterator get_token = token_map.find(token);
	if (token == "int")
		return 3;
	else if (token == "float")
		return 4;
	else if (token == "string")
		return 5;
	else if (token == "id") //Token is an identifier not found in map
		return 2;
	else if (get_token == token_map.end()) {
		return 99; //Return the ID for error
	}
	else																						//Found and return token's ID
	{
		return get_token->second;
	}
}

/********************************************************************************************************
*											Parser::print_symtab()                                      *
*	This function prints the symbol table.                                             					*
********************************************************************************************************/
void Parser::print_symtab() {
	std::cout << "Printing symtab" << symtab.size() << std::endl;
	typedef std::map<std::string, std::vector<Node*>>::iterator it_type;
	for (it_type iterator = symtab.begin(); iterator != symtab.end(); iterator++) {
		std::cout << "(Id: \"" << iterator->first << "\"";
		std::vector<Node *> occurrences = iterator->second;
		for (int i = 0; i < occurrences.size(); i++) {
			std::cout << " (T: lin= " << occurrences[i]->get_lineNum() << " ";
			std::cout << "pos= " << occurrences[i]->get_tokenPosition() << " )";
		}
		std::cout << ")" << std::endl;
	}
}

void Parser::print_create_ast() {
	pst.p2ast(pst.get_root());
	pst.print_preorder_ast(pst.get_root());
}