/*
* Created by Daniel Nguyen
* Email: duynguyen1494@fullerton.edu
* Created date: 09/02/16
* Modified by Sae Hun Kim, Anthony Nguyen
* Modified date: 09/11/16
*/

#ifndef PST_H
#define PST_H

#pragma once
#include "Node.h"

class Pst {
private:
	Node * _root;				//root of the tree

	Node * top_stack;			//top of the stack; primarily used to hook up kids' nodes to the mom

	void clear(Node*);			//Clear function to deallocate every node of the tree

	void print(Node *);			//print out node's data
	
	void p2acvt(Node *);			//Modify each node to make it ast's node
public:
	//Constructor
	Pst();					
	
	//Destructor
	~Pst();					
	
	//Check if the tree is empty( has no node)
	bool is_empty();			

	//Getter function to retrieve the root of the tree
	Node * get_root();			
	
	//Setter function for the root of the tree
	void set_root(Node *);
	
	//A recursive function to traverse the tree preorder (used for printing out node's data)
	void print_preorder(Node *);
	
	//A recursive function to traverse the tree preorder (used for converting pst to ast)
	void p2ast(Node *);
};
#endif
