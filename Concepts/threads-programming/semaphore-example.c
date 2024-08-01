/*
        SEMAPHORES IN THREAD SYNCHRONIZATION

    - A semaphore is used to manage access to a finite number of resources by multiple threads. 
    - The semaphore keeps track of the number of available resources and allows a limited number 
        of threads to access those resources at the same time.
    
            key Points

    - Single Resource: You can use a semaphore to manage access to a single resource. 
        This is essentially the same as a binary semaphore (or mutex), which allows 
            only one thread to access the resource at a time.
        
    - Multiple Resources: When you have multiple instances of a resource (e.g., database connections, printers), 
                a counting semaphore is used to manage access. The value of the semaphore represents 
                    the number of available resources.
            
        Example with Multiple Resources

    - Let's consider a semaphore managing access to a pool of 3 database connections by multiple threads.

        - If 3 connections are available, the semaphore's initial value is 3.
        - Each time a thread acquires a connection, it performs a wait (P) operation, decrementing the semaphore.
        - When a thread releases a connection, it performs a signal (V) operation, incrementing the semaphore.

        Simplified Scenerio

    - Semaphore Initialization: Value set to the number of available resources (e.g., 3 database connections).
    - Wait (P) Operation: A thread decrements the semaphore value before accessing a resource. If the value is greater than 0, 
        the thread proceeds. If 0, the thread waits until a resource becomes available.
    - Signal (V) Operation: A thread increments the semaphore value after releasing a resource, potentially unblocking a waiting thread.
*/
//Example code
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5
#define NUM_RESOURCES 3
#define SEM_NAME "/example_semaphore"

sem_t *semaphore; // Named semaphore

void *access_resource(void *arg) {
    int thread_id = *((int *)arg);

    sem_wait(semaphore); // Wait (decrement) the semaphore
    printf("Thread %d is accessing the resource\n", thread_id);
    // Simulate resource access
    sleep(1);
    printf("Thread %d is done accessing the resource\n", thread_id);
    sem_post(semaphore); // Signal (increment) the semaphore

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Create the named semaphore with the number of resources
    semaphore = sem_open(SEM_NAME, O_CREAT, 0644, NUM_RESOURCES);
    if (semaphore == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, access_resource, (void *)&thread_ids[i]) != 0) {
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

    // Close and unlink the named semaphore
    if (sem_close(semaphore) != 0) {
        perror("sem_close");
        exit(EXIT_FAILURE);
    }
    if (sem_unlink(SEM_NAME) != 0) {
        perror("sem_unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}

