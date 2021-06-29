#ifndef Lexer_H
#define Lexer_H
#include "Lexeme.h"
#include "Terminal.h"
#include <string>
#include <vector>


class Lexer
{
public:
    Lexer();
    virtual ~Lexer();
    void Run();

    vector<Lexeme> tokens;

protected:

private:
    const vector<Terminal> TERMINALS = {
       Terminal("VAR", "[a-zA-Z][a-zA-Z0-9]*"),
       Terminal("ASSIGN_OP", "="),
       Terminal("NUMBER", "0|([1-9][0-9]*)"),
       Terminal("OP", "\\+|\\-|\\*|\\/", 0),
       Terminal("L_BR","\\("),
       Terminal("R_BR","\\)"),
       Terminal("L_S_BR","\\{",0),
       Terminal("R_S_BR","\\}",0),
       Terminal("SC",";",0),
       Terminal("LOGICAL_OP",">|<", 2),
       Terminal("IF_KW","if",1),
       Terminal("WS", "[\\t\\r ]+"),
       Terminal("NLINE", "\\n", 1),
       Terminal("ELSE_KW","else",1)
    };
    int line;
    bool AnyTerminalMatches(string buffer);
    vector<Terminal> lookupTerminals(string buffer);
    Terminal GetPrioritizedTerminal(std::vector<Terminal> terminals);
    void print(vector<Lexeme> lexemes);
    Lexeme ExtractNextToken(string input);
};

#endif // Lexer_H