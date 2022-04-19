// John Leeds
// 3/2/2022
// Stack.h

#ifndef STACK_H
#define STACK_H

class StackNode{
    public:
        /*
         * constructor
         * Creates a StackNode with the given coordinates
         */
        StackNode(int newCoords[]);
        
        // Getters
        int* getCoords();
        StackNode* getNext();
        // Setters
        void setCoords(int coords[]);
        void setNext(StackNode* newNext);
        
    private:
        int myCoords[2];
        StackNode* next;
};

class Stack{
    public:
        /*
         * constructor
         * Creates a new Stack from a pair of coordinates
         */
        Stack(int coords[2]);

        /*
         * push
         * Pushes a new value of coordinates to the stack
         */
        void push(int newCoords[]);
        
        /*
         * peek
         * Returns the value of the top of the stack
         */
        int* peek();
        
        /*
         * pop
         * Deletes the head of the stack and returns the value
         */
        int* pop();
        
        /*
         * length
         * Returns the length of the stack
         */
        int length();

        /*
         * isEmpty
         * Returns true of the stack is empty
         */
        bool isEmpty();

        /*
         * show
         * Prints the contents of the stack
         */
        void show();
        
        /* 
         * getHead
         * Returns the head of the stack
         */
        StackNode* getHead();

    private:
        StackNode* head;
};

#endif
