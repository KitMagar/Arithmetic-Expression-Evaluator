#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>
#include <iostream>

union nodeData{
    char character;
    double value;
    bool isChar;
};

struct Node{
    nodeData entry;
    Node *next;
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
    ~LinkedList();
    int getLength();
    nodeData getEntry(int index);
    void insert(char c, int index);
    void insert(double v, int index);
    void remove(int index);

};

#endif