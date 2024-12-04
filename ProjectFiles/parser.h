#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <stdexcept>
#include "dataStruct.h"
#include "errorhandler.h"

struct BinaryNode{
    LinkedList entry;
    BinaryNode *left;
    BinaryNode *right;
};

class Parser{
    private:
        BinaryNode *root;
        void rec_add(BinaryNode *curNode);
        BinaryNode* split(LinkedList list, int index);
        int lowPriority(LinkedList list);
        void clean(LinkedList list);
        void deleteTree(BinaryNode *curNode);
        void rec_postOrder(BinaryNode *curNode);
    public:
        Parser(LinkedList entry);
        void postOrderDisplay();
        ~Parser();
};


#endif