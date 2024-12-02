#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <string>
#include <vector>

class ErrorHandler {
private:
    std::vector<std::string> errorMessages; // Stores all error messages

public:
    // Adds a new error message to the list
    void logError(const std::string& message);

    // Returns true if there are errors
    bool hasErrors() const;

    // Prints all error messages to the console
    void displayErrors() const;

    // Clears all logged errors
    void clearErrors();

    // Specific error handling functions
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

#endif // ERRORHANDLER_H
