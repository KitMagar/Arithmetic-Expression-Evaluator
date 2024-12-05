#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
using namespace std;

int main(){
    bool quit = false;
    string userInput;
    cout << "Welcome to the arithmetic Evaluator\n";
    while(!quit){
        cout << "What is your input: \n";
        cin >> userInput;
        Lexer lex(userInput);
        Parser parsed(lex.tokenize());
        Evaluator evaluated(parsed);
        cout << evaluated.evaluate();
        ~lex();
        ~parsed();
        ~evaluated();
    }
}