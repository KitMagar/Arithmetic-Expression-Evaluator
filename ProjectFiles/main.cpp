#include <iostream>
#include <string>
#include <stack>   // cpp container, data structure called stack access using push and pop 
#include <cstring> // For isdigit(), strchr()
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include "errorhandler.h"
#include "main.h"

using namespace std;


/* CURRENT ISSUES:

CANNOT DO OPERATION 1+-5 (negative acceptance, should we ignore?)

weird observation: inputting an expression which does not crash after evaluation, allows all expressions thereafter to be properly evaluated
(maybe we should just secretly input one at the beginning and not display it lol)


Error Handler is called but the purpose is unclear.

-Phoenix
*/


// This function checks for unmatched parentheses in the input expression and logs errors using the ErrorHandler.
bool checkParentheses(const string &input, ErrorHandler &errorHandler) {
    stack<char> stack;
    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            if (stack.empty()) {
                errorHandler.unmatchedParenthesesError();
                return false;
            }
            stack.pop();
        }
    }
    if (!stack.empty()) {
        errorHandler.unmatchedParenthesesError();
        return false;
    }
    return true;
}


// This function validates the sequence of operators and operands in the input and logs errors for invalid sequences.
bool checkOperatorOperandSequence(const string &input, ErrorHandler &errorHandler) {
    bool expectOperand = true;
    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        // Check if the character is a digit
        if (c >= '0' && c <= '9') {
            expectOperand = false;
        }
        // Check if the character is a valid operator
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^') {
            if (expectOperand) {
                errorHandler.operatorWithoutOperandsError(string(1, c), i);
                return false;
            }
            expectOperand = true;
        }
        // Check for invalid characters (not digit, operator, or parentheses)
        else if (c != ' ' && c != '(' && c != ')') {
            errorHandler.invalidCharacterError(c, i);
            return false;
        }
    }
    // If the last character requires an operand, it's an error
    if (expectOperand) {
        errorHandler.missingOperandError();
        return false;
    }
    return true;
}

// Evaluation function
void evalCall(string userInput) {
    ErrorHandler errorHandler;

    // Perform pre-parsing checks for unmatched parentheses and invalid operator/operand sequences.
    if (!checkParentheses(userInput, errorHandler) || 
        !checkOperatorOperandSequence(userInput, errorHandler)) {
        errorHandler.displayErrors();
        return;
    }

    Lexer lex(userInput);
        //cout << "tokenizing";
        LinkedList l = lex.tokenize();
        //cout << "tokenized";
        l.print();
        

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
    } else {
        cout << "That is not a valid expression\n";
    }
    // 💣🔥💥
    //Currently commented out 
    //l.Cleanup();
}

int main() {
    bool quit = false;
    string userInput;

    cout << "Welcome to the arithmetic Evaluator" << endl;
    cout << "When you're ready to quit type \"QUIT\"" << endl;

    while (!quit) {
        cout << "What is your input: ";
        getline(cin, userInput);
        cout << endl;

        if (userInput == "QUIT") {
            break;
        }/*else{
            evalCall(userInput);
        }*/


        //passed all :)
        /*
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
        cin >> userInput;*/

        //FOR THE INVALID EXPRESSION TESTS 2 and 8 CRASH, BUT ALL PROVIDE A GENERIC RESPONSE
        /*
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
    }
}

/** First test cases using the error handler, division by zero is 
the only one working right now, below code is what I would compile 
but I kept the top alt + shift + a to comment out each section 
program.exe is the compile with error handler */


/* void evalCall(const string &userInput, ErrorHandler &errorHandler) {
    try {
        // Lexical Analysis
        Lexer lex(userInput);
        LinkedList l = lex.tokenize();
        l.print(); // Display tokens for debugging

        // Check for invalid tokens
        for (int i = 0; i < l.getLength(); i++) {
            if (l.getEntry(i).isChar && l.getEntry(i).entry.character == 'I') {
                errorHandler.invalidCharacterError(l.getEntry(i).entry.character, i);
                throw runtime_error("Invalid character in expression");
            }
        }

        // Parse and Evaluate
        if (!l.getEntry(0).isChar && l.getLength() == 1) {
            cout << l.getEntry(0).entry.value << "\n";
        } else {
            Parser parsed(l);
            Evaluator evaluated(parsed);
            cout << evaluated.evaluate() << "\n";
        }

    } catch (const exception &e) {
        errorHandler.logError(e.what());
        cout << "Error: " << e.what() << "\n";
    }
}

void runTestCases(ErrorHandler &errorHandler) {
    struct TestCase {
        string input;
        string expectedResult;
    };

    TestCase testCases[] = {
        {"3+4", "7"},
        {"8-(5-2)", "5"},
        {"10*2/5", "4"},
        {"2**3", "8"},
        {"4*(3+2)%7-1", "2"},
        {"(((2+3)))+(((1+2)))", "8"},
        {"((5*2)-((3/1)+((4%3))))", "7"},
        {"(((2**(1+1))+((3-1)**2))/((4/2)%3))", "5"},
        {"(((((5-3)))*(((2+1)))+((2*3))))", "11"},
        {"((9+6))/((3*1)/(((2+2)))-1)", "15"},
        {"4/0", "Error: Division by zero"},
        {"(((3+4)-2)+(1)", "Error: Mismatched parentheses detected"},
    };

    for (const auto &testCase : testCases) {
        cout << "Testing input: " << testCase.input << "\n";
        errorHandler.clearErrors();
        evalCall(testCase.input, errorHandler);

        cout << "Errors:" << endl;
        errorHandler.displayErrors();
        cout << "\n";
    }
}

int main() {
    ErrorHandler errorHandler;
    bool quit = false;
    string userInput;

    cout << "Welcome to the Arithmetic Evaluator" << endl;
    cout << "Type \"QUIT\" to exit, or press Enter to run test cases." << endl;

    while (!quit) {
        cout << "What is your input: ";
        getline(cin, userInput);

        if (userInput.empty()) {
            cout << "Running test cases...\n";
            runTestCases(errorHandler);
            break;
        }

        if (userInput == "QUIT") {
            quit = true;
            break;
        }

        evalCall(userInput, errorHandler);

        cout << "Errors encountered:" << endl;
        errorHandler.displayErrors();
        cout << "\n";
    }

    return 0;
}
 */