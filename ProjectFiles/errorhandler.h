#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <string>

class ErrorHandler {
private:
    static const int MAX_ERRORS = 100; 
    std::string errorMessages[MAX_ERRORS]; 
    int errorCount; 

public:
    ErrorHandler(); // Constructor to initialize the error handler

    void logError(const std::string& message); // Add a new error message
    bool hasErrors() const; // Check if errors are present
    void displayErrors() const; // Print all error messages to the console
    void clearErrors(); // Clear all logged errors

    
    void unmatchedParenthesesError();
    void operatorWithoutOperandsError(const std::string& operatorSymbol, int position);
    void incorrectOperatorUsageError();
    void missingOperatorError();
    void invalidCharacterError(char character, int position);
    void mismatchedParenthesesError();
    void divisionByZeroError();
    void invalidOperatorSequenceError();
    void missingOperandError();
    void invalidCharactersError(const std::string& characterSequence, int position);
};

#endif 