// Interpreter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Terminal.h"
#include "Lexer.h"
#include <fstream>
#include "Parser.h"

int main()
{
    Lexer lexer;
    Parser parser;

    lexer.Run();
    parser.Parse(lexer);
    return 0;
}

