#include <iostream>
#include <string>
#include <stack>   // cpp container, data structure called stack access using push and pop 
#include <cstring> // For isdigit()
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include "errorhandler.h"
#include "main.h"

using namespace std;

void evalCall(string userInput);
void test();

int main() {
    bool quit = false;
    string userInput;

    cout << "Welcome to the arithmetic Evaluator" << endl;
    cout << "When you're ready to quit type \"QUIT\"" << endl;

    while (!quit) {
        cout << "What is your input: ";
        getline(cin, userInput);
        if(userInput == ""){
            cout << "\nCannot do an evaluation with an empty expression\n";
            continue;
        }
        cout << endl;

        if (userInput == "QUIT") {
            break;
        }else if(userInput== "TEST"){
            test();
        }else{
            evalCall(userInput);
        }
    }

    return 0;
}

// Evaluation function
void evalCall(string userInput) {
    ErrorHandler errorHandler;

    Lexer lex(userInput);
    //cout << "tokenizing";
    LinkedList l = lex.tokenize(errorHandler);
    //cout << "tokenized";
    //l.print();

    // Validation of tokens
    bool invalid = false;
    bool operatorOnly = true;
    for (int i = 0; i < l.getLength(); i++) {
        if(!l.getEntry(i).isChar){//this will deal with expressions which are ONLY operators
            operatorOnly = false;
        }
        if (l.getEntry(i).isChar && l.getEntry(i).entry.character == 'I') {
            invalid = true;
            break;
        }
    }

    if (!invalid && !operatorOnly) {
        if (!l.getEntry(0).isChar && l.getLength() == 1) {
            cout << l.getEntry(0).entry.value << "\n";
        } else if (l.getLength() == 3 && l.getEntry(0).entry.character == '(' && l.getEntry(l.getLength() - 1).entry.character == ')') {
            l.remove(0);
            l.remove(l.getLength() - 1);
            cout << l.getEntry(0).entry.value << "\n";
        } else if (l.getLength() > 1) {
            try {
                Parser parsed(l);
                Evaluator evaluated(parsed);
                cout << evaluated.evaluate() << "\n";
            } catch (const exception &e) {
                errorHandler.logError(e.what());
                errorHandler.displayErrors();
            } catch (...) {
                errorHandler.logError("Unknown error occurred.");
                errorHandler.displayErrors();
            }
        }
    } else if(invalid && !operatorOnly){
            errorHandler.displayErrors();
    }else{
        errorHandler.invalidOperatorSequenceError();
        errorHandler.displayErrors();
    }
}

//TEST CASES
void test(){
    string userInput;
    evalCall("3+4"); //1
    cin >> userInput;
    evalCall("8-(5-2)"); //2
    cin >> userInput;
    evalCall("10*2/5"); //3
    cin >> userInput;
    evalCall("2**3"); //4
    cin >> userInput;
    evalCall("4*(3+2)%7-1"); //5
    cin >> userInput;
    evalCall("(((2+3)))+(((1+2)))"); //6
    cin >> userInput;
    evalCall("((5*2)-((3/1)+((4%3))))"); //7
    cin >> userInput;
    evalCall("(((2**(1+1))+((3-1)**2))/((4/2)%3))"); //8
    cin >> userInput;
    evalCall("(((((5-3)))*(((2+1)))+((2*3))))"); //9
    cin >> userInput;
    evalCall("((9+6))/((3*1)/(((2+2)))-1)"); //10
    cin >> userInput;
    evalCall("+(-2)*(-3)-((-4)/(+5))"); //11
    cin >> userInput;
    evalCall("-(+1)+(+2)"); //12
    cin >> userInput;
    evalCall("-(-(-3))+(-4)+(+5)"); //13
    cin >> userInput;
    evalCall("+2**(-3)"); //14
    cin >> userInput;
    evalCall("-(+2)*(+3)-(-4)/(-5)"); //15
    cin >> userInput;

    //FOR THE INVALID EXPRESSION TESTS 2 and 8 CRASH, BUT ALL PROVIDE A GENERIC RESPONSE
    cout << "\n\nINVALID TESTS\n\n";
    evalCall("2*(4+3-1"); //1 
    cin >> userInput;
    evalCall("*5+2"); //2
    cin >> userInput;
    evalCall("4/0"); //3
    cin >> userInput;
    evalCall("5(2+3)"); //4 (PASSES BECAUSE OF ADVANCED FEATURE)
    cin >> userInput;
    evalCall("7&3"); //5
    cin >> userInput;
    evalCall("(((3+4)-2)+(1)"); //6
    cin >> userInput;
    evalCall("((5+2)/(3*0))"); //7
    cin >> userInput;
    evalCall("((2-)1+3)"); //8
    cin >> userInput;
    evalCall("((4*2)+(-))"); //9
    cin >> userInput;
    evalCall("((7*3)^2)"); //10 (PASSES BECAUSE OF ADVANCED FEATURE)
    cin >> userInput;
    cout << "TESTS COMPLETE\n";
}
