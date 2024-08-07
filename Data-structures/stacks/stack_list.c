#include "stack_list.h" // Includes the header file for stack list
#include <stdio.h>      // Includes the standard input/output library
#include <stdlib.h>     // Includes the standard library for memory allocation, process control, etc.

// Function to initialize the stack
void initStack(Stack* s) {
    s->top = NULL; // Sets the top pointer to NULL, indicating the stack is empty
}

// Function to check if the stack is empty
int isEmpty(Stack* s) {
    return s->top == NULL; // Returns true if the top pointer is NULL
}

// Function to push an element onto the stack
void push(Stack* s, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Allocates memory for a new node
    if (!newNode) { // Checks if memory allocation was successful
        printf("Memory allocation error\n"); // Prints an error message if memory allocation fails
        return; // Exits the function without pushing the element
    }
    newNode->data = value; // Sets the data of the new node
    newNode->next = s->top; // Points the new node to the current top node
    s->top = newNode; // Sets the new node as the top node
}

// Function to pop an element from the stack
int pop(Stack* s) {
    if (isEmpty(s)) { // Checks if the stack is empty before popping
        printf("Stack underflow\n"); // Prints an error message if the stack is empty
        return -1; // Returns -1 to indicate that the stack is empty
    }
    Node* temp = s->top; // Stores the current top node in a temporary variable
    int popped = temp->data; // Stores the data of the top node
    s->top = s->top->next; // Moves the top pointer to the next node
    free(temp); // Frees the memory of the popped node
    return popped; // Returns the popped data
}

// Function to peek the top element of the stack without removing it
int peek(Stack* s) {
    if (isEmpty(s)) { // Checks if the stack is empty before peeking
        printf("Stack is empty\n"); // Prints an error message if the stack is empty
        return -1; // Returns -1 to indicate that the stack is empty
    }
    return s->top->data; // Returns the data of the top node without modifying the stack
}

// Function to free the memory allocated for the stack
void freeStack(Stack* s) {
    while (!isEmpty(s)) { // Continuously pops elements until the stack is empty
        pop(s); // Pops an element from the stack
    }
}
