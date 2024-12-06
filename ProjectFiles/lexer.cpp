#include <iostream>
#include <string>
#include <cctype>
#include "dataStruct.h"
#include "lexer.h"

using namespace std;
Lexer::Lexer(const string& input) : input(input), pos(0) {}
LinkedList Lexer::tokenize() {
    LinkedList tokens;

    while (pos < input.length()) {
        char current = input[pos];

        if (isspace(current)) {
            pos++;
            continue;
        }
        else if (isdigit(current)) {
            string constant = parseConstant();
            tokens.insert(stod(constant), tokens.getLength());
        }
        else if (current == '(') {
            tokens.insert('(', tokens.getLength());
            pos++;
        }
        else if (current == ')') {
            tokens.insert(')', tokens.getLength());
            pos++;
        }
        else if (current == '+') {
            tokens.insert('+', tokens.getLength());
            pos++;
        }
        else if (current == '-') {
            tokens.insert('-', tokens.getLength());
            pos++;
        }
        else if (current == '*') {
            if (input[pos+1] == '*' && pos+1 < input.length()) {
                tokens.insert('^', tokens.getLength());
                pos++;
                pos++;
            }
            else {
                tokens.insert('*', tokens.getLength());
                pos++;
            }
        }
        else if (current == '/') {
            tokens.insert('/', tokens.getLength());
            pos++;
        }
        else if (current == '%') {
            tokens.insert('%', tokens.getLength());
            pos++;
        }
        else {
            //invalid entry
            tokens.insert('I', tokens.getLength());
            pos++;
        }
    }
    return tokens;
}

string Lexer::parseConstant() {
    int start = pos;
    while (pos < input.length() && isdigit(input[pos])) {
        pos++;
    }
    return input.substr(start, pos - start);
}
