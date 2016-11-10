//File name: map_storing_abbreviation.h
//Author: Daniel Nguyen
//Written on 10/23/2016
//Description: File contains an unordered_map storing the Terminal and Non-terminal symbols of the rules
//as keys and their abbreviations as look-up values.

#ifndef MAP_STORING_ABBREVIATION_H
#define MAP_STORING _ABBREVIATION_H
#pragma once
#include <unordered_map>
#include <string>

std::unordered_map<std::string,std::string> abbre_map = {
	{"E","E."},
	{"Elist","EL."},
	{"Elist2", "E2."},
	{"F","F."},
	{"Fatom","Fa."},
	{"Opadd","O+."},
	{"Opmul","O*"},
	{"Pgm","Pg."},
	{"S_Asgn","S=."},
	{"S_In","SI."},
	{"S_Out","SO."},
	{"Slist","SL."},
	{"Stmt","S."},
	{"T","T."},
	{"X","X."},
	{"Y","Y."},
	{"Z","Z."},
	{"*","*."},
	{"{","{."},
	{"}","}."},
	{"^","^."},
	{",",",."},
	{"=","=."},
	{"float","fl."},
	{"id","id."},
	{"int","it."},
	{"input","ki."},
	{"print","ko."},
	{"prog","kp."},
	{"-","-."},
	{"(","(."},
	{")",")."},
	{"+","+."},
	{";",";."},
	{"/","/."},
	{"string","st."},
	{"eof","eof."}
};

#endif