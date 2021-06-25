// Interpreter.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Terminal.h"
#include <fstream>



int main()
{
    setlocale(LC_ALL, "ru");

    string path = "Code.txt";

    ifstream fin;
    fin.open(path);
    
    if (!fin.is_open()) {

        cout << "Ошибка открытия файла!" << endl;
    }
    else {
        cout << "Открыт!" << endl;
        char ch;
        while (fin.get(ch)) {
            cout << ch;
        }
    }
    fin.close();

    return 0;
}

