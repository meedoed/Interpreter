#pragma once
#ifndef PARSER_H
#define PARSER_H
#include "Lexer.h"
#include "Lexeme.h"
#include <map>
#include <vector>
#include <iostream>

class Parser
{
public:
	~Parser();
	Parser()
	{
		line = 0;
	}

	void Parse(Lexer lexer);

private:


	vector<Lexeme>::iterator currentToken;
	vector<Lexeme>::iterator endToken;
	int line;


	map<std::string, std::vector<std::string> > firstSets = {
		{"expr", {"TYPE", "VAR", "IF_KW", "$"}},
		{"value_expr", {"L_BR", "VAR", "NUMBER", "$"}}
	};
	void lang();
	void expr();
	void assign(bool semicol = true);
	void value_expr();
	void if_expr();
	void if_head();
	void if_condition();
	void if_body();
	void else_expr();
	void else_head();
	void else_body();
	void value_expr_wbr();
	void value();
	void logical_expr();

	void IgnoreWhitespaces();
	void checkExpr();
	void Match(string t);
	void err(const string& message);
};

#endif // PARSER_H