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
        string waitVar;
        Lexer lex(userInput);
        cout << "Lex\n";
        cin >> waitVar;
        cout << "Input accepted\n";

        LinkedList l = lex.tokenize();

            //DEBUG SECTION
            l.print();
            //IF WE MAKE IT OUT OF THE LOOP TOKENIZER WORKs


        Parser parsed(l);
        cout << "Parse";
        cin >> waitVar;
        cout << "Input accepted";
        Evaluator evaluated(parsed);
        cout << "Eval";
        cin >> waitVar;
        cout << "Input accepted";
        cout << evaluated.evaluate();
        // 💣🔥💥
        lex.~Lexer();
        parsed.~Parser();
        evaluated.~Evaluator();
        l.Cleanup();
    }
}