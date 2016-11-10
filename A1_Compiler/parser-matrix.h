//File name: parser-matrix.h
//Author:Daniel Nguyen
//Written on 10/04/2016
//Description: This file initilizes an unordered map using a pair of token id and LHS as key and return the RHS vectors.

#ifndef PARSER_MATRIX_H
#define PARSER_MATRIX_H
#pragma once
#include<functional>
#include <vector>
#include <unordered_map>

//define the key as a pair of int and string
typedef std::pair<int, std::string> Key;

//Create a hash_key structure that hash Keys
struct hash_key {
	std::size_t operator()(Key key) const
	{
		return std::hash<int>()(key.first) ^ std::hash<std::string>()(key.second);
	}
};

//Based on the Parser-matrix.pdf file, initialize all the keys for all non-empty cells using the corresponding column and row headers
Key prog_pgm(10, "Pgm");
Key print_slist(23, "Slist");
Key brace2_slist(34, "Slist");
Key id_slist(2, "Slist");
Key print_stmt(23, "Stmt");
Key id_stmt(2, "Stmt");
Key input_x(22, "X");
Key paren1_x(37, "X");
Key id_x(2, "X");
Key int_x(3, "X");
Key float_x(4, "X");
Key string_x(5, "X");
Key print_s_out(23, "S_Out");
Key paren1_elist(37, "Elist");
Key paren2_elist(38, "Elist");
Key id_elist(2, "Elist");
Key int_elist(3, "Elist");
Key float_elist(4, "Elist");
Key string_elist(5, "Elist");
Key comma_elist2(6, "Elist2");
Key paren1_e(37, "E");
Key id_e(2, "E");
Key int_e(3, "E");
Key float_e(4, "E");
Key string_e(5, "E");
Key semi_Y(7, "Y");
Key comma_Y(6, "Y");
Key plus_Y(47, "Y");
Key minus_Y(46, "Y");
Key paren2_Y(38, "Y");
Key paren1_T(37, "T");
Key id_T(2, "T");
Key int_T(3, "T");
Key float_T(4, "T");
Key string_T(5, "T");
Key semi_Z(7, "Z");
Key comma_Z(6, "Z");
Key plus_Z(47, "Z");
Key minus_Z(46, "Z");
Key aster_Z(41, "Z");
Key slash_Z(48, "Z");
Key caret_Z(42, "Z");
Key paren2_Z(38, "Z");
Key paren1_F(37, "F");
Key id_F(2, "F");
Key int_F(3, "F");
Key float_F(4, "F");
Key string_F(5, "F");
Key id_fatom(2, "Fatom");
Key int_fatom(3, "Fatom");
Key float_fatom(4, "Fatom");
Key string_fatom(5, "Fatom");
Key plus_opadd(47, "Opadd");
Key minus_opadd(46, "Opadd");
Key aster_opmul(41, "Opmul");
Key slash_opmul(48, "Opmul");
Key caret_opmul(42, "Opmul");

//Populate the unordered_map using all the keys defined above and RHS arrays as values needed to look up according to the parser matrix
const std::unordered_map<Key, int, hash_key> parser_matrix{
	{ prog_pgm, 1 },
	{ print_slist,2 },
	{ brace2_slist,25 },
	{ id_slist, 2 },
	{ print_stmt, 6 },
	{ id_stmt, 3 },
	{ input_x, 5 },
	{ paren1_x, 4 },
	{ id_x, 4 },
	{ int_x, 4 },
	{ float_x, 4 },
	{ string_x,4 },
	{ print_s_out, 7 },
	{ paren1_elist, 8 },
	{paren2_elist, 25},
	{id_elist, 8},
	{int_elist, 8},
	{float_elist, 8},
	{string_elist, 8},
	{comma_elist2, 9},
	{paren1_e, 10},
	{id_e, 10},
	{int_e, 10},
	{float_e, 10},
	{string_e, 10},
	{paren2_Y, 25},
	{semi_Y, 25},
	{comma_Y,25},
	{plus_Y, 11},
	{minus_Y, 11},
	{paren1_T, 12},
	{id_T, 12},
	{int_T, 12},
	{float_T, 12},
	{string_T, 12},
	{paren2_Z, 25},
	{semi_Z, 25},
	{comma_Z, 25},
	{plus_Z, 25},
	{minus_Z, 25},
	{aster_Z, 13},
	{slash_Z, 13},
	{caret_Z, 13},
	{paren1_F, 15},
	{id_F, 14},
	{int_F, 14},
	{float_F, 14},
	{string_F, 14},
	{id_fatom, 16},
	{int_fatom, 17},
	{float_fatom, 18},
	{string_fatom, 19},
	{plus_opadd, 20},
	{minus_opadd, 21},
	{aster_opmul, 22},
	{slash_opmul, 23},
	{caret_opmul,24}
};

#endif
