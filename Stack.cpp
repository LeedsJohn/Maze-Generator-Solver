// John Leeds
// 3/2/2022
// Stack.cpp
// Implements a stack for maze generation / solving
#include <iostream>
#include "Stack.h"
using namespace std;

/*
 * constructor
 * Creates a StackNode with the given coordinates
 */
StackNode::StackNode(int newCoords[]){
    myCoords[0] = newCoords[0];
    myCoords[1] = newCoords[1];
    next = nullptr;
}

// Getters
int* StackNode::getCoords() {
    int* cPtr;
    cPtr = myCoords;
    return cPtr;
}

StackNode* StackNode::getNext() {
    return next;
}

// Setters
void StackNode::setCoords(int newCoords[]){
    myCoords[0] = newCoords[0];
    myCoords[1] = newCoords[1];
}

void StackNode::setNext(StackNode* newNext){
    next = newNext;
}

/*
 * constructor
 * Creates a new Stack from a pair of coordinates
 */
Stack::Stack(int coords[2]){
    head = new StackNode(coords);
}

/*
 * push
 * Pushes a new value of coordinates to the stack
 */
void Stack::push(int newCoords[]){
    StackNode* newHead = new StackNode(newCoords);
    newHead->setNext(head);
    head = newHead;
}

/*
 * peek
 * Returns the value of the top of the stack
 */
int* Stack::peek() {
    int* cPtr;
    cPtr = head->getCoords();
    return cPtr;
}

/*
 * pop
 * Deletes the head of the stack and returns the value
 */
int* Stack::pop(){
    int* cPtr;
    cPtr = head->getCoords();
    head = head->getNext();
    return cPtr;
}

/*
 * length
 * Returns the length of the stack
 */
int Stack::length() {
    if ( head == NULL ) return 0;
    StackNode* counter = head;
    int c = 0;
    while ( counter ){
        c++;
        counter = counter->getNext();
    }
    return c;
}

/*
 * isEmpty
 * Returns true of the stack is empty
 */
bool Stack::isEmpty() {
    if ( head == NULL ) return true;
    return false;
}

/*
 * show
 * Prints the contents of the stack
 */
void Stack::show(){
    if ( head == NULL ){
        cout << "Stack is empty." << endl;
        return;
    }
    StackNode* printNode = head;
    while ( printNode ){
        int* coords = printNode->getCoords();
        cout << "(" << coords[0] << ", " << coords[1] << ")" << endl;
        printNode = printNode->getNext();
    }
}

/* 
 * getHead
 * Returns the head of the stack
 */
StackNode* Stack::getHead(){
    return head;
}
