#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <cctype>
#include "dataStruct.h"

class Lexer {
    public:
        explicit Lexer(const string& input) : input(input), pos(0) {}
        LinkedList tokenize();

    private:
        string input;
        int pos;

        string parseConstant();
};

#endif
