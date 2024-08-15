/*
    implement a queue using two stacks

    algorihtm:
        - enqueue: push the elements onto stack1
        - dequeue:
            - if stack2 is empty pop all elements from stack1 and push them onto stack2.
                this reverses the order of elements so that the oldest element is now on top of the stack2.
            - pop element from the stack2
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
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

// Function to initialize a stack
void initStack(Stack* s) {
    s->top = NULL;
}

// Function to push an element onto a stack
void push(Stack* s, int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) {
        return;
    }
    newNode->next = s->top;
    s->top = newNode;
}

// Function to pop an element from a stack
int pop(Stack* s) {
    if (s->top == NULL) {
        printf("Stack underflow\n");
        return -1; // Return a special value to indicate stack underflow
    }
    int popped = s->top->value;
    Node* temp = s->top;
    s->top = s->top->next;
    free(temp);
    return popped;
}

// Function to check if a stack is empty
bool isEmpty(Stack* s) {
    return s->top == NULL;
}

// Struct to represent a queue using two stacks
typedef struct Queue {
    Stack stack1;
    Stack stack2;
} Queue;

// Function to initialize the queue
void initQueue(Queue* q) {
    initStack(&q->stack1);
    initStack(&q->stack2);
}

// Function to enqueue an element
void enqueue(Queue* q, int data) {
    push(&q->stack1, data);
}

// Function to dequeue an element
int dequeue(Queue* q) {
    if (isEmpty(&q->stack2)) {                // Check if stack2 is empty
        while (!isEmpty(&q->stack1)) {        // While stack1 is not empty
            int value = pop(&q->stack1);      // Pop the top element from stack1
            push(&q->stack2, value);          // Push that element onto stack2
        }
    }
    return pop(&q->stack2);                   // Pop and return the top element from stack2, which is the front of the queue
}


// Function to check if the queue is empty
bool isQueueEmpty(Queue* q) {
    return isEmpty(&q->stack1) && isEmpty(&q->stack2);
}

// Function to get the front element of the queue
int front(Queue* q) {                        
    if (isEmpty(&q->stack2)) {                 // Check if stack2 is empty
        while (!isEmpty(&q->stack1)) {         // While stack1 is not empty
            int value = pop(&q->stack1);       // Pop the top element from stack1
            push(&q->stack2, value);           // Push that element onto stack2
        }
    }
    return q->stack2.top->value;               // Return the top element of stack2, which is the front of the queue
}


int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);

    printf("Dequeued: %d\n", dequeue(&q)); // Output: 1
    printf("Front element: %d\n", front(&q)); // Output: 2
    printf("Dequeued: %d\n", dequeue(&q)); // Output: 2

    enqueue(&q, 4);

    printf("Dequeued: %d\n", dequeue(&q)); // Output: 3
    printf("Dequeued: %d\n", dequeue(&q)); // Output: 4

    if (isQueueEmpty(&q)) {
        printf("Queue is empty\n");
    } else {
        printf("Queue is not empty\n");
    }

    return 0;
}
