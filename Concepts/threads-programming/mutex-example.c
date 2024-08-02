/*
                MUTEX IN THREAD SYNCHRONIZATION

    - A mutex (mutual exclusion) is used to prevent multiple threads from accessing the same resource at the same time
    -  It ensures only one thread can enter the critical section (part of the code that uses shared resources) at a time, 
    - preventing race conditions and keeping data consistent.

                Key concepts
    - Locking and Unlocking:
        - Lock: When a thread locks a mutex, other threads must wait until it is unlocked.
        - Unlock: When the thread unlocks the mutex, one of the waiting threads can lock it and proceed.
    
    - Critical Section: The code that accesses shared resources, protected by a mutex to prevent simultaneous access

    - Mutex Initialization and Destruction:
        - Initialization: A mutex must be initialized before use.
        - Destruction: A mutex should be destroyed when no longer needed to free up resources.
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10
#define NUM_INCREMENTS 10

int counter = 0; // Shared counter
pthread_mutex_t lock; //mutex to protect the counter
// pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *increment_counter(void *arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        pthread_mutex_lock(&lock);
        counter++; // Increment the shared counter
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&lock, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0) {
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Error joining thread %d\n", i);
            return 1;
        }
    }

    //destroy the mutex
    pthread_mutex_destroy(&lock);

    printf("Final counter value: %d\n", counter);
    return 0;
}

