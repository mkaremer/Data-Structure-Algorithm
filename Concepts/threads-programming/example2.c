#include <pthread.h> // Include the POSIX thread library
#include <stdio.h>   // Include standard input/output library
#include <stdlib.h>  // Include standard library for general functions
#include <unistd.h>  // Include standard symbolic constants and types

#define NUM_THREADS 100 // Define the number of threads to create

// Thread function that prints the thread identifier
void* thread_function(void* arg) {
    printf("Thread %ld is running\n", (long)arg); // Print the thread identifier
    return NULL; // Return NULL when the thread function is done
}

int main() {
    pthread_t threads[NUM_THREADS]; // Declare an array of thread identifiers

    // Loop to create threads
    for (long i = 0; i < NUM_THREADS; i++) {
        // Create a thread and check for errors
        if (pthread_create(&threads[i], NULL, thread_function, (void*)i)) {
            fprintf(stderr, "Error creating thread %ld\n", i); // Print error message if thread creation fails
            return 1; // Return 1 to indicate failure
        }
    }

    // Loop to join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        // Wait for each thread to finish and check for errors
        if (pthread_join(threads[i], NULL)) {
            fprintf(stderr, "Error joining thread %d\n", i); // Print error message if thread joining fails
            return 2; // Return 2 to indicate failure
        }
    }

    printf("All threads have finished\n"); // Print message when all threads are done
    return 0; // Return 0 to indicate successful execution
}
