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

void Pst::p2acvt(Node * rp) {
	int rId = rp->get_ruleId();
	Node * gma = rp->get_uplink();
	switch (rId) {
	case 14:{								//F -> Fatom		
		gma->change_specific_kid(rp->get_position(), rp->get_kid(0));
        rp->set_uplink(gma);
		break;
	}
	case 16: {								//F -> Fatom -> id
		gma->change_specific_kid(0, rp->get_kid(0));
		gma->set_numKid(1);
		rp->set_uplink(gma);
		break;
	}

	case 17: {								//F -> Fatom -> int	
		gma->change_specific_kid(0, rp->get_kid(0));
		gma->set_numKid(1);
		rp->set_uplink(gma);
		break;
	}

	case 18: {								//F -> Fatom -> float	
		gma->change_specific_kid(0, rp->get_kid(0));
		gma->set_numKid(1);
		rp->set_uplink(gma);
		break;
	}

	case 19: {								//F -> Fatom -> string
		gma->change_specific_kid(0, rp->get_kid(0));
		gma->set_numKid(1);
		rp->set_uplink(gma);
		break;
	}

	case 20: {								//Y -> Opadd -> +
		gma->change_specific_kid(0, rp->get_kid(0));
		rp->set_uplink(gma);
		break;
	}

	case 21: {								//Y -> Opadd -> -		
		gma->change_specific_kid(0, rp->get_kid(0));
		rp->set_uplink(gma);
		break;
	}

	case 22: {								//Z -> Opmul -> *
		gma->change_specific_kid(0, rp->get_kid(0));
		gma->set_numKid(1);
		rp->set_uplink(gma);
		break;
	}

	case 23: {								//Z -> Opmul -> /
		gma->change_specific_kid(0, rp->get_kid(0));
		gma->set_numKid(1);
		rp->set_uplink(gma);
		break;
	}

	case 24: {								//Z -> Opmul -> ^
		gma->change_specific_kid(0, rp->get_kid(0));
		gma->set_numKid(1);
		rp->set_uplink(gma);
		break;
	}

	case 25: {								//Anything ->Anything -> Eps
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
	for (int i = rp->get_numKid() - 1; i >= 0; i--) {
		p2ast(rp->get_kid(i));
	}
	p2acvt(rp);
}