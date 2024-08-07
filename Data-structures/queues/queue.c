#include <stdio.h>
#include <stdlib.h>
#include "queue.h"  // Include the header file

// Function to create a new node
static Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize a queue
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    q->front = q->rear = NULL;  // Initialize front and rear to NULL
    return q;
}

// Function to add an element to the queue (enqueue)
void enqueue(Queue* q, int data) {
    Node* newNode = createNode(data);  // Create a new node
    if (newNode == NULL) {
        return;
    }

    if (q->rear == NULL) {  // If the queue is empty
        q->front = q->rear = newNode;  // New node is both front and rear
        return;
    }

    q->rear->next = newNode;  // Add the new node at the end of the queue
    q->rear = newNode;  // Update the rear to the new node
}

// Function to remove an element from the queue (dequeue)
int dequeue(Queue* q) {
    if (q->front == NULL) {  // If the queue is empty
        fprintf(stderr, "Queue is empty\n");
        return -1;  // Return an error value
    }

    Node* temp = q->front;  // Store the front node
    int data = temp->data;  // Get the data from the front node
    q->front = q->front->next;  // Move the front to the next node

    if (q->front == NULL) {  // If the queue becomes empty
        q->rear = NULL;  // Set rear to NULL as well
    }

    free(temp);  // Free the old front node
    return data;  // Return the dequeued data
}

// Function to display the queue
void displayQueue(Queue* q) {
    Node* temp = q->front;  // Start from the front
    while (temp != NULL) {  // Traverse the queue
        printf("%d -> ", temp->data);  // Print each element
        temp = temp->next;  // Move to the next node
    }
    printf("NULL\n");  // Indicate the end of the queue
}

// Function to free the entire queue
void freeQueue(Queue* q) {
    while (q->front != NULL) {
        Node* temp = q->front;  // Temporary pointer to hold the front
        q->front = q->front->next;  // Move the front to the next node
        free(temp);  // Free the memory of the current front
    }
    free(q);  // Free the queue structure
}
