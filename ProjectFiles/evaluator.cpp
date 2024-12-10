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
#include "evaluator.h"

using namespace std;
	
	// UNDER THE HOOD 🚗
		//BinaryNode *root; // root is a pointer that points to the root BinaryNode
		//ErrorHandler errorH; // errorH is a var of ErrorHandler type that allows us to throw errors

		//evaluateNode is a method that takes in a BinaryNode pointer 
double Evaluator::evaluateNode(BinaryNode *node) {

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
		return entry.entry.value;
	}

	// Evaluate left and right subtrees
	double leftValue = evaluateNode(node->left);
	double rightValue = evaluateNode(node->right);

	// Get the operator
	char op = node->entry.getEntry(0).entry.character;

	// HERE WE DETERMINE WHAT OPERATION IS EXECUTED
	switch (op) {
		// Addition
		case '+':
			return leftValue + rightValue;
		// Subtraction
		case '-':
			return leftValue - rightValue;
		// Multiplication
		case '*':
			return leftValue * rightValue;
		// Division
		case '/':
			// Ensure DIVBY0 is handled properly
			if (rightValue == 0) {
				errorH.divisionByZeroError();
				throw runtime_error("Division by zero"); // NEEDS TO BE CHANGED AT SOME POINT MAYBE
			}
			return leftValue / rightValue;
		// Modulus
		case '%':
			// Ensure DIVBY0 is handled properly
			if (rightValue == 0) {
				errorH.divisionByZeroError();
				throw runtime_error("Division by zero"); // NEEDS TO BE CHANGED AT SOME POINT MAYBE
			}
			return fmod(leftValue, rightValue);
		// Exponent
		case '^':
			return pow(leftValue, rightValue);
		// If none of the above we throw an error
		default:
			errorH.incorrectOperatorUsageError();
			throw runtime_error("Unknown operator"); // NEEDS TO BE CHANGED AT SOME POINT MAYBE
	}
}

// DECONSTRUCTOR
void Evaluator::deleteTree(BinaryNode* node) {
	if (node!= nullptr) {
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}

// WHAT Y'ALL CAN LOOK AT 😀
// PUBLIC CONSTRUCTOR METHOD
Evaluator::Evaluator(Parser &rootNode) : root(rootNode.root) {}
double Evaluator::evaluate() {
	return evaluateNode(root);
}

// PUBLIC DECONSTRUCTOR METHOD
Evaluator::~Evaluator() {
	deleteTree(root);
	root = nullptr;
}