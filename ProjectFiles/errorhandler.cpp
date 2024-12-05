#include "errorhandler.h"
#include <iostream>
#include <string>

ErrorHandler::ErrorHandler() : errorCount(0) {}

void ErrorHandler::logError(const std::string& message) {
    if (errorCount < MAX_ERRORS) {
        errorMessages[errorCount++] = message;
    } else {
        std::cerr << "Error log overflow: Cannot log more errors." << std::endl;
    }
}

void ErrorHandler::displayErrors() const {
    if (errorCount == 0) {
        std::cout << "No errors detected." << std::endl;
        return;
    }
    for (int i = 0; i < errorCount; ++i) {
        std::cout << "Error: " << errorMessages[i] << std::endl;
    }
}

void ErrorHandler::clearErrors() {
    errorCount = 0;
}

void ErrorHandler::unmatchedParenthesesError() {
    logError("Unmatched parentheses detected. Check for missing opening or closing parentheses.");
}

void ErrorHandler::operatorWithoutOperandsError(const std::string& operatorSymbol, int position) {
    std::string error = "Operator '" + operatorSymbol + "' at position " + std::to_string(position) + " does not have valid operands.";
    logError(error);
}

void ErrorHandler::incorrectOperatorUsageError() {
    logError("Incorrect operator usage detected.");
}

void ErrorHandler::missingOperatorError() {
    logError("Missing operator in the expression. Check for implicit multiplication or misplaced numbers.");
}

void ErrorHandler::invalidCharacterError(char character, int position) {
    std::string error = "Invalid character '" + std::string(1, character) + "' at position " + std::to_string(position) + ".";
    logError(error);
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
    std::string error = "Invalid character sequence '" + characterSequence + "' starting at position " + std::to_string(position) + ".";
    logError(error);
}