#include "Lexer.h"
#include <iostream>
#include <fstream>

using namespace std;

Lexer::Lexer()
{
}

Lexer::~Lexer()
{
}

void Lexer::Run()
{
    setlocale(LC_ALL, "ru");

    line = 0;

    string buffer;
    vector<string> lines;
    string path = "Code.txt";

    ifstream fin;
    fin.open(path);

    if (!fin.is_open()) {

        cout << "Ошибка открытия файла!" << endl;
    }
    else {
        cout << "Открыт!" << endl;
        char ch;
        while (!fin.eof()) {
            getline(fin, buffer);
            lines.push_back(buffer);
        }
    }
    fin.close();

    for (size_t i = 0; i < lines.size(); i++)
    {
        string input = lines[i];
        while (input != "")
        {
            if (input.at(0) == '\n')
            {
                ++line;
            }

            Lexeme token = ExtractNextToken(input);
            tokens.push_back(token);

            input = input.substr(token.getValue().length(), input.length());
        }
        line++;
    }
    tokens.push_back(Lexeme(Terminal("EOF", ""), ""));

    print(tokens);
}

bool Lexer::AnyTerminalMatches(string str)
{
    return lookupTerminals(str).size() != 0;
}



vector<Terminal> Lexer::lookupTerminals(string str)
{
    vector<Terminal> matched;
    for (auto terminal : TERMINALS)
    {
        if (terminal.Matches(str))
        {
            matched.push_back(terminal);
        }
    }
    return matched;
}



Terminal Lexer::GetPrioritizedTerminal(std::vector<Terminal> terminals)
{
    Terminal prioritized = terminals.at(0);

    for (auto terminal : terminals)
    {
        if (terminal.getPriority() > prioritized.getPriority())
        {
            prioritized = terminal;
        }
    }
    return prioritized;
}



void Lexer::print(vector<Lexeme> lexemes)
{
    std::cout << "Lexer: success\n\nTokens:\n";

    for (auto& token : tokens)
    {
        std::cout << token.ToString() << "\n";
    }
    std::cout << "\n\n\n";
    
}

Lexeme Lexer::ExtractNextToken(string input)
{
    std::string buffer;

    buffer.push_back(input.at(0));
    try {
        if (AnyTerminalMatches(buffer))
        {
            while (AnyTerminalMatches(buffer) && buffer.length() != input.length())
            {
                buffer.push_back(input.at(buffer.length()));
            }

            if (buffer.length() != input.length() || !AnyTerminalMatches(buffer))
                buffer.pop_back();

            std::vector<Terminal> terminals = lookupTerminals(buffer);

            return Lexeme(GetPrioritizedTerminal(terminals), buffer);
        }
        else
        {
            std::string err = "Unexpected symbol at line " + std::to_string(line);
            throw std::runtime_error(err);
        }
    }
    catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        exit(-1);
    }
}

