/*
            CONDITION VARIABLE IN THREAD SYNCHRONIZATION

    - Condition variables are tools used with mutexes to help threads wait for certain 
                conditions before continuing.
    - This is useful when a thread needs to wait for an event to happen.

            KEY CONCEPTS

    - Condition Variable: Lets one or more threads wait until notified that a condition is met.
    - Mutex: Used with condition variables to ensure safe access to shared data.
    - Wait: A thread waits on a condition variable, releasing the mutex and blocking until notified.
    - Signal: A thread notifies one waiting thread that the condition is met.
    - Broadcast: A thread notifies all waiting threads that the condition is met.

        EXAMPLE SCENERIO
    - In a producer-consumer problem, the producer creates data, and the consumer processes it.
    - The consumer waits until the producer has data available.

        CONDITION VARIABLE OPERATIONS
    - Initialization: Set up the condition variable and mutex.
    - Waiting: A thread waits on the condition variable, releasing the mutex until the condition is signaled.
    - Signaling: Notify one waiting thread that the condition is met.
    - Broadcasting: Notify all waiting threads that the condition is met.

This ensures efficient coordination between threads without busy-waiting, 
    making programs more responsive and efficient.
*/
//EXAMPLE CODE WITHOUT CONDITION VARIABLE
// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// #define NUM_ITEMS 10

// int buffer = 0; // Shared buffer
// int data_ready = 0; // Flag indicating data readiness

// void *producer(void *arg) {
//     for (int i = 0; i < NUM_ITEMS; i++) {
//         while(data_ready == 1)
//         while (data_ready); // Busy-waiting until data is consumed
//         buffer = i; // Produce data
//         data_ready = 1; // Indicate data is ready
//         printf("Produced: %d\n", i);
//         sleep(1); // Simulate time-consuming production
//     }
//     return NULL;
// }

// void *consumer(void *arg) {
//     for (int i = 0; i < NUM_ITEMS; i++) {
//         while(data_ready == 0);
//         while (!data_ready); // Busy-waiting until data is produced
//         printf("Consumed: %d\n", buffer);
//         data_ready = 0; // Indicate data is consumed
//     }
//     return NULL;
// }

// int main() {
//     pthread_t producer_thread, consumer_thread;

//     // Create producer and consumer threads
//     pthread_create(&producer_thread, NULL, producer, NULL);
//     pthread_create(&consumer_thread, NULL, consumer, NULL);

//     // Wait for threads to complete
//     pthread_join(producer_thread, NULL);
//     pthread_join(consumer_thread, NULL);

//     return 0;
// }

// EXAMPLE WITH CONDITION VARIABLE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_ITEMS 10

int buffer = 0; // Shared buffer
int data_ready = 0; // Flag indicating data readiness
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for synchronizing access
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; // Condition variable for signaling

void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        pthread_mutex_lock(&mutex); // Lock the mutex
        while (data_ready) {
            pthread_cond_wait(&cond, &mutex); // Wait until data is consumed
        }
        buffer = i; // Produce data
        data_ready = 1; // Indicate data is ready
        printf("Produced: %d\n", i);
        pthread_cond_signal(&cond); // Signal the consumer
        pthread_mutex_unlock(&mutex); // Unlock the mutex
        sleep(1); // Simulate time-consuming production
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        pthread_mutex_lock(&mutex); // Lock the mutex
        while (!data_ready) {
            pthread_cond_wait(&cond, &mutex); // Wait until data is produced
        }
        printf("Consumed: %d\n", buffer);
        data_ready = 0; // Indicate data is consumed
        pthread_cond_signal(&cond); // Signal the producer
        pthread_mutex_unlock(&mutex); // Unlock the mutex
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to complete
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy the condition variable and mutex
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    return 0;
}

/*
        We lock the mutex around the while loop to ensure that the check and wait for the condition are done safely. 
        This prevents race conditions and makes sure that no other thread can change the shared data while the current 
        thread is checking and waiting. The mutex ensures only one thread can modify the shared data at a time, and the
        condition variable allows threads to wait efficiently without constantly checking.
*/