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
#include <string>
using namespace std;

void Parser::rec_add(BinaryNode *curNode){
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
BinaryNode* Parser::split(LinkedList list, int index){
    LinkedList leftList;
    LinkedList rightList;
    LinkedList center;

    //fills center value
    //cout << index;
    //list.print();
    center.insert(list.getEntry(index).entry.character, 0);

    //fills center's lst
    for(int i=0; i<index;i++){
        if(list.getEntry(i).isChar){
            leftList.insert(list.getEntry(i).entry.character,i);
        }else{
            leftList.insert(list.getEntry(i).entry.value, i);
        }
    }
    //should remove areas of parentheses around a constant
    if(leftList.getLength()==3){
        if(leftList.getEntry(0).isChar && leftList.getEntry(2).isChar){
            if(leftList.getEntry(0).entry.character == '(' && leftList.getEntry(2).entry.character == ')'){
                leftList.remove(2);
                leftList.remove(0);
            }
        }
    }
    //fills center's rst
    for(int i=0; i<list.getLength()-index-1;i++){
        if(list.getEntry(index+i+1).isChar){
            rightList.insert(list.getEntry(index+i+1).entry.character,i);
        }else{
            rightList.insert(list.getEntry(index+i+1).entry.value, i);
        }
    }
    //should remove areas of parentheses around a constant
    if(rightList.getLength()==3){
        if(rightList.getEntry(0).isChar && rightList.getEntry(2).isChar){
            if(rightList.getEntry(0).entry.character == '(' && rightList.getEntry(2).entry.character == ')'){
                rightList.remove(2);
                rightList.remove(0);
            }
        }
    }
    //cout << "pass 3\n";
    //creates a node with the value of center and respective trees
    BinaryNode *newNode = new BinaryNode();
    newNode->left = new BinaryNode();
    newNode->right = new BinaryNode();
    
    newNode->entry = center;
    newNode->left->entry=leftList;
    newNode->right->entry=rightList;
    /*
    cout << "center";
    center.print();
    cout << "left";
    leftList.print();
    cout << "right";
    rightList.print();*/
    return newNode;

}
int Parser::lowPriority(LinkedList &list){//expects a cleaned list, one with only a valid mathematical expression inside
    //traverse through list right to left, only look for pluses/minus outside of parenthesis, then go right to left only looking for multi/div, then right to left only looking for exp. After this is done that must mean list expression is inside a set of parenthesis, do this all again but drop the exterior parenthesis
    bool addSub = true;
    bool multDiv = false;
    bool exp = false;
    bool par = false;
    string c;
    while(list.getLength() >1){//either we escape by only being left with a number, or by returning.
        int parenthDepth = 0;
        int startIndex = -1;
        int endIndex = -1;

        //this block is used to remove unecessary beginning and end parentheses
        for(int i=0; i<list.getLength(); i++){
            if(list.getEntry(i).isChar){
                if(list.getEntry(i).entry.character == '('){
                    if(parenthDepth==0){
                        startIndex = i;
                    }
                    parenthDepth++;
                }else if(list.getEntry(i).entry.character == ')'){
                    parenthDepth--;
                    if(parenthDepth==0){
                        endIndex=i;
                        break;
                    }
                }
            }
        }
        //list.print();
        //cin >> c;
        if(startIndex == 0 && endIndex == list.getLength()-1){
            //cout << "TRUE REMOVE";
            list.remove(list.getLength()-1);
            list.remove(0);
            //list.print(); cout << "printedList";
        }
        //cout << parenthDepth << addSub << multDiv << exp << par <<"\n";
        for(int j=0;j<4;j++){ //j<4 so we don't eliminate early, if j<3, we would switch case 2 but never acutally perform anything with the new case
            for(int i=list.getLength()-1; i>=0;i--){
                if(list.getEntry(i).isChar){
                    if(list.getEntry(i).entry.character == ')' && !par){
                        parenthDepth++;
                    }else if(list.getEntry(i).entry.character == '('){
                        parenthDepth--;
                    }else if(parenthDepth == 0){
                        if(addSub && (list.getEntry(i).entry.character == '+' || list.getEntry(i).entry.character == '-')){
                            return i;
                        }else if(multDiv &&((list.getEntry(i).entry.character == '*' || list.getEntry(i).entry.character == '/' || list.getEntry(i).entry.character == '%'))){
                            return i;
                        }else if(exp && list.getEntry(i).entry.character == '^'){
                            return i;
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
                addSub=true;
                par=false;
                break;

            }
        }
        rec_paren(list); //this call removes unnecessary parentheses for sub-expressions
    }
    return 0; //this is the case that there is only one item remaining in the list typically it comes from examples like 3*(4), first pass * is returned, then (4) is handled parenthesis are removed, then we only have 4 in the list now 

}
void Parser::clean(LinkedList &list){
    //Explanation of goal: Check if the expression makes sytactical sense, as well as inserting in multiplication into the correct index of the list in cases where it is implied like (4+5)(9/3) or 6(7+9) also check for valid parenthesis (this can be achieved by doing something similar to parentDepth in lowPriority method) and then making sure there aren't any nonsensical expressions like 9+/9, the lexer guys will be giving us data in the form of a linked list in the form [6,+,-6] or [6,-,6]
    int parenthDepth = 0;
    bool lastWasOperator = false;
    //bool lastWasValue = false;
    //9(3+7)
    for (int i = 0; i < list.getLength(); i++) {
        auto current = list.getEntry(i);
    
            // This gonna check for valid parentheses
        if (current.isChar && current.entry.character == '(') {
            parenthDepth++;
            lastWasOperator = true; // Opening parentheses acts as an implicit operator
            //lastWasValue = false;
        } else if (current.isChar && current.entry.character == ')') {
            parenthDepth--;
            if (parenthDepth < 0) {
                errorH.mismatchedParenthesesError();
                throw runtime_error("mismatched parentheses");
            }
            lastWasOperator = false;
            //lastWasValue = true;
        }
    
            // This will check for operators and their valid placements
        if (current.isChar && (current.entry.character == '+' || current.entry.character == '-' || current.entry.character == '*' || current.entry.character == '/' || current.entry.character == '^' || current.entry.character == '%')) {
            if (lastWasOperator || i==0) {
                errorH.invalidOperatorSequenceError();
                throw runtime_error("invalid operator sequence");
            }else if(list.getEntry(i+1).isChar){
                if(list.getEntry(i+1).entry.character == '+' || list.getEntry(i+1).entry.character == '-' || list.getEntry(i+1).entry.character == '*' || list.getEntry(i+1).entry.character == '/' || list.getEntry(i+1).entry.character == '^' || list.getEntry(i+1).entry.character == '%' || list.getEntry(i+1).entry.character == ')'){
                    errorH.invalidOperatorSequenceError();
                    throw runtime_error("invalid operator sequence");
                }
            }
            lastWasOperator = true;
            //lastWasValue = false;
        } else if (!current.isChar) { 
            if(i+1 < list.getLength()){
                if (list.getEntry(i+1).isChar) {
                    if(list.getEntry(i+1).entry.character == '('){
                        list.insert('*', i+1);
                        i++; 
                    }
                }
            }
            lastWasOperator = false;
            //lastWasValue = true;
        }

//  this handles implied multiplication after closing parentheses
        if (current.isChar && current.entry.character == ')' && i + 1 < list.getLength()) {
            auto next = list.getEntry(i + 1);
            if (!next.isChar || next.entry.character == '(') {
                list.insert('*', i + 1);
                i++; // Skip over newly inserted operator
            }
        }

    }
    // Final check for mismatched parentheses
    if (parenthDepth != 0) {
        errorH.mismatchedParenthesesError();
        throw runtime_error("mismatched parentheses");
    }

    // this will check for invalid ending 
    if (lastWasOperator) {
        errorH.invalidOperatorSequenceError();
        throw runtime_error("invalid operator sequence");
    }
}
//used to destroy any single numbers surrounded by parentheses
LinkedList Parser::rec_paren(LinkedList &expression){
    //cout << "rec_paren";
    //expression.print();
    int startIndex = -1;
    int endIndex = -1;
    int depth = 0;
    LinkedList smallerExpression;
    //find the start and end index of a sub expression
    for(int i=0; i<expression.getLength();i++){
        if(expression.getEntry(i).isChar){
            if(expression.getEntry(i).entry.character == '('){
                if(depth == 0){
                    startIndex = i;
                }
                depth++;
            }else if(expression.getEntry(i).entry.character == ')'){
                depth--;
                if(depth == 0){
                    endIndex = i;
                    break;
                }
            }
        }
    }
    if(startIndex == -1 || endIndex == -1){//if none are found
        return expression;
    }else if(expression.getEntry(startIndex+1).entry.character == '(' && expression.getEntry(endIndex-1).entry.character == ')'){//if it's just the end and beginning parentheses
        expression.remove(endIndex);
        expression.remove(startIndex);
        rec_paren(expression);
    }else{
        for(int i=0;i<endIndex-startIndex-1;i++){
            //fill list with all values after start index and before end index
            if(expression.getEntry(startIndex+i+1).isChar){
                smallerExpression.insert(expression.getEntry(startIndex+i+1).entry.character,i);
            }else{
                smallerExpression.insert(expression.getEntry(startIndex+i+1).entry.value,i);
            }
        }
        //look deeper, since we use the address the edits to remove uneccessary parentheses works.
        rec_paren(smallerExpression);
    }
}

void Parser::deleteTree(BinaryNode *curNode){
    if(curNode == nullptr){
        return;
    }
    deleteTree(curNode->left);
    deleteTree(curNode->right);
    curNode->entry.Cleanup();
    delete curNode;
}
void Parser::rec_postOrder(BinaryNode *curNode){
    if(curNode->left != nullptr){
        //cout << "going left";
        rec_postOrder(curNode->left);
    }
    if(curNode->right != nullptr){
        //cout << "going right";
        rec_postOrder(curNode->right);
    }
    if(curNode->entry.getEntry(0).isChar){
        cout << curNode->entry.getEntry(0).entry.character << "\n";
    }else{
        cout << curNode->entry.getEntry(0).entry.value << "\n";
    }
}
Parser::Parser(LinkedList entry){
    //cout << "Parser Creation\n";
    clean(entry);
    //cout << "Clean Executed\n";
    //entry.print();
    root = split(entry, lowPriority(entry));
    //cout << "root = split\n";
    rec_add(root);
    //postOrderDisplay();
    //cout << "creation complete\n";
}
void Parser::postOrderDisplay(){
    rec_postOrder(root);
}
Parser::~Parser(){
    deleteTree(root);
}