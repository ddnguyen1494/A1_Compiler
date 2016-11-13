/**
* Created by Daniel Nguyen
* Modified by Sae Hun Kim
*/

#include "Node.h"

Node::Node(std::string sym, Node * mom, int pos, int ruleNum, int lineNum, int tokenId)
	: symbol(sym), upLink(mom), position(pos), ruleId(ruleNum), lineNum(lineNum), tokenId(tokenId) {};

void Node::set_symbol(std::string s){
	symbol = s;
}

std::string Node::get_terminal() {
	return terminal;
}

void Node::set_terminal(std::string token) {
	terminal = token;
}
std::string Node::get_symbol(){
	return symbol;
}

void Node::set_uplink(Node * mom){
	upLink = mom;
}

Node * Node::get_uplink(){
	return upLink;
}

void Node::set_position(int pos){
	position = pos;
}

int Node::get_position(){
	return position;
}

void Node::set_kid(Node * kid){
	kids[numKids] = kid;
	numKids++;
}

// Change a specific specific kid to the given kid
// pos must be an index of an already existing kid
void Node::change_specific_kid(int pos, Node * kid) {
	if (pos >= 0 && pos < numKids) {
		kids[pos] = kid;
	}
}

Node * Node::get_kid(int kid_position){
	return kids[kid_position];
}

int Node::get_numKid() {
	return numKids;
}

void Node::dec_numKid() {
	--numKids;
}

void Node::set_numKid(int num) {
	numKids = num;
}

int Node::get_ruleId() {
	return ruleId;
}

void Node::set_ruleId(int id) {
	ruleId = id;
}

int Node::get_lineNum() {
	return lineNum;
}

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