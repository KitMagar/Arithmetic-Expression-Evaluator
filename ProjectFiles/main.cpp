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
        cout << "Lex";
        cin >> waitVar;
        cout << "Input accepted";
        LinkedList l = lex.tokenize();

            //DEBUG SECTION

                        for(int i=0;i<l.getLength();i++){ //This will be used for debugging


                            //This is how we handle if linked list has characters or numbers
                            if(l.getEntry(i).isChar){ 
                                cout << l.getEntry(i).entry.character << "C\n";
                            }else{
                                cout << l.getEntry(i).entry.value << "V\n";
                            }
                        }
            //IF WE MAKE IT OUT OF THE LOOP TOKENIZER WORKS



        Parser parsed(lex.tokenize());
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
    }
}