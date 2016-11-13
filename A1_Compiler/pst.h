/**
* Created by Daniel Nguyen
*/

#ifndef PST_H
#define PST_H

#pragma once
#include "Node.h"

class Pst {
private:
	Node * _root;
	Node * top_stack;

	void clear(Node*);

	void print(Node *);

	void p2acvt(Node *);
public:
	Pst();

	~Pst();

	bool is_empty();

	Node * get_root();

	void set_root(Node *);

	void print_preorder(Node *);
	
	void p2ast(Node *);
};
#endif
