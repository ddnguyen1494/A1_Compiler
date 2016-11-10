//File name: map_storing_token.h
//Author: Daniel Nguyen
//CWID: 891794570
//Written on 9/23/2016
//File description: This header file declares and initializes the unorderd map with keywords and operators as the keys 
//and token's ID as look-up value.

#ifndef MAP_STORING_TOKEN_H
#define MAP_STORING_TOKEN_H
#include <unordered_map>
#pragma once

const std::unordered_map<std::string, int> token_map = {
	{",",6},
	{";",7},
	{ "prog" ,10},
	{ "main" ,11},
	{"fcn",12},
	{ "class" ,13},
	{ "float" ,15},
	{ "int" ,16},
	{ "string" ,17},
	{ "if" ,18},
	{ "elseif" ,19},
	{ "else" ,20},
	{ "while" ,21},
	{ "input" ,22},
	{ "print" ,23},
	{ "new" ,24},
	{ "return" ,25},
	{ "<" ,31},
	{ ">" ,32 },
	{ "{" ,33 },
	{ "}" ,34 },
	{ "[" ,35 },
	{ "]" ,36 },
	{ "(" ,37 },
	{ ")" ,38 },
	{ "*" ,41 },
	{ "^" ,42 },
	{ ":" ,43 },
	{ "." ,44 },
	{ "=" ,45 },
	{ "-" ,46 },
	{ "+" ,47 },
	{ "/" ,48 },
	{ "->" ,51 },
	{ "==" ,52 },
	{ "!=" ,53 },
	{ "<=" ,54 },
	{ ">=" ,55 },
	{ "<<" ,56 },
	{ ">>" ,57 },
	{ "error" ,99 },
	{ "eof" ,0 },
};

#endif

