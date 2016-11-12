/*
* Created by Daniel Nguyen
* Email: duynguyen1494@fullerton.edu
* Modified by Sae Hun Kim
* Modified date: 11/09/16
* File Description: This file contains the Node class declaration.
*/

#ifndef NODE_H
#define NODE_H
#pragma once

#include <string>

class Node{
	private:
		std::string symbol;			//The symbol of the node
	
		Node* upLink;				//Uplink pointer pointing to the mom
	
		int position;				//position of the node on the RHS starting at 0
	
		Node * kids[4] = { nullptr };		//array of pointers pointing to all its kids (RHS Nodes)
	
		int ruleId;				//It has rule Id if its a LHS, otherwise intialized to -1
	
		int numKids = 0;			//Initialize number of kids to 0
	
		int lineNum; 				//line number terminal node
	
		int tokenId; 				//token id for terminal node
	
		std::string terminal;			//terminal used in printing out id|int|float|string|Opadd|Opmul
	
		int token_position;			//position in the line
	public:
		//Constructor 
		Node(std::string, Node * , int, int, int, int);
		
		//setter and getter for terminal string
		std::string get_terminal();
		void set_terminal(std::string);
		
		//setter and getter for symbol string
		void set_symbol(std::string);
		std::string get_symbol();
		
		//setter and getter for uplin Node
		void set_uplink(Node*);
		Node* get_uplink();
		
		//setter and getter for position index
		void set_position(int);
		int get_position();
		
		//setter and getter for Kid pointer in the array
		void set_kid(Node*);
		void change_specific_kid(int, Node*); 			// Addition by Sae Hun Kim
		Node * get_kid(int);
		
		//setter and getter for number of Kids
		int get_numKid();
		void set_numKid(int);
		
		//setter and getter for rule Id
		int get_ruleId();
		void set_ruleId(int);

		//Setter and getter for line num (Additions by Sae Hun Kim)
		int get_lineNum();
		void set_lineNum(int);
		
		//getter for token id
		int get_tokenId();
		
	
		//setter and getter for token position in a line.
		int get_tokenPosition();
		void set_tokenPosition(int);
};


#endif
