#ifndef PARSER_H
#define PARSER_H

#include "dataStruct.h"
#include "errorhandler.h"

struct BinaryNode{
    LinkedList entry;
    BinaryNode *left;
    BinaryNode *right;
};
class Parser{
    private:
        ErrorHandler errorH;
        void rec_add(BinaryNode *curNode);
        BinaryNode* split(LinkedList list, int index);
        int lowPriority(LinkedList list);
        void clean(LinkedList &list);
        void deleteTree(BinaryNode *curNode);
        void rec_postOrder(BinaryNode *curNode);
    public:
        BinaryNode *root;
        Parser(LinkedList entry);
        void postOrderDisplay();
        ~Parser();
};


#endif