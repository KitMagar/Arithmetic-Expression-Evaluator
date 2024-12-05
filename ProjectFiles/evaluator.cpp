// evaluator.cpp
// Aiden's Task
// Created on Dec 5 @ 1230am
//
// Objective: Traverse the expression tree built by parser & evaluate it to produce the final result
//
// Implement support for basic operators (+,-,*,/,%,**) and ensure proper handling of operator precedence
// Handle division by 0 errors and other invalid expressions

#include "dataStruct.h"
#include "parser.h"
#include "errorhandler.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

using namespace std;

// Assuming BinaryNode structure is accessible
// If not, move the BinaryNode definition to a shared header file

class Evaluator {
	
	// UNDER THE HOOD 🚗
	private:
		BinaryNode *root; // root is a pointer that points to the root BinaryNode
		ErrorHandler errorH; // errorH is a var of ErrorHandler type that allows us to throw errors

		//evaluateNode is a method that takes in a BinaryNode pointer 
		double evaluateNode(BinaryNode *node) {

			// We want a valid pointer
			// If node is a null pointer 👎🏼 then we throw an ✨error✨
			if (node == nullptr) {
				errorH.incorrectOperatorUsageError(); //Null Node Error
				throw runtime_error("Null node encountered");
			}

			// If the node is a leaf node 🍃 (operand)
			if (node->left == nullptr && node->right == nullptr) {
				auto entry = node->entry.getEntry(0);
				if (entry.isChar) {
					errorH.incorrectOperatorUsageError(); //Invalid Operand Error
					throw runtime_error("Invalid operand");
				}
				return entry.value;
			}

			// Evaluate left and right subtrees
			double leftValue = evaluateNode(node->left);
			double rightValue = evaluateNode(node->right);

			// Get the operator
			char op = node->entry.getEntry(0).character;

			// Perform the operation
			switch (op) {
				case '+':
					return leftValue + rightValue;
				case '-':
					return leftValue - rightValue;
				case '*':
					return leftValue * rightValue;
				case '/':
					if (rightValue == 0) {
						errorH.divisionByZeroError();
						throw runtime_error("Division by zero");
					}
					return leftValue / rightValue;
				case '%':
					if (rightValue == 0) {
						errorH.divisionByZeroError();
						throw runtime_error("Division by zero");
					}
					return fmod(leftValue, rightValue);
				case '^':
					return pow(leftValue, rightValue);
				default:
					errorH.incorrectOperatorUsageError();
					throw runtime_error("Unknown operator");
			}
		}

	// WHAT Y'ALL CAN LOOK AT 😀
	public:
		Evaluator(BinaryNode *rootNode) : root(rootNode) {}

		double evaluate() {
			return evaluateNode(root);
		}
};

// Usage example (to be adapted based on actual implementation)

/*
int main() {
	// Assume parser has been used to build the expression tree
	Parser parser(inputLinkedList);
	BinaryNode *expressionTreeRoot = parser.getRoot();

	Evaluator evaluator(expressionTreeRoot);
	try {
		double result = evaluator.evaluate();
		cout << "The result is: " << result << endl;
	} catch (const runtime_error &e) {
		cout << "Evaluation error: " << e.what() << endl;
	}

	return 0;
}
*/

