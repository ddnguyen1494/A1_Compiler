/**
* Created by Daniel Nguyen
* Email: duynguyen1494@fullerton.edu
* Modified by Sae Hun Kim
* Modified date: 11/09/16
* File description: This file contains the definition for all functions of Node class
*/

#include "Node.h"

//Constructor initializing symbol, upLink, position, ruleId, lineNum, and tokenId
Node::Node(std::string sym, Node * mom, int pos, int ruleNum, int lineNum, int tokenId)
	: symbol(sym), upLink(mom), position(pos), ruleId(ruleNum), lineNum(lineNum), tokenId(tokenId) {};

//Setter for symbol
void Node::set_symbol(std::string s){
	symbol = s;
}

//Getter for symbol
std::string Node::get_symbol(){
	return symbol;
}

//Setter for terminal string
std::string Node::get_terminal() {
	return terminal;
}

//Getter for terminal string
void Node::set_terminal(std::string token) {
	terminal = token;
}

//Setter for upLink pointer
void Node::set_uplink(Node * mom){
	upLink = mom;
}

//Getter for upLink pointer
Node * Node::get_uplink(){
	return upLink;
}

//Setter for position 
void Node::set_position(int pos){
	position = pos;
}

//Getter for position
int Node::get_position(){
	return position;
}

//Receiving the pointer poiting to a node, setting next kid in the array to the argument node, increment the number of kids
void Node::set_kid(Node * kid){
	kids[numKids] = kid;
	numKids++;
}

// Change a specific specific kid to the given kid
// pos must be an index of an already existing kid (added by Sae Hun Kim)
void Node::change_specific_kid(int pos, Node * kid) {
	if (pos >= 0 && pos < numKids) {
		kids[pos] = kid;
	}
}

//Getter function receiving int and use it as index to access specific kid
Node * Node::get_kid(int kid_position){
	return kids[kid_position];
}

//Getter function for number of kids.
int Node::get_numKid() {
	return numKids;
}

//Setter function for number of kids.
void Node::set_numKid(int num) {
	numKids = num;
}

//Getter function for ruleID
int Node::get_ruleId() {
	return ruleId;
}

//Setter function for ruleId
void Node::set_ruleId(int id) {
	ruleId = id;
}

//Getter function for line number
int Node::get_lineNum() {
	return lineNum;
}

//Setter function for line number
void Node::set_lineNum(int num) {
	lineNum = num;
}

int Node::get_tokenId() {
	return tokenId;
}

void Node::set_tokenPosition(int pos) {
	token_position = pos;
}

int Node::get_tokenPosition() {
	return token_position;
}
