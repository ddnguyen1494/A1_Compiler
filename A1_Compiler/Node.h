/**
* Created by Daniel Nguyen
* Modified by Sae Hun Kim
*/

#ifndef NODE_H
#define NODE_H
#pragma once

#include <string>

class Node{
	private:
		std::string symbol;
		Node* upLink;
		int position;
		Node * kids[4] = { nullptr };
		int ruleId;
		int numKids = 0;
		int lineNum; // Added line num per Daniel's request
		int tokenId; // Added token id per Daniel's request
		std::string terminal;			//Add terminal symbol to print out actual string | int | float | ident
		int token_position;				//Add token position because printing out string| int | float | ident require this
	public:
		Node(std::string, Node * , int, int, int, int);
		
		//Add in to handle situation Fatom = string/int/id/float because we need to print out token, line, and position for those
		std::string get_terminal();
		void set_terminal(std::string);

		void set_symbol(std::string);
		std::string get_symbol();
		
		void set_uplink(Node*);
		Node* get_uplink();
		
		void set_position(int);
		int get_position();
		
		void set_kid(Node*);
		void change_specific_kid(int, Node*); // Addition by Sae Hun Kim
		Node * get_kid(int);

		int get_numKid();
		void dec_numKid();
		void set_numKid(int);

		int get_ruleId();
		void set_ruleId(int);

		// Additions by Sae Hun Kim
		int get_lineNum();
		void set_lineNum(int);

		int get_tokenId();

		int get_tokenPosition();
		void set_tokenPosition(int);
};


#endif
