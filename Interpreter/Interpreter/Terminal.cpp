#include "Terminal.h"

Terminal::Terminal(string identifier, string pattern, int priority)
{
    this->identifier = identifier;
    this->pattern = regex(pattern);
    this->priority = priority;
}

Terminal::Terminal()
{
}

Terminal::Terminal(string identifier, string pattern)
{
    this->identifier = identifier;
    this->pattern = regex(pattern);
    this->priority = 0;
}


Terminal::~Terminal()
{
    //dtor
}

bool Terminal::Matches(string Str) {
    return regex_match(Str, pattern);

}

int Terminal::getPriority() {
    return priority;
}

string Terminal::getIdentifier() {
    return identifier;
}

