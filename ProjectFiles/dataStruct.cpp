#include <stdexcept>
#include <iostream>
using namespace std;
template <typename T>
struct Node{
    T entry;
    Node *next; //next points to the address of another node
};

template <typename T>
class LinkedList{
    private:
    Node *head;
    int length;
    public:
    LinkedList(){
        head = nullptr;
        length =0;
    }
    int length(){
        return length;
    }
    T getEntry(int index){
        if(length == 0){
            cout << "List is empty\n";
        }else if(index >= length || index < 0){
            throw out_of_range("Index out of bounds");
        }
        Node *temp = head;
        for(int i =0;i<index;i++){
            temp = temp->next;
        }
        return temp->entry;
    }
    void insert(T value,int index){
        if(length == 0){
            Node *insertVal = new Node();
            insertVal->entry = value;
            insertVal->next = nullptr;
            head = insertVal;
        }else if(index >= length || index < 0){
            throw out_of_range("Index out of bounds");
        }else{
            //Impliment
        }
    }
};


template <typename T>
struct BinaryNode{
    T entry;
    BinaryNode *left;
    BinaryNode *right;
};