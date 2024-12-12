#ifndef LEXER_H
#define LEXER_H

#include "dataStruct.h"
#include "errorhandler.h"
#include <string>
using namespace std;

class Lexer {
    public:
        explicit Lexer(const string& input);
        LinkedList tokenize(ErrorHandler &errorH);

    private:
        string input;
        int pos;

        string parseConstant();
};

#endif