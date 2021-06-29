#include "Lexeme.h"

Lexeme::Lexeme(Terminal terminal, string value)
{
    this->terminal = terminal;
    this->value = value;
}

Lexeme::~Lexeme()
{
    //dtor
}

Terminal Lexeme::getTerminal() {
    return terminal;
}

string Lexeme::getValue() {
    return value;
}

