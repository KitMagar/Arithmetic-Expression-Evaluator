#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include "main.h"
using namespace std;

int main(){
    bool quit = false;
    string userInput;
    cout << "Welcome to the arithmetic Evaluator" << endl;
    cout << "When you're ready to quit type \"QUIT\"" << endl;
    while(!quit){
        cout << "What is your input: ";
        cin >> userInput;
        cout << endl;
        
        if(userInput == "QUIT"){
            break;
        }
        
        Lexer lex(userInput);
        Parser parsed(lex.tokenize());
        Evaluator evaluated(parsed);
        cout << evaluated.evaluate();
        // 💣🔥💥
        lex.~Lexer();
        parsed.~Parser();
        evaluated.~Evaluator();
    }
}