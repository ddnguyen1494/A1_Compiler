//File name: parser.h
//Author: Daniel Nguyen
//Written on 10/23/2016
//Description: This file contains the declaration of Parser class
//Modified by Sae Hun Kim and Anthony Nguyen

#ifndef PARSER_H
#define PARSER_H
#pragma once
#include "rule.h"

// Additions by Sae Hun Kim and Anthony Nguyen
#include "Node.h"
#include "pst.h"
#include <map>
#include <vector>
#include <string>

class Parser {
private:
	std::vector<Node*> stack; // Change stack<RHS> to stack<Pst_Node>
	std::vector<std::string> rule;	
	std::string front;
	Node* top; // Change type from string to pst node
	int front_id;
	int rule_id;
	A1_Rule rule_list;

	// Additions by Sae Hun Kim and Anthony Nguyen
	Pst pst;
	int token_position;
	int nodeCreationCounter = 0;
	std::map<std::string, std::vector<Node*>> symtab;
public:
	Parser();
	bool parse(std::string, int, int);
	bool is_top_token();
	void output_token_and_stack_contents(int);
	void find_rule();
	bool check_fatom_opadd_opmul(int, std::string);
	std::string getAbbreviation(std::string);

	// Additions by Sae Hun Kim and Anthony Nguyen
	void print_pst();
	void print_symtab();

	int get_tokenPosition();
	void set_tokenPosition(int);

	int find_tokenId(std::string);

	void print_create_ast();
};

#endif