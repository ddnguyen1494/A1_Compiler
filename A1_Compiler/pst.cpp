/**
* Created by Daniel Nguyen
* Modified by Sae Hun Kim
*/

#include <iostream>
#include "pst.h"

//Delete all the node
void Pst::clear(Node * rp)
{
	if (!rp) {
		return;
	}
	for (int i = 0; i < rp->get_numKid(); i++) {
		clear(rp->get_kid(i));
	}
	delete rp;
}

//print function for pst
void Pst::print(Node * rp) {
	if (rp->get_numKid() > 0) {
		std::cout << "(N: rule= # " << rp->get_ruleId()
			<< ": " << rp->get_symbol() << " = ";
		for (int i = rp->get_numKid() -1 ; i >= 0; i--)
			std::cout << rp->get_kid(i)->get_symbol() << " ";
		

		if ((rp->get_numKid() == 1) && (rp->get_kid(0)->get_numKid() == 0) && (rp->get_kid(0)->get_symbol() != "eps"))
		{
			std::cout << "(T: " << rp->get_kid(0)->get_terminal() << " lin= " << rp->get_kid(0)->get_lineNum()
				<< " pos= " << rp->get_kid(0)->get_tokenPosition() << ")";
		}

		std::cout << ")" << std::endl;
	}
}


void Pst::print_ast(Node * rp) {
	if (rp->get_symbol() != "Pgm") 
	{
		std::cout << "N " << rp->get_position() << ": " << rp->get_symbol()
			<< " mom= " << rp->get_uplink()->get_tokenId() << " kids= " << rp->get_numKid();
	}

	if ((rp->get_numKid() == 1) && (rp->get_kid(0)->get_numKid() == 0) && (rp->get_kid(0)->get_symbol() != "eps"))
	{
		std::cout << "(T: " << rp->get_kid(0)->get_terminal() << " lin= " << rp->get_kid(0)->get_lineNum()
			<< " pos= " << rp->get_kid(0)->get_tokenPosition() << ")";
	}

	std::cout << ")" << std::endl;
}

void Pst::p2acvt(Node * rp) {
	int rId = rp->get_ruleId();
	Node * gma = rp->get_uplink();
	switch (rId) {
	case 12: {         // T -> F Z
		std::cout << "\tcase12 kid0 is null? " << (rp->get_kid(0) == NULL) << std::endl;
		if (rp->get_kid(0)->get_kid(1) == NULL) {
			//gma abandon mom T and adopt Z
			gma->change_specific_kid(rp->get_position(), rp->get_kid(0));
			//set Z's mom to gma
			rp->get_kid(0)->set_uplink(gma);


			std::cout << "\tcase12if " << rp->get_kid(0)->get_numKid() << std::endl;
			std::cout << "\tcase12if " << rp->get_kid(0)->get_symbol() << std::endl;

			// Z's 2nd child adopts F
			rp->get_kid(0)->change_specific_kid(1, rp->get_kid(1));
			// set F's mom to be Z's 2nd child
			rp->get_kid(1)->set_uplink(rp->get_kid(0));

			delete rp;
		}
		else
		{
			//gma abandon mom T and adopt Z
			gma->change_specific_kid(rp->get_position(), rp->get_kid(0));
			//set Z's mom to gma
			rp->get_kid(0)->set_uplink(gma);


			std::cout << "\tcase12else " << rp->get_kid(0)->get_numKid() << std::endl;
			std::cout << "\tcase12else " << rp->get_kid(0)->get_symbol() << std::endl;

			// Z's 2nd child adopts F
			rp->get_kid(0)->get_kid(1)->change_specific_kid(1, rp->get_kid(1));
			// set F's mom to be Z's 2nd child
			rp->get_kid(1)->set_uplink(rp->get_kid(0)->get_kid(1));

			delete rp;
		}
		break;
	}
	case 13: {         // Z -> Opmul F Z
					   // Z is in pos 0, F is in pos 1, Opmul in pos 2
		if (rp->get_kid(0) == NULL) {
			//gma abandon mom Z and adopt Opmul
			gma->change_specific_kid(rp->get_position(), rp->get_kid(2));
			// Opmul adopt sibling F
			rp->get_kid(2)->change_specific_kid(0, rp->get_kid(1));
			//set Opmul's mom to gma
			rp->get_kid(2)->set_uplink(gma);
			//set F's mom to Opmul
			rp->get_kid(1)->set_uplink(rp->get_kid(2));
			delete rp;
		}
		else {
			//gma abandon mom Z and adopt kid Z's Opmul
			gma->change_specific_kid(rp->get_position(), rp->get_kid(0));
			//set kid Z's Opmul to gma
			rp->get_kid(0)->set_uplink(gma);

			// mom Z's Opmul adopt sibling F
			rp->get_kid(2)->change_specific_kid(0, rp->get_kid(1));
			// set sibling F's mom to mom Z's Opmul
			rp->get_kid(1)->set_uplink(rp->get_kid(2));

			// kid Z's Opmul adopt mom Z's Opmul
			rp->get_kid(0)->change_specific_kid(1, rp->get_kid(2));
			// set mom Z's Opmul's mom to kid Z's Opmul
			rp->get_kid(2)->set_uplink(rp->get_kid(0));

			delete rp;
		}
		break;
	}
	case 14: {								//F -> Fatom		
		//grandma abandon F and adopt Fatom
		gma->change_specific_kid(rp->get_position(), rp->get_kid(0));
		//set float 's mom to F
		rp->get_kid(0)->set_uplink(gma);
		delete rp;
		break;
	}

	case 15: {                               //F -> ( E )
		gma->change_specific_kid(rp->get_position(), rp->get_kid(1));
		rp->get_kid(1)->set_uplink(gma);
		delete rp->get_kid(0);
		delete rp->get_kid(2);
		delete rp;
	}
	case 16: {								//F -> Fatom -> id
											//F abandon Fatom and adopt id
		gma->change_specific_kid(rp->get_position(), rp->get_kid(0));
		//set id's mom to F
		rp->get_kid(0)->set_uplink(gma);
		delete rp;
		break;
	}

	case 17: {								//F -> Fatom -> int	
											//F abandon Fatom and adopt int
		gma->change_specific_kid(rp->get_position(), rp->get_kid(0));
		//set int's mom to F
		rp->get_kid(0)->set_uplink(gma);
		delete rp;
		break;
	}

	case 18: {								//F -> Fatom -> float	
											//F abandon Fatom and adopt float
		gma->change_specific_kid(rp->get_position(), rp->get_kid(0));
		//set float's mom to F
		rp->get_kid(0)->set_uplink(gma);
		delete rp;
		break;
	}

	case 19: {								//F -> Fatom -> string
											//F abandon Fatom and adopt string
		gma->change_specific_kid(rp->get_position(), rp->get_kid(0));
		//set string's mom to F
		rp->get_kid(0)->set_uplink(gma);
		delete rp;
		break;
	}

	case 20: {								//Y -> Opadd -> +
											//Y abandon Opadd and adopt plus
		gma->change_specific_kid(rp->get_position(), rp->get_kid(0));
		//set plus's mom to Y
		rp->get_kid(0)->set_uplink(gma);
		delete rp;
		break;
	}

	case 21: {								//Y -> Opadd -> -		
											//Y abandon Opadd and adopt minus
		gma->change_specific_kid(rp->get_position(), rp->get_kid(0));
		//set minus's mom to Y
		rp->get_kid(0)->set_uplink(gma);
		delete rp;
		break;
	}

	case 22: {								//Z -> Opmul -> *
		//Z abandon Opmul and adopt asterisk
		gma->change_specific_kid(rp->get_position(), rp->get_kid(0));
		//set asterisk's mom to Z
		rp->get_kid(0)->set_uplink(gma);
		delete rp;
		break;
	}

	case 23: {								//Z -> Opmul -> /
		//Z abandon Opmul and adopt slash
		gma->change_specific_kid(rp->get_position(), rp->get_kid(0));
		//set slash 's mom to Z
		rp->get_kid(0)->set_uplink(gma);
		delete rp;
		break;
	}

	case 24: {								//Z -> Opmul -> ^
		//Z abandon Opmul and adopt caret
		gma->change_specific_kid(rp->get_position(), rp->get_kid(0));
		//set caret 's mom to Z
		rp->get_kid(0)->set_uplink(gma);
		delete rp;
		break;
	}

	case 25: {								//Anything ->Anything -> Eps
		rp->get_uplink()->change_specific_kid(rp->get_position(), NULL);
		delete rp->get_kid(0);				//delete eps node
		delete rp;							//delete eps node's mom
		break;
	}
	default:
		break;
	}
}
Pst::Pst() {
	// The prompt states "The PST has an extra fixed header node that will have one kid"
	// I believe this extra fixed header node is best implemented in the contructor of the PST
	Node * header = new Node("header", nullptr, 0, 0, 0, 0);
	header->set_kid(nullptr); // Give the header an empty soulless kid for now
	_root = header;
}

Pst::~Pst() {
	clear(_root);
	_root = NULL;
}

bool Pst::is_empty() {
	return _root == NULL;
}

// Returns the only child of the fixed header
// For most purposes outside of the parse tree, the "root" is the only child of the fixed header
Node * Pst::get_root () {
	return _root->get_kid(0);
}

// Sets the only child of the fixed header
// For most purposes outside of the parse tree, the "root" is the only child of the fixed header
void Pst::set_root(Node * root) {
	_root->change_specific_kid(0, root);
}

void Pst::print_preorder(Node * rp) {
	if (!rp) {
		return;
	}
	print(rp);
	for (int i = rp->get_numKid()-1; i >= 0 ; i--) {
		print_preorder(rp->get_kid(i));
	}
}

void Pst::p2ast(Node * rp) {
	if (!rp) {
		return;
	}
	for (int i = 0; i < rp->get_numKid(); i++) {
		p2ast(rp->get_kid(i));
	}
	p2acvt(rp);
}

void Pst::print_preorder_ast(Node * rp) {
	if (!rp) {
		return;
	}
	print_ast(rp);
	for (int i = rp->get_numKid() - 1; i >= 0; i--) {
		print_preorder_ast(rp->get_kid(i));
	}
}