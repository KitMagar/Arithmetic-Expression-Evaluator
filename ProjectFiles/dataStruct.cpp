//Phoenix Brehm
#include <stdexcept>
#include <iostream>
using namespace std;

union nodeData{
    char character;
    double value;
};

struct Node{
    nodeData entry;
    Node *next; //next points to the address of another node
    bool isChar; //used in conjunction with main and getEntry to find out if we are interacting with a character or a value.

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
    Node getEntry(int index){ //The way we interact with the returned node is handled elsewhere.
        if(length == 0){
            cout << "List is empty\n";
        }else if(index >= length || index < 0){
            throw out_of_range("Index out of bounds");
        }
        Node *temp = head;
        for(int i =0;i<index;i++){
            temp = temp->next; //temp will point at the next node in line
        }
        return *temp;
    }

    void insert(char c,int index){ //used for characters
        Node *jumper = head;
        Node *insertVal = new Node(c);
        insertVal->next = nullptr;
        if(index >= length || index < 0){
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

    void insert(double v,int index){ //USED For values
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

    void remove(int index){
        if(index >= length || index <0){
            throw out_of_range("Index out of bounds");
        }else if(index == 0){
            head = head->next;
            length = length -1;
        }else{
            Node *before = head;
            for(int i=0;i<index-1;i++){
                before = before->next;
            }
            Node *temp = before->next;
            before->next = before->next->next;
            delete temp; //removes node from memory
            length = length -1;
        }
    }

    ~LinkedList(){ //iterates from the back and then deletes nodes from memory via remove function
        Node *current = head;
        while(current != nullptr){
            Node* nextnode = current->next;
            delete current;
            current = nextnode;
        }
        head = nullptr;
        length = 0;
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


    //This is how we handle if linked list has characters or numbers
        if(list.getEntry(i).isChar){ 
            cout << list.getEntry(i).entry.character << "\n";
        }else{
            cout << list.getEntry(i).entry.value << "\n";
        }
    }
    while (true)
    {
        ;
    }
    
    return 0;
}

*/