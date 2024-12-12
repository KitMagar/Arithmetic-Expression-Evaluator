#include <iostream>
#include <string>
#include <cctype>
#include "dataStruct.h"
#include "lexer.h"

using namespace std;

// Change pos to size_t to match input.length(), which is unsigned.
Lexer::Lexer(const string& input) : input(input), pos(0) {} 

LinkedList Lexer::tokenize() {
    LinkedList tokens;
    double neg = -1;

    while (pos < input.length()) { // No changes needed here; pos is now size_t.
        char current = input[pos];

        if (isspace(current)) {
            pos++;
            continue;
        }
        else if (isdigit(current) || current == '.') {
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
            if (pos == 0) {
                pos++;
                continue;
            }
            else {
                if (input[pos - 1] == '(') {
                    pos++;
                    continue;
                }
                else {
                    tokens.insert('+', tokens.getLength());
                    pos++;
                }
            }
        }
        else if (current == '-') {
            if (pos == 0) {
                if (pos + 1 < input.length() && isdigit(input[pos + 1])) {
                    pos++;
                    string constant = parseConstant();
                    tokens.insert(stod(constant) * (-1), tokens.getLength());
                }
                else if (pos + 1 < input.length() && input[pos + 1] == '(') {
                    tokens.insert(neg, tokens.getLength());
                    tokens.insert('*', tokens.getLength());
                    pos++;
                }
            }
            else {
                if (pos + 1 < input.length() && isdigit(input[pos + 1]) && input[pos - 1] == '(' && input[pos + 1] != '(') {
                    pos++;
                    string constant = parseConstant();
                    tokens.insert(stod(constant) * (-1), tokens.getLength());
                }
                else if (pos + 1 < input.length() && input[pos - 1] == '(' && input[pos + 1] == '(') {
                    tokens.insert(neg, tokens.getLength());
                    tokens.insert('*', tokens.getLength());
                    pos++;
                }
                else {
                    tokens.insert('-', tokens.getLength());
                    pos++;
                }
            }
        }
        else if (current == '*') {
            if (pos + 1 < input.length() && input[pos + 1] == '*') {
                tokens.insert('^', tokens.getLength());
                pos++;
                pos++;
            }
            else {
                tokens.insert('*', tokens.getLength());
                pos++;
            }
        }
        else if(current == '^'){
            tokens.insert('^', tokens.getLength());
            pos++;
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
            // invalid entry
            tokens.insert('I', tokens.getLength());
            pos++;
        }
    }
    return tokens;
}

string Lexer::parseConstant() {
    size_t start = pos; // Change start to size_t for consistency with pos.
    while (pos < input.length() && (isdigit(input[pos]) || input[pos] == '.')) {
        pos++;
    }
    return input.substr(start, pos - start); // No changes needed here.
}