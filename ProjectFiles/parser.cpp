//parser.cpp
//Phoenix Brehm and Kit Magar

/*
Purpose: To take in an input from the lexer in the form of a linked list and output a binary tree, one with the order of operations happening in post-order. This tree will be passed into the evaluator for it to evaluate the tree in this order. The parser will also handle errors like incorrect parenthesis use, nonsensical orderings like 3+*4, and the distriubutive property.

By post order the intention is to go as far down as possible, then once you have two numbers go up go to the common parent and perform the operation, continue until the root is missing.
*/
//Assuming clean input in the form of a linked list
//TODO: Throw error to errorhandler when we find the doubling up of operators, except for cases of nested parenthesis (()), distibution ()(), ()Operator()
//Checking parenthesis validity
//Look through the linked list from right to left, finding the lowest precidence operator [ +-, */and distributive, ^, () ] then putting the operator at the root, and then the leftside of the expression on the left child and the right side of the expression into the right child, perform this operation until every item of the list is isolated, then return this new tree to the evaluator
#include "dataStruct.h"
#include <stdexcept>

using namespace std;

struct BinaryNode{
    LinkedList entry;
    bool isChar;
    BinaryNode *left;
    BinaryNode *right;
};

class Parser{
    private:
        BinaryNode *root;
    public:
        Parser(LinkedList entry){
            //TODO: clean(entry);
            root = split(entry, lowPriority(entry));
            rec_add(root);
        }
        void rec_add(BinaryNode *curNode){
            if(curNode==nullptr){ //not quite sure if necessary, but it's a good to have for safety.
                return;
            }
            if(curNode->left != nullptr && curNode->left->entry.getLength() > 1){
                curNode->left = split(curNode->left->entry, lowPriority(curNode->left->entry));
                rec_add(curNode->left);
            }
            if(curNode->right != nullptr && curNode->right->entry.getLength() > 1){
                curNode->right = split(curNode->right->entry, lowPriority(curNode->right->entry));
                rec_add(curNode->right);
            }
        }
        BinaryNode* split(LinkedList list, int index){;
            LinkedList leftList;
            LinkedList rightList;
            LinkedList center;

            //fills center value
            center.insert(list.getEntry(index).character, 0);

            //fills center's lst
            for(int i=0; i<index;i++){
                if(list.getEntry(i).isChar){
                    leftList.insert(list.getEntry(i).character,i);
                }else{
                    leftList.insert(list.getEntry(i).value, i);
                }
            }

            //fills center's rst
            for(int i=0; i<list.getLength()-index-1;i++){
                if(list.getEntry(index+i+1).isChar){
                    rightList.insert(list.getEntry(index+i+1).character,i);
                }else{
                    rightList.insert(list.getEntry(index+i+1).value, i);
                }
            }

            //creates a node with the value of center and respective trees
            BinaryNode *newNode = new BinaryNode();
            newNode->entry = center;
            newNode->left->entry=leftList;
            newNode->right->entry=rightList;
            return newNode;

        }



        //TODO: Clean method which adds in implied multiplication as well as checks validity of expression
        //TODO: Fix LowPriority
        //TODO: Create deconstructor method
        //TODO: Create post order traversal
        //LowPriority needs to be worked on in order to get accurate results from it.
        int lowPriority(LinkedList list){//expects a clean list
            //traverse through list right to left
            bool ignore = false;
            bool addSub = true;
            bool multDiv = false;
            bool exp = false;
            bool par = false;
            while(list.getLength() >0){
                for(int j;j<4;j++){
                    for(int i=list.getLength()-1; i>=0;i--){
                        if(list.getEntry(i).isChar){
                            if(list.getEntry(i).character == ')' && !par){
                                ignore = true;
                            }else if(list.getEntry(i).character == '('){
                                ignore = false;
                            }else if(!ignore){
                                if(addSub && (list.getEntry(i).character == '+' || list.getEntry(i).character == '-')){
                                    return i;
                                }else if(multDiv &&((list.getEntry(i).character == '*' || list.getEntry(i).character == '/'))){
                                    return i;
                                }else if(exp && list.getEntry(i).character == '^'){
                                    return i;
                                }else if(par && )
                            }
                        }
                    }
                switch (j){
                case 0:
                    addSub = false;
                    multDiv = true;
                    break;
                case 1:
                    multDiv = false;
                    exp = true;
                case 2:
                    exp = false;
                    par = true;

                }
                }
            }

        }
};

//once we have a clean list, move right find lowest priority item.
//next put that at root, place items in left and right subtree
//next move into the left subtree, find the lowest priority item
//perform until lst=size 1, then move down rst until rst=size 1
//end recursion