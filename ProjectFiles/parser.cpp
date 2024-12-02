/*

TO KIT
Please go to line 137 to see what to do. Implementation of void clean() method
If you need any clarification on documentation feel free to text me - Phoenix (913-258-0706).
*/


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
#include <iostream>
#include "parser.h"
using namespace std;

struct BinaryNode{
    LinkedList entry;
    BinaryNode *left;
    BinaryNode *right;
};

class Parser{
    private:
        BinaryNode *root;
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
        int lowPriority(LinkedList list){//expects a cleaned list, one with only a valid mathematical expression inside
            //traverse through list right to left, only look for pluses/minus outside of parenthesis, then go right to left only looking for multi/div, then right to left only looking for exp. After this is done that must mean list expression is inside a set of parenthesis, do this all again but drop the exterior parenthesis
            int parenthDepth = 0;
            bool addSub = true;
            bool multDiv = false;
            bool exp = false;
            bool par = false;
            while(list.getLength() >1){//either we escape by only being left with a number, or by returning.
                for(int j=0;j<4;j++){ //j<4 so we don't eliminate early, if j<3, we would switch case 2 but never acutally perform anything with the new case
                    for(int i=list.getLength()-1; i>=0;i--){
                        if(list.getEntry(i).isChar){
                            if(list.getEntry(i).character == ')' && !par){
                                parenthDepth++;
                            }else if(list.getEntry(i).character == '('){
                                parenthDepth--;
                            }else if(parenthDepth == 0){
                                if(addSub && (list.getEntry(i).character == '+' || list.getEntry(i).character == '-')){
                                    return i;
                                }else if(multDiv &&((list.getEntry(i).character == '*' || list.getEntry(i).character == '/'))){
                                    return i;
                                }else if(exp && list.getEntry(i).character == '^'){
                                    return i;
                                }else if(par && list.getEntry(0).character == '(' && list.getEntry(list.getLength()-1).character == ')'){
                                    list.remove(0);
                                    list.remove(list.getLength()-1);
                                    par = false;
                                    addSub = true;
                                }
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
                        break;
                    case 2:
                        exp = false;
                        par = true;
                        break;
                    default:
                        break;

                    }
                }
            }
            return 0; //this is the case that there is only one item remaining in the list typically it comes from examples like 3*(4), first pass * is returned, then (4) is handled parenthesis are removed, then we only have 4 in the list now 

        }
        void clean(LinkedList list){
            //To Kit: Please implement this method. What is required is to check if the expression makes sytactical sense, as well as inserting in multiplication into the correct index of the list in cases where it is implied like (4+5)(9/3) or 6(7+9) also check for valid parenthesis (this can be achieved by doing something similar to parentDepth in lowPriority method) and then making sure there aren't any nonsensical expressions like 9+/9, the lexer guys will be giving us data in the form of a linked list in the form [6,+,-6] or [6,-,6]
            int parenthDepth = 0;
            bool lastWasOperator = false;
            bool lastWasValue = false;
            
            for (int i = 0; i < list.getLength(); i++) {
                auto current = list.getEntry(i);
            
                    // This gonna check for valid parentheses
                if (current.isChar && current.character == '(') {
                    parenthDepth++;
                    lastWasOperator = true; // Opening parentheses acts as an implicit operator
                    lastWasValue = false;
                } else if (current.isChar && current.character == ')') {
                    parenthDepth--;
                    if (parenthDepth < 0) {
                        throw runtime_error("Error: Mismatched parentheses detected.");
                    }
                    lastWasOperator = false;
                    lastWasValue = true;
                }
            
                    // This will check for operators and their valid placements
                if (current.isChar && (current.character == '+' || current.character == '-' || current.character == '*' || current.character == '/')) {
                    if (lastWasOperator) {
                        throw runtime_error("Error: Consecutive operators are not allowed.");
                    }
                    lastWasOperator = true;
                    lastWasValue = false;
                } else if (!current.isChar) { 
                    if (lastWasValue) {
                        list.insert('*', i);
                        i++; 
                    }
                    lastWasOperator = false;
                    lastWasValue = true;
    }

        //  this handles implied multiplication after closing parentheses
            if (current.isChar && current.character == ')' && i + 1 < list.getLength()) {
                auto next = list.getEntry(i + 1);
                if (!next.isChar || next.character == '(') {
                    list.insert('*', i + 1);
                    i++; // Skip over newly inserted operator
                }
            }
        }
    
        // Final check for mismatched parentheses
            if (parenthDepth != 0) {
                throw runtime_error("Error: Mismatched parentheses detected.");
            }
        
            // this will check for invalid ending 
            if (lastWasOperator) {
                throw runtime_error("Error: Expression ends with an invalid operator.");
            }
                }
                void deleteTree(BinaryNode *curNode){
                    if(curNode == nullptr){
                        return;
                    }
                    deleteTree(curNode->left);
                    deleteTree(curNode->right);
                    delete curNode;
                }
                void rec_postOrder(BinaryNode *curNode){
                    if(curNode->left != nullptr){
                        rec_postOrder(curNode->left);
                    }
                    if(curNode->right != nullptr){
                        rec_postOrder(curNode->right);
                    }
                    if(curNode->entry.getEntry(0).isChar){
                        cout << curNode->entry.getEntry(0).character << "\n";
                    }else{
                        cout << curNode->entry.getEntry(0).value << "\n";
                    }
                }
    public:
        Parser(LinkedList entry){
            clean(entry);
            root = split(entry, lowPriority(entry));
            rec_add(root);
        }
        void postOrderDisplay(){
            rec_postOrder(root);
        }
        ~Parser(){
            deleteTree(root);
        }
};
