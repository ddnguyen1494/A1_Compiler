#include "rule.h"

void A1_Rule::get_rule(std::vector<std::string> * vect_ptr, int rule_id) {
	switch (rule_id) {
	case 1:
		vect_ptr->insert(vect_ptr->begin(), Pgm, Pgm + 4);
		break;
	case 2:
		vect_ptr->insert(vect_ptr->begin(), Slist, Slist + 3);
		break;
	case 3:
		vect_ptr->insert(vect_ptr->begin(), Stmt1, Stmt1 + 3);
		break;
	case 4:
		vect_ptr->push_back("E");
		break;
	case 5:
		vect_ptr->push_back("input");
		break;
	case 6:
		vect_ptr->push_back("S_Out");
		break;
	case 7:
		vect_ptr->insert(vect_ptr->begin(), S_Out, S_Out + 4);
		break;
	case 8:
		vect_ptr->insert(vect_ptr->begin(), Elist, Elist + 2);
		break;
	case 9:
		vect_ptr->insert(vect_ptr->begin(), Elist2, Elist2 + 2);
		break;
	case 10:
		vect_ptr->insert(vect_ptr->begin(), E, E + 2);
		break;
	case 11:
		vect_ptr->insert(vect_ptr->begin(), Y, Y + 3);
		break;
	case 12:
		vect_ptr->insert(vect_ptr->begin(), T, T + 2);
		break;
	case 13:
		vect_ptr->insert(vect_ptr->begin(), Z, Z + 3);
		break;
	case 14:
		vect_ptr->push_back("Fatom");
		break;
	case 15:
		vect_ptr->insert(vect_ptr->begin(), F2, F2 + 4);
		break;
	case 16:
		vect_ptr->push_back("id");
		break;
	case 17:
		vect_ptr->push_back("int");
		break;
	case 18:
		vect_ptr->push_back("float");
		break;
	case 19:
		vect_ptr->push_back("string");
		break;
	case 20:
		vect_ptr->push_back("plus");
		break;
	case 21:
		vect_ptr->push_back("-");
		break;
	case 22:
		vect_ptr->push_back("*");
		break;
	case 23:
		vect_ptr->push_back("/");
		break;
	case 24:
		vect_ptr->push_back("^");
		break;
	case 25:
		vect_ptr->push_back("eps");
		break;
	case 26:
		vect_ptr->push_back("error");
		break;
	}
}