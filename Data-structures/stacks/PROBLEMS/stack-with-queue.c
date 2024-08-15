/*
        Implement stack using queues
        Algorithm:
            - push:
                - enqueue the new element into the queue
                - rotate the queue so that the new element is moved at the front of the queue.
                    - this can be done by dequeueing all prev elements and queueing them back after the new element
            - pop:
                - simply dequeue the element from the front of the queue
            - top:
                - return the front element of the queue without dequeueing it.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for queue elements
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
    int size;
} Queue;

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

// Function to initialize a queue
void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

// Function to check if a queue is empty
bool isQueueEmpty(Queue* q) {
    return q->size == 0;
}

// Function to enqueue an element to a queue
void enqueue(Queue* q, int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) {
        return;
    }
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

// Function to dequeue an element from a queue
int dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue underflow\n");
        return -1;
    }
    Node* temp = q->front;
    int data = temp->value;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    q->size--;
    return data;
}

// Stack structure using a single queue
typedef struct Stack {
    Queue queue;
} Stack;

// Function to initialize a stack
void initStack(Stack* s) {
    initQueue(&s->queue);
}

// Function to push an element onto the stack
void push(Stack* s, int data) {
    enqueue(&s->queue, data); // Enqueue the new element into the queue
    int size = s->queue.size;

    // Rotate the queue to move the new element to the front
    for (int i = 0; i < size - 1; i++) {
        enqueue(&s->queue, dequeue(&s->queue));
    }
}

// Function to pop an element from the stack
int pop(Stack* s) {
    if (isQueueEmpty(&s->queue)) {
        printf("Stack underflow\n");
        return -1;
    }
    return dequeue(&s->queue); // Dequeue the front element, which is the top of the stack
}

// Function to check if the stack is empty
bool isStackEmpty(Stack* s) {
    return isQueueEmpty(&s->queue);
}

// Function to get the top element of the stack
int top(Stack* s) {
    if (isStackEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->queue.front->value; // The front element of the queue is the top of the stack
}

int main() {
    Stack s;
    initStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("Top element: %d\n", top(&s)); // Output: 30
    printf("Popped element: %d\n", pop(&s)); // Output: 30
    printf("Popped element: %d\n", pop(&s)); // Output: 20
    printf("Top element: %d\n", top(&s)); // Output: 10

    return 0;
}
