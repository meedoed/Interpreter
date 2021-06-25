#ifndef LEXER_H
#define LEXER_H
#include "Lexeme.h"
#include "Terminal.h"
#include <list>
#include <string>


class lexer
{
public:
    lexer();
    virtual ~lexer();
    void Run(string str);
    list<string> token;

protected:

private:
    const list<Terminal> TERMINALS = {
       Terminal("VAR", "[a-zA-Z][a-zA-Z0-9]*",0),
       Terminal("ASSIGN_OP", "=",0),
       Terminal("NUMBER", "0|([1-9][0-9]*)",0),
       Terminal("OP", "+|-|*|/", 0),
       Terminal("L_BR","(",0),
       Terminal("R_BR",")",0),
       Terminal("L_S_BR","{",0),
       Terminal("R_S_BR","}",0),
       Terminal("SC",";",0),
       Terminal("LOGICAL_OP","> | <",0),
       Terminal("IF_KW","if",1),
       Terminal("ELSE_KW","else",1)
    };
};

#endif // LEXER_H