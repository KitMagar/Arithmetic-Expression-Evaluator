#include <iostream>
#include <string>
#include <cctype>
#include "dataStruct.h"

using namespace std;

class Lexer {
    public:
        explicit Lexer(const string& input) : input(input), pos(0) {}
        LinkedList tokenize() {
            LinkedList tokens;

            while (pos < input.length()) {
                char current = input[pos];

                if (isspace(current)) {
                    pos++;
                    continue;
                }
                else if (isdigit(current)) {
                    string constant = parseConstant();
                    tokens.insert(stod(constant), pos);
                    pos++;
                }
                else if (current == '(') {
                    tokens.insert('(', pos);
                    pos++;
                }
                else if (current == ')') {
                    tokens.insert(')', pos);
                    pos++;
                }
                else if (current == '+') {
                    tokens.insert('+', pos);
                    pos++;
                }
                else if (current == '-') {
                    tokens.insert('-', pos);
                    pos++;
                }
                else if (current == '*') {
                    if (input[pos+1] == '*' && pos+1 < input.length()) {
                        tokens.insert('^', pos);
                        pos++;
                        pos++;
                    }
                    else {
                        tokens.insert('*', pos);
                        pos++;
                    }
                }
                else if (current == '/') {
                    tokens.insert('/', pos);
                    pos++;
                }
                else if (current == '%') {
                    tokens.insert('%', pos);
                    pos++;
                }
                else {
                    //invalid entry
                    tokens.insert('I', pos);
                    pos++;
                }
            }
            //end of input
            tokens.insert('E', pos);
            return tokens;
        }

    private:
        string input;
        int pos;

        string parseConstant() {
            int start = pos;
            while (pos < input.length() && isdigit(input[pos])) {
                pos++;
            }
            return input.substr(start, pos - start);
        }
};
