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
        vector<Token> tokenize() {
            vector<Token> tokens;

            while (pos < input.length()) {
                char current = input[pos];

                if (isspace(current)) {
                    pos++;
                    continue;
                }
                else if (isdigit(current)) {
                    tokens.push_back(Token(TokenType::Constant, parseConstant()));
                }
                else if (current == '(') {
                    tokens.push_back(Token(TokenType::LeftParen));
                    pos++;
                }
                else if (current == ')') {
                    tokens.push_back(Token(TokenType::RightParen));
                    pos++;
                }
                else if (current == '+') {
                    tokens.push_back(Token(TokenType::Plus));
                    pos++;
                }
                else if (current == '-') {
                    tokens.push_back(Token(TokenType::Minus));
                    pos++;
                }
                else if (current == '*') {
                    if (input[pos+1] == '*' && pos+1 < input.length()) {
                        tokens.push_back(Token(TokenType::Exponent));
                        pos++;
                        pos++;
                    }
                    else {
                        tokens.push_back(Token(TokenType::Multiply));
                        pos++;
                    }
                }
                else if (current == '/') {
                    tokens.push_back(Token(TokenType::Divide));
                    pos++;
                }
                else if (current == '%') {
                    tokens.push_back(Token(TokenType::Modulo));
                    pos++;
                }
                else {
                    tokens.push_back(Token(TokenType::Invalid, string(1, current)));
                    pos++;
                }
            }
            tokens.push_back(Token(TokenType::End));
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

string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::Constant:
            return "Constant";
        case TokenType::LeftParen:
            return "LeftParen";
        case TokenType::RightParen:
            return "RightParen";
        case TokenType::Plus:
            return "Plus";
        case TokenType::Minus:
            return "Minus";
        case TokenType::Exponent:
            return "Exponent";
        case TokenType::Multiply:
            return "Multiply";
        case TokenType::Divide:
            return "Divide";
        case TokenType::Modulo:
            return "Modulo";
        case TokenType::End:
            return "End";
        case TokenType::Invalid:
            return "Invalid";
    }
    return 0;
}
