#ifndef LEXEME_H
#define LEXEME_H
#include "Terminal.h"

class Lexeme
{
public:
    Lexeme(Terminal terminal, string value);
    virtual ~Lexeme();
    Terminal getTerminal();
    string getValue();
    string ToString()
    {
        return "[" + terminal.getIdentifier() + ", " + value + "]";
    }

private:
    Terminal terminal;
    string value;

};

#endif // LEXEME_H
