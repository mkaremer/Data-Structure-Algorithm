/*
                THREADS IN C
    - A thread is the smallest unit of a process that can be scheduled by the operating system
    - threads programming allows you execute multiple threads concurrently within the same process
                sharing the same memory space.
    - This improve performanc of your program by making better use of CPU resources especailly in multi-core systems
    - multithreading: the process of executing multiple threads simultaneously to achieve parallelism

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

/*
           CONCURRENCY VS PARALLEL EXECUTION
    1. Parallel execution
        - What it is: Doing multiple tasks exactly at the same time.
        - How it works: Uses multiple processors or cores.
        - Benefit: Faster performance by splitting work.
        - Example: Multiple people working on different parts of a puzzle at the same time.
    
    2. Concurrent execution:
        - What it is: Making it look like multiple tasks are happening at the same time by switching between them quickly.
        - How it works: Can be done with one processor by quickly switching tasks.
        - Benefit: Better responsiveness and resource use.
        - Example: A single person working on different parts of a puzzle by switching between them quickly.
    
    3. Key differences:
        - Parallel: Tasks are done at the same time using multiple processors.
        - Concurrent: Tasks take turns quickly, giving the illusion of simultaneity, and can use just one processor.

*/

/*
            SYNCRONIZATION IN MULTITHREADING
    Why it matters:
        - Race conditions: Multiple threads accessing shared data at the same time can cause errors
        - Data integrity: keeps data correct and consistent
        - Avoid deadlocks: prevents threads from getting stuck waiting for each other

    Common synchronization tools
        
        1. MUTEX (Mutual Exclusion)
            - purpose: Ensures only one thread accesses a resource at a time
            - How it works:
                - lock: A thread locks the resource
                - unlock: the thread unlocks it after use
*/
//Example of Mutex
pthread_mutex_t lock;           // Declare a mutex variable
pthread_mutex_init(&lock, NULL); // Initialize the mutex

pthread_mutex_lock(&lock);       // Lock the mutex
// Access shared resource        // Critical section: code that accesses the shared resource
pthread_mutex_unlock(&lock);     // Unlock the mutex

pthread_mutex_destroy(&lock);    // Destroy the mutex

/*
        2. Spinlock
            - Purpose: similar to mutex but spins in a loop waiting for the lock.
            - when to use: For short tasks to avoid wasting CPU cycles
*/
//exmaple of spinlock
pthread_spinlock_t spinlock;                    // Declare a spinlock variable
pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE); // Initialize the spinlock

pthread_spin_lock(&spinlock);                   // Lock the spinlock
// Access shared resource                       // Critical section: code that accesses the shared resource
pthread_spin_unlock(&spinlock);                 // Unlock the spinlock

pthread_spin_destroy(&spinlock);                // Destroy the spinlock

/*
        3. Semaphore
            - purpose: controls access to a resource by multiple threads
            - how it works: 
                - wait: decreases the semaphore value
                - signal: increases the semaphore value
*/
//exmaple of semaphore
sem_t semaphore;                // Declare a semaphore variable
sem_init(&semaphore, 0, 1);     // Initialize the semaphore with an initial value of 1

sem_wait(&semaphore);           // Wait (decrease) on the semaphore
// Access shared resource      // Critical section: code that accesses the shared resource
sem_post(&semaphore);           // Signal (increase) the semaphore

sem_destroy(&semaphore);        // Destroy the semaphore


/*
            4. Condition Variable
                - puporse: Blocks until the condition is signaled
                - signal: wakes up waiting threads
*/
// Example of condition variable
pthread_cond_t cond;                // Declare a condition variable
pthread_mutex_t lock;               // Declare a mutex variable

pthread_mutex_init(&lock, NULL);    // Initialize the mutex
pthread_cond_init(&cond, NULL);     // Initialize the condition variable

pthread_mutex_lock(&lock);          // Lock the mutex
while (!condition) {                // Check the condition in a loop
    pthread_cond_wait(&cond, &lock); // Wait for the condition variable to be signaled
}
// Condition met, access shared resource // Critical section: code that accesses the shared resource
pthread_mutex_unlock(&lock);        // Unlock the mutex

pthread_cond_signal(&cond);         // Signal the condition variable

pthread_mutex_destroy(&lock);       // Destroy the mutex
pthread_cond_destroy(&cond);        // Destroy the condition variable
