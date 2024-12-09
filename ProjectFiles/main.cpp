#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include "main.h"
using namespace std;

/*
CURRENT ISSUES:

DECIMAL INPUT AND '^' FOR THE EXPONENT IS CURRENTLY UNSUPPORTED (ALSO QUESTION, ARE WE SUPPORTING MODULUS (%)?)

SOMETIMES AFTER EVALUATION WE CRASH

INPUTTING THINGS AGAIN SIMPLY DOES NOT WORK SOMETIMES

weird observation: inputting an expression which does not crash after evaluation, allows all expressions thereafter to be properly evaluated
(maybe we should just secretly input one at the beginning and not display it lol)

And the destructors are commented out currently because I think they were causing me some issues, not quite sure?

-Phoenix
*/
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
        LinkedList l = lex.tokenize();
        l.print();

        if(l.getLength()>1){
            Parser parsed(l);
            Evaluator evaluated(parsed);
            cout << evaluated.evaluate() << "\n";
        }else if(!l.getEntry(0).isChar){
            cout << l.getEntry(0).entry.value << "\n";
        }else{
            cout << l.getEntry(0).entry.character << " Is not a valid expression\n";
        }

        // 💣🔥💥
        //Currently commented out 
        /*lex.~Lexer();
        parsed.~Parser();
        evaluated.~Evaluator();
        l.Cleanup();*/
        
    }
}