/**
* Created by Daniel Nguyen
*/

#ifndef PST_H
#define PST_H

#pragma once
#include "Node.h"
#include <vector>
using std::vector;

class Pst {
private:
	Node * _root;
	Node * top_stack;

	void clear(Node*);

	void print(Node *);

	void p2acvt(Node *);

	void print_ast(Node*);

	vector<Node*> S_Out_Vector;
	vector<Node*> prog_vector;
public:
	Pst();

	~Pst();

	bool is_empty();

	Node * get_root();

	void set_root(Node *);

	void print_preorder(Node *);
	
	void p2ast(Node *);

	void print_preorder_ast(Node *);
};
#endif
