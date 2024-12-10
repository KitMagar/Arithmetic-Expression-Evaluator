#include <iostream>
#include <string>
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include "main.h"
using namespace std;

/*
CURRENT ISSUES:

CANNOT DO OPERATION 1+-5 (negative acceptance, should we ignore?)

weird observation: inputting an expression which does not crash after evaluation, allows all expressions thereafter to be properly evaluated
(maybe we should just secretly input one at the beginning and not display it lol)


Error Handler is called but the purpose is unclear.

-Phoenix
*/


void evalCall(string userInput){
    Lexer lex(userInput);
        //cout << "tokenizing";
        LinkedList l = lex.tokenize();
        //cout << "tokenized";
        //l.print();
        

        bool invalid = false;

        for(int i=0; i<l.getLength();i++){
            if(l.getEntry(i).isChar){
                if(l.getEntry(i).entry.character == 'I'){
                    invalid = true;
                    break;
                }
            }
        }
        
        if(!invalid){
            if(!l.getEntry(0).isChar && l.getLength()==1){
                cout << l.getEntry(0).entry.value << "\n";

            }else if(l.getLength()==3 && l.getEntry(0).entry.character == '(' && l.getEntry(l.getLength()-1).entry.character == ')'){
                l.remove(0);
                l.remove(l.getLength()-1);
                cout << l.getEntry(0).entry.value << "\n";
            }else if(l.getLength()>1){
                try{
                    Parser parsed(l);
                    Evaluator evaluated(parsed);
                    cout << evaluated.evaluate() << "\n";
                }
                catch(...){
                    cout << "That is not a valid expression\n";
                }

            }
        }else{
            cout << "That is not a valid expression\n";
        }

        // 💣🔥💥
        //Currently commented out 
        l.Cleanup();
        
}



int main(){
    bool quit = false;
    string userInput;
    cout << "Welcome to the arithmetic Evaluator" << endl;
    cout << "When you're ready to quit type \"QUIT\"" << endl;

    /*
    This below is stupid, but I have no idea why, but the destructor for evaluator will cause a crash if we don't use this (I can't figure out a pattern) expression on the first use.

    But after we evluate this once, it works perfectly fine from then on with no more crashing. If we can figure out why that would be great.
    */
    //1+9(7+3)
    LinkedList startExp;
    startExp.insert(1.0, 0); startExp.insert('+', 1); startExp.insert(9.0, 2); startExp.insert('(', 3); startExp.insert(7.0, 4); startExp.insert('+', 5); startExp.insert(3.0, 6); startExp.insert(')', 7);
    Parser p(startExp);
    Evaluator e(p);
    e.evaluate();
    startExp.Cleanup();
    while(!quit){
        cout << "What is your input: ";
        getline(cin, userInput);
        cout << endl;
        
        if(userInput == "QUIT"){
            break;
        }
        evalCall("3+4");
        cin >> userInput;
        evalCall("8-(5-2)");
        cin >> userInput;
        evalCall("10*2/5");
        cin >> userInput;
        evalCall("2**3");
        cin >> userInput;
        evalCall("4*(3+2)%7-1");
        cin >> userInput;
        evalCall("(((2+3)))+(((1+2)))");
        cin >> userInput;
        evalCall("((2*2)-((3/1)+((4%3))))");
        cin >> userInput;
        evalCall("(((2**(1+1))+((3-1)**2))/((4/2)%3))");
        cin >> userInput;
        evalCall("(((((5-3)))*(((2+1)))+((2*3))))");
        cin >> userInput;
        evalCall("((9+6))/((3*1)/(((2+2)))-1)");
        cin >> userInput;
        evalCall("+(-2)*(-3)-((-4)/(+5))");
        cin >> userInput;
        evalCall("-(+1)+(+2)");
        cin >> userInput;
        evalCall("-(-(-3))+(-4)+(+5)");
        cin >> userInput;
        evalCall("+2**(-3)");
        cin >> userInput;
        evalCall("-(+2)*(+3)-(-4)/(-5)");
        cin >> userInput;
    }
}
