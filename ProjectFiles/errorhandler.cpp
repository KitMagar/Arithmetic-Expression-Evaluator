#include "errorhandler.h"
#include <iostream>

// Adds a new error message to the list
void ErrorHandler::logError(const std::string& message) {
    errorMessages.push_back(message);
}

// Returns true if there are errors
bool ErrorHandler::hasErrors() const {
    return !errorMessages.empty();
}

// Prints all error messages to the console
void ErrorHandler::displayErrors() const {
    for (const std::string& message : errorMessages) {
        std::cout << "Error: " << message << std::endl;
    }
}

// Clears all logged errors
void ErrorHandler::clearErrors() {
    errorMessages.clear();
}

// Specific error handling functions
void ErrorHandler::unmatchedParenthesesError() {
    logError("Unmatched parentheses detected. Check for missing opening or closing parentheses.");
}

void ErrorHandler::operatorWithoutOperandsError(const std::string& operatorSymbol, int position) {
    logError("Operator '" + operatorSymbol + "' at position " + std::to_string(position) + " does not have valid operands.");
}

void ErrorHandler::incorrectOperatorUsageError() {
    logError("Incorrect operator usage detected.");
}

void ErrorHandler::missingOperatorError() {
    logError("Missing operator in the expression. Check for implicit multiplication or misplaced numbers.");
}

void ErrorHandler::invalidCharacterError(char character, int position) {
    logError("Invalid character '" + std::string(1, character) + "' at position " + std::to_string(position) + ".");
}

void ErrorHandler::mismatchedParenthesesError() {
    logError("Mismatched parentheses detected. Check for balanced parentheses.");
}

void ErrorHandler::divisionByZeroError() {
    logError("Division by zero is not allowed.");
}

void ErrorHandler::invalidOperatorSequenceError() {
    logError("Invalid operator sequence detected. Check if operators are correctly placed between operands.");
}

void ErrorHandler::missingOperandError() {
    logError("Missing operand detected. Check if all operators have valid operands.");
}

void ErrorHandler::invalidCharactersError(const std::string& characterSequence, int position) {
    logError("Invalid character sequence '" + characterSequence + "' starting at position " + std::to_string(position) + ".");
}