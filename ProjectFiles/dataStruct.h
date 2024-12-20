#ifndef LINKEDLIST_H
#define LINKEDLIST_H
union nodeData{
    char character;
    double value;
};

struct Node{
    nodeData entry;
    Node *next;
    bool isChar;
    Node(char c);
    Node(double v);
};

class LinkedList
{
private:
    Node *head;
    int length;
public:
    LinkedList();
    void Cleanup();
    int getLength();
    Node getEntry(int index);
    void insert(char c, int index);
    void insert(double v, int index);
    void remove(int index);
    void print();

};

#endif