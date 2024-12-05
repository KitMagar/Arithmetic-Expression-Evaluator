#ifndef LEXER_H
#define LEXER_H

#include "dataStruct.h"
#include <string>
using namespace std;

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
