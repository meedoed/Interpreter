#include "Parser.h"


/*
		lang -> expr+
		expr -> assign_expr | if_expr | var_declaration | for_expr
		assign_expr -> VAR ASSIGN_OP value_expr SC
		value_expr -> (value_expr_wbr | value) (OP value_expr)*
		value_expr_wbr -> L_BR value_expr R_BR
		value -> NUMBER | VAR
		if_expr -> if_head if_body (else_head else_body)?
		if_head -> IF_KW if_condition
		else_head -> ELSE_KW
		if_condition -> L_BR logical_expr R_BR
		logical_expr -> value_expr LOGICAL_OP value_expr
		if_body -> L_S_BR expr+ R_S_BR
		else_body -> L_S_BR expr+ R_S_BR
		VAR -> [a-zA-Z][a-zA-Z1-9_]*
		ASSIGN_OP -> =
		IF_KW -> if
		ELSE_KW -> else
		L_BR -> (
		R_BR -> )
		L_S_BR -> {
		R_S_BR -> }
		NUMBER -> 0|([1-9][0-9]*)
		OP -> [+-/*]
		LOGICAL_OP -> > | <
		SC -> ;
		NLINE -> \n
		WS -> [\t\s]+
	 */

//using namespace std;


Parser::~Parser()
{
}

	void Parser::lang()
	{
		checkExpr();
		if(currentToken->getTerminal().getIdentifier() != "EOF")
		{
			err("Expected end of file, but met: " + currentToken->getTerminal().getIdentifier());
		}
	}

	void Parser::expr()
	{
		auto firstSet = firstSets.at("expr");
		const std::string id = *std::find(firstSet.begin(), firstSet.end(), currentToken->getTerminal().getIdentifier());
		
		 if (id == "VAR")
		{
			assign();
		}
		else if (id == "IF_KW")
		{
			if_expr();
		}
		else
		{
			err("Unexpected token: " + currentToken->getTerminal().getIdentifier());
		}

	}

	void Parser::assign(bool semicol)
	{
		Match("VAR");
		Match("ASSIGN_OP");
		value_expr();
		if(semicol)
			Match("SC");
	}

	void Parser::value_expr()
	{
		auto firstSet = firstSets.at("value_expr");
		IgnoreWhitespaces();
		const std::string id = *std::find(firstSet.begin(), firstSet.end(), currentToken->getTerminal().getIdentifier());
		if(id == "L_BR")
		{
			value_expr_wbr();
		}
		else if(id == "VAR" || id == "NUMBER")
		{
			value();
		}
		else
		{
			err("Unexpected token: " + currentToken->getTerminal().getIdentifier());
		}
		if (currentToken->getTerminal().getIdentifier() == "OP")
		{
			Match("OP");
			value_expr();
		}

	}

	void Parser::value_expr_wbr()
	{
		Match("L_BR");
		value_expr();
		Match("R_BR");

	}

	void Parser::value()
	{
		try
		{
			Match("NUMBER");
		}
		catch (std::exception e)
		{

			Match(("VAR"));
		}
	}


	void Parser::if_expr()
	{
		if_head();
		if_body();
		if (currentToken->getTerminal().getIdentifier() == "ELSE_KW")
		{
			else_expr();
		}
	}


	void Parser::if_head()
	{
		Match("IF_KW");
		if_condition();
	}

	void Parser::if_condition()
	{
		Match("L_BR");
		logical_expr();
		Match("R_BR");
	}

	void Parser::if_body()
	{
		Match("L_S_BR");
		checkExpr();
		Match("R_S_BR");
	}

	void Parser::else_expr()
	{
		else_head();
		else_body();
	}

	void Parser::else_head()
	{
		Match("ELSE_KW");
	}

	void Parser::else_body()
	{
		Match("L_S_BR");
		checkExpr();
		Match("R_S_BR");
	}

	void Parser::logical_expr()
	{
		value_expr();
		Match("LOGICAL_OP");
		value_expr();
	}



	void Parser::checkExpr()
	{
		std::vector<std::string> firstSet = firstSets.at("expr");
		do
		{
			expr();
		} while (std::find(firstSet.begin(), firstSet.end(), currentToken->getTerminal().getIdentifier()) != firstSet.end());
	}

	void Parser::Match(std::string t)
	{
		IgnoreWhitespaces();

		if((currentToken++)->getTerminal().getIdentifier() == t)
		{
			IgnoreWhitespaces();
			return;
		}
		--currentToken;
		err("Unexpected token: " + currentToken->getTerminal().getIdentifier());
	}

	void Parser::IgnoreWhitespaces()
	{
		while (currentToken->getTerminal().getIdentifier() == "WS") ++currentToken;
		while (currentToken->getTerminal().getIdentifier() == "NLINE")
		{
			++currentToken;
			++line;
		}
	}

	void Parser::err(const std::string &message)
	{
		throw std::runtime_error(message ); //+ " at line " + std::to_string(line)
	}


	void Parser::Parse(Lexer lexer)
	{
		try
		{
			currentToken = lexer.tokens.begin();
			endToken = lexer.tokens.end();
			lang();
			std::cout << "Parser: success\n";
		}
		catch (std::exception exc)
		{
			std::cout << exc.what() << std::endl;
			exit(-2);
		}
	}




