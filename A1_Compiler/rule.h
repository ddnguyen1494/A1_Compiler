//Initialize all RHS rules as arrays of std::vector<std::string>
#ifndef RULE_H
#define RULE_H
#pragma once
#include <string>
#include <vector>

class A1_Rule {
private:
	std::string Pgm[4] = { "prog","{","Slist","}"};
	std::string Slist[3] = { "Stmt",";","Slist"};
	std::string Stmt1[3] = { "id","=","X"};
	std::string X1[1] = { "E"};
	std::string X2[1] = { "input"};
	std::string Stmt2[1] = { "S_Out"};
	std::string S_Out[4] = { "print","(", "Elist", ")"};
	std::string Elist[2] = { "E","Elist2"};
	std::string Elist2[2] = { ",", "Elist"};
	std::string E[2] = { "T","Y"};
	std::string Y[3] = { "Opadd","T","Y"};
	std::string T[2] = { "F","Z"};
	std::string Z[3] = { "Opmul","F","Z"};
	std::string F1[1] = { "Fatom"};
	std::string F2[3] = { "(", "E", ")"};
	std::string Fatom_id[1] = { "id"};
	std::string Fatom_int[1] = { "int"};
	std::string Fatom_float[1] = { "float"};
	std::string Fatom_string[1] = { "string"};
	std::string Opadd_plus[1] = { "+"};
	std::string Opadd_minus[1] = { "-"};
	std::string Opmul_aster[1] = { "*"};
	std::string Opmul_slash[1] = { "/"};
	std::string Opmul_caret[1] = { "^"};
	std::string Eps[1] = { "eps"};
	std::string Error[1] = { "error" };
public:
	void get_rule(std::vector<std::string> *, int);

	};
#endif