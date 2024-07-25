#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void* thread_function(void* arg) {
    printf("Thread is running\n");
    return NULL;
}

int main() {
    pthread_t thread;
    if (pthread_create(&thread, NULL, thread_function, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    // Wait for the thread to finish
    if (pthread_join(thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    printf("Thread has finished\n");
    return 0;
}
