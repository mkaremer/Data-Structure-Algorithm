/*
                THREADS IN C

    - threads programming allows you execute multiple threads concurrently within the same process
                sharing the same memory space.
    - This improve performanc of your program by making better use of CPU resources especailly in multi-core systems

            BASICS OF THREADS

    - A thread is a smaller unit of a process that can be scheduled to run independently.
    - Multiple threads within a process share the same data space
    - which allows them to communicate easily, but they must be carefully managed to avoid conflicts.

        WHY USE THREADS

    - Concurrency: Run multiple tasks simultaneously.
    - Resource Sharing: Threads share the same memory space, which is efficient for data sharing.
    - Responsiveness: Keep a program responsive by performing long-running tasks in the background.

        CREATING THREADS
    
    - To work with threads in C, you typically use the POSIX thread library (pthread)
*/

#include <pthread.h> //  step1: pthread library
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//step 2: define a thread fucntion
// A thread function is a function that the thread will execute
//  It takes a void* argument and returns a void*.
void* thread_function(void* arg) {
    printf("Thread is running\n");
    return NULL;
}


//step 3: create a thread
// Use pthread_create to create a new thread.
int main() {
    /*
        - pthread_create: Creates a new thread.
        - Arguements:
            1. The first argument is a pointer to a pthread_t variable that will hold the thread identifier.
            2. The second argument is a pointer to a pthread_attr_t structure that can be used to specify 
                        thread attributes (set to NULL for default attributes).
            3. The third argument is the thread function.
            4. The fourth argument is the argument to the thread function (set to NULL in this case).
    */
    pthread_t thread;
    if (pthread_create(&thread, NULL, thread_function, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    /*
       - pthread_join: Waits for the specified thread to finish.
       - Arguments:
        - The first argument is the thread identifier.
        - The second argument is a pointer to the return value of the thread (set to NULL if not needed).

    */
    if (pthread_join(thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    printf("Thread has finished\n");
    return 0;
}

