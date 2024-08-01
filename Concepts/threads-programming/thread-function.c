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
    // pthread_create returns:
    // 0: when the thread was successfully created
    // Non-zero: an error occured
    if (pthread_create(&thread, NULL, thread_function, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    // Wait for the thread to finish
    // pthread_join returns:
    // 0: when the thread was successfully created
    // Non-zero: an error occured
    if (pthread_join(thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    printf("Thread has finished\n");
    return 0;
}
/*
                    THREAD FUNCTION
    A thread function is a function that a thread runs in a multithreaded program. 
    It must return void * and take a void * argument to be flexible with any data type.
*/

void *thread_function2(void* args){
    //convert argument to int pointer
    int *num = (int *) args;
    printf("Thread number %d\n", *num);
    return NULL;
}
int main() {
    pthread_t thread_id;
    int thread_arg = 42;

    // Create a new thread
    pthread_create(&thread_id, NULL, thread_function, (void *)&thread_arg);

    // Wait for the thread to finish
    pthread_join(thread_id, NULL);

    return 0;
}

/*
        PASSING MULTIPLE ARGUMENTS
    Use a structure to pass multiple arguments.

*/
typedef struct{
    int arg1;
    float arg2;
} thread_args;

void* thread_function3(void* args){
    thread_args *args = (thread_args *)args;
    printf("Arg1: %d, Arg2: %f\n", args->arg1, args->arg2);
    return NULL;
}

int main(){
    pthread_t thread_id:
    thread_args args = {42, 3.14};

    if (pthread_create(thread_id, NULL, thread_fucntion3, (void *)&args)){
        fprintf(stderr, "Thread creation failed\n");
        return 1;
    }

    if (pthread_join(thread_id, NULL)){
        fprintf(stderr, "Thread join failed\n");
        return 2;
    }
}

/*
            RETURNING A VALUE FROM THE THREAD FUNCTION

    - The thread function doesn't always have to return NULL
    - It returns a void *, so you can return any type of data by casting it to void *
    - This is useful if you need to send a result back to the main thread or 
                another waiting thread.
*/
//Example:

void *thread_function(void *arg) {
    int *num = (int *)arg;            // Cast the argument to int pointer
    int *result = malloc(sizeof(int)); // Allocate memory for the result
    *result = (*num) * 2;              // Calculate the result
    return (void *)result;             // Return the result
}

int main() {
    pthread_t thread_id;
    int thread_arg = 42;
    int *thread_result;

    // Create the thread
    pthread_create(&thread_id, NULL, thread_function, (void *)&thread_arg);

    // Wait for the thread to finish and get the result
    // void **: pthread_join expect a pointer to "void *" that is why there is double pointer (**). 
    // it needs it to store the return value
    pthread_join(thread_id, (void **)&thread_result);

    // Print the result
    printf("Thread result: %d\n", *thread_result);

    // Free the allocated memory
    free(thread_result);

    return 0;
}

/*
        THREADS ATTRIBUTES
   -  The second argument in pthread_create is a pointer to a pthread_attr_t structure, 
   - which lets you customize thread attributes. If you pass NULL, default attributes are used.

   Common thread attributes

   - Detached State: Determines if a thread can be joined or if it cleans up automatically when done.
   - Stack Size: Specifies the thread's stack size.
   - Scheduling Policy: Defines how the thread is scheduled.

   How to use thread attributes

   1. Initialize the Attribute:
        pthread_attr_init(&attr); // Initialize the attribute with default values

   2. Set the Attribute (e.g., Detached State):
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); // Set thread to be detached

   3. Create the Thread with Attributes:
        pthread_create(&thread_id, &attr, thread_function, (void *)&thread_arg); // Create thread with custom attributes

   4. Destroy the Attribute:
        pthread_attr_destroy(&attr); // Free resources used by the attribute
*/
// Example:
void *thread_function(void *arg) {
    int *num = (int *)arg;
    printf("Thread number: %d\n", *num);
    return NULL;
}

int main() {
    pthread_t thread_id;
    pthread_attr_t attr;
    int thread_arg = 42;

    pthread_attr_init(&attr); // Initialize the attribute
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); // Set to detached

    pthread_create(&thread_id, &attr, thread_function, (void *)&thread_arg); // Create thread
    pthread_attr_destroy(&attr); // Destroy the attribute

    printf("Thread created in detached state\n");
    pthread_exit(NULL); // Ensure main thread waits for other threads

    return 0;
}