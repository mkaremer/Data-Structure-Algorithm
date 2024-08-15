/*
        MIN STACK PROBLEM
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
    int minValue;
} Stack;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    newNode->value = data;
    newNode->next = NULL;

    return newNode;
}

// Function to initialize the stack
void initStack(Stack* s) {
    s->top = NULL;
    s->minValue = INT_MAX;
}

// Function to push an element onto the stack
void push(Stack* s, int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) {
        return;
    }

    if (s->top == NULL) {
        s->minValue = data;
        newNode->value = data;
    } else {
        if (data < s->minValue) {
            newNode->value = data - s->minValue; // Store the difference
            s->minValue = data; // Update the minimum value
        } else {
            newNode->value = data;
        }
    }

    newNode->next = s->top;
    s->top = newNode;
}

// Function to pop an element from the stack
int pop(Stack* s) {
    if (s->top == NULL) {
        printf("Stack underflow\n");
        return INT_MIN; // Return a special value to indicate stack underflow
    }

    int popped = s->top->value;
    Node* temp = s->top;
    s->top = s->top->next;

    if (popped < 0) {
        int originalMin = s->minValue;
        s->minValue = s->minValue - popped; // Restore the previous minimum value
        popped = originalMin; // Return the original minimum value
    }

    free(temp);

    return popped;
}

// Function to get the minimum element from the stack
int getMin(Stack* s) {
    if (s->top == NULL) {
        printf("Stack is empty\n");
        return INT_MIN; // or some other error code
    }
    return s->minValue;
}

int main() {
    Stack s;
    initStack(&s);

    push(&s, 5);
    push(&s, 3);
    push(&s, 7);
    push(&s, 3);

    printf("Current Min: %d\n", getMin(&s)); // Output: 3

    printf("Popped: %d\n", pop(&s)); // Popped 3
    printf("Current Min: %d\n", getMin(&s)); // Output: 3

    printf("Popped: %d\n", pop(&s)); // Popped 7
    printf("Current Min: %d\n", getMin(&s)); // Output: 3

    printf("Popped: %d\n", pop(&s)); // Popped 3
    printf("Current Min: %d\n", getMin(&s)); // Output: 5

    return 0;
}
