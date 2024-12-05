#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

enum class TokenType {
    LeftParen,
    RightParen,
    Plus,
    Minus,
    Multiply,
    Divide,
    Modulo,
    Exponent,
    Constant,
    Invalid,
    End
};

struct Token {
    TokenType type;
    string value;

    Token(TokenType type, string value = "") : type(type), value(value) {}
};

class Lexer {
    public:
        explicit Lexer(const string& input) : input(input), pos(0) {}
        vector<Token> tokenize();

    private:
        string input;
        int pos;

        string parseConstant();
};

string tokenTypeToString(TokenType type);

#endif