#include <stdexcept>
#include <iostream>
#include <cmath>
using namespace std;

union nodeData{
    char character;
    double value;
};

struct Node{
    nodeData entry;
    Node *next; //next points to the address of another node
    bool isChar; //used with the getValue method of linkedList, as well as could be useful to use ptr.isChar to determine what to do.

    //Our constructor cases, if character or if value
    Node(char c){
        entry.character = c;
        isChar = true;
        next = nullptr;
    }
    Node(double v){
        entry.value = v;
        isChar = false;
        next = nullptr;
    }
};

class LinkedList{
    private:
    Node *head; //head will point to the address of a node
    int length;
    public:
    LinkedList(){ //constructor
        head = nullptr;
        length =0;
    }
    int getLength(){
        return length;
    }
    double getEntry(int index){
        if(length == 0){
            cout << "List is empty\n";
        }else if(index >= length || index < 0){
            throw out_of_range("Index out of bounds");
        }
        Node *temp = head;
        for(int i =0;i<index;i++){
            temp = temp->next; //temp will point at the next node in line
        }
        if(temp->isChar){
            cout << temp->entry.character << "\n";
        }else{
            return temp->entry.value;
        }
    }

    void insert(char c,int index){ //USED FOR Characters
        Node *jumper = head;
        Node *insertVal = new Node(c);
        insertVal->next = nullptr;
        if(index > length || index < 0){
            throw out_of_range("Index out of bounds");


        }else if(length == 0){ //if we are putting in our first node
            head = insertVal;
            length = 1;

        }else if(length > 0 && index != 0){//executed when going for an item not at the front
            Node *prejump = head;
            for(int i=0;i<index;i++){
                if(i>0){
                    prejump = prejump->next;
                }
                jumper = jumper->next;
            }
            insertVal->next = jumper; //insertval is now pointing at the node ahead of it
            prejump->next = insertVal; //prejump is now the node behind insertVal
            length = length + 1;

        }else{//executed when we have items in the list, but are inserting at the beginning
            head = insertVal;
            head->next = jumper;
            length = length + 1;
        }
    }

    void insert(double v,int index){ //USED for values
        Node *jumper = head;
        Node *insertVal = new Node(v);
        insertVal->next = nullptr;
        if(index > length || index < 0){
            throw out_of_range("Index out of bounds");


        }else if(length == 0){ //if we are putting in our first node
            head = insertVal;
            length = 1;

        }else if(length > 0 && index != 0){//executed when going for an item not at the front
            Node *prejump = head;
            for(int i=0;i<index;i++){
                if(i>0){
                    prejump = prejump->next;
                }
                jumper = jumper->next;
            }
            insertVal->next = jumper; //insertval is now pointing at the node ahead of it
            prejump->next = insertVal; //prejump is now the node behind insertVal
            length = length + 1;

        }else{//executed when we have items in the list, but are inserting at the beginning
            head = insertVal;
            head->next = jumper;
            length = length + 1;
        }
    }
};


/* SAMPLE MAIN



int main(){
    LinkedList list;
    list.insert(4.0, 0);
    list.insert(6.0, 0);
    list.insert(3.0, 1);
    list.insert(8.0, 2);
    list.insert('+', 2);

    for(int i=0;i<list.getLength();i++){
        if(!isnan(list.getEntry(i))){                       <-This line is used because of the return method for getEntry not being the most well done, if anybody does a better implementation that would be nice
            cout << list.getEntry(i) << "\n";
        }
    }
    while (true)
    {
        ;
    }
    
    return 0;
}
*/

template <typename T>
struct BinaryNode{
    T entry;
    BinaryNode *left;
    BinaryNode *right;
};