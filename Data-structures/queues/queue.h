#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

// Define a node structure for the queue
typedef struct Node {
    int data;               // Data part of the node
    struct Node* next;      // Pointer to the next node
} Node;

// Define a queue structure
typedef struct Queue {
    Node* front;            // Pointer to the front node
    Node* rear;             // Pointer to the rear node
} Queue;

// Function prototypes
Queue* createQueue();                // Initialize a new queue
void enqueue(Queue* q, int data);    // Add an element to the queue
int dequeue(Queue* q);               // Remove an element from the queue
void displayQueue(Queue* q);         // Display the queue
void freeQueue(Queue* q);            // Free the entire queue

#endif // QUEUE_H
