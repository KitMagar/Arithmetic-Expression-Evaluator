#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "dataStruct.h"
#include "parser.h"
#include "errorhandler.h"

class Evaluator {
private:
    BinaryNode *root;
    ErrorHandler errorH;
    double evaluateNode(BinaryNode *node);

public:
    Evaluator(Parser rootNode);
    double evaluate();
	virtual ~Evaluator();
};

#endif