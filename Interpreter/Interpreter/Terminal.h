#ifndef TERMINAL_H
#define TERMINAL_H
#include <string>
#include <regex>

using namespace std;

class Terminal
{
public:
    Terminal(string identifier, string pattern, int priority);
    Terminal(string identifier, string pattern);
    Terminal();
    virtual ~Terminal();
    bool Matches(string Str);
    string getIdentifier();
    int getPriority();


private:
    int priority;
    string identifier;
    regex pattern;

};

#endif // TERMINAL_H