#include <stdio.h>
#include <stdlib.h>
#include "queue.h"  // Include the queue header file

int main() {
    Queue* q = createQueue();  // Initialize a new queue

    // Enqueue elements into the queue
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);

    // Display the queue
    printf("Queue: ");
    displayQueue(q);

    // Dequeue an element
    int data = dequeue(q);
    printf("Dequeued: %d\n", data);

    // Display the queue after dequeue
    printf("Queue after dequeue: ");
    displayQueue(q);

    // Free the queue
    freeQueue(q);

    return EXIT_SUCCESS;
}
