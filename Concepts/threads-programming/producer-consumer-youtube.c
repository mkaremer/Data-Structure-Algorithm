#include <stdio.h>       // Standard input and output library
#include <stdlib.h>      // Standard library for functions like rand()
#include <pthread.h>     // POSIX thread library for creating and managing threads
#include <unistd.h>      // Unix standard library for functions like sleep()
#include <time.h>        // Library for time-related functions
#include <semaphore.h>   // Semaphore library for controlling access to resources

#define THREAD_NUM 8     // Define the number of threads (7 producers and 1 consumer)

sem_t semEmpty;          // Semaphore to track empty slots in the buffer
sem_t semFull;           // Semaphore to track filled slots in the buffer

pthread_mutex_t mutexBuffer;  // Mutex to protect access to the shared buffer

int buffer[10];          // Shared buffer with a capacity of 10 integers
int count = 0;           // Count of items currently in the buffer

// Producer function
void* producer(void* args) {
    while (1) {
        // Produce a random number
        int x = rand() % 100;  // Generate a random number between 0 and 99
        sleep(1);              // Simulate time taken to produce the item

        // Add the produced item to the buffer
        sem_wait(&semEmpty);           // Wait for an empty slot in the buffer
        pthread_mutex_lock(&mutexBuffer); // Lock the buffer to ensure exclusive access
        buffer[count] = x;             // Add the item to the buffer
        count++;                       // Increment the item count
        pthread_mutex_unlock(&mutexBuffer); // Unlock the buffer
        sem_post(&semFull);            // Signal that a new item is added (buffer is more full)
    }
}

// Consumer function
void* consumer(void* args) {
    while (1) {
        int y;

        // Remove an item from the buffer
        sem_wait(&semFull);            // Wait for an available item in the buffer
        pthread_mutex_lock(&mutexBuffer); // Lock the buffer to ensure exclusive access
        y = buffer[count - 1];         // Remove the item from the buffer
        count--;                       // Decrement the item count
        pthread_mutex_unlock(&mutexBuffer); // Unlock the buffer
        sem_post(&semEmpty);           // Signal that a slot is freed (buffer is less full)

        // Consume the item
        printf("Got %d\n", y);         // Print the consumed item
        sleep(1);                      // Simulate time taken to consume the item
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));                 // Seed the random number generator with the current time
    pthread_t th[THREAD_NUM];          // Array to hold thread identifiers
    pthread_mutex_init(&mutexBuffer, NULL); // Initialize the mutex for the buffer
    sem_init(&semEmpty, 0, 10);        // Initialize the semEmpty semaphore with a value of 10
    sem_init(&semFull, 0, 0);          // Initialize the semFull semaphore with a value of 0
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (i > 0) {                   // For the first thread, create a consumer thread
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0) { // Create producer threads
                perror("Failed to create thread"); // Print error message if thread creation fails
            }
        } else {                       // Create a consumer thread
            if (pthread_create(&th[i], NULL, &consumer, NULL) != 0) { // Create consumer thread
                perror("Failed to create thread"); // Print error message if thread creation fails
            }
        }
    }
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) { // Wait for all threads to finish execution
            perror("Failed to join thread"); // Print error message if thread joining fails
        }
    }
    sem_destroy(&semEmpty);            // Destroy the semEmpty semaphore
    sem_destroy(&semFull);             // Destroy the semFull semaphore
    pthread_mutex_destroy(&mutexBuffer); // Destroy the mutex for the buffer
    return 0;                          // Exit the program
}
