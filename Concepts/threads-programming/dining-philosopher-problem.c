/*
            THE DINING PHILOSOPHER PROBLEM

    The Dining Philosophers Problem is a classic synchronization and concurrency problem that illustrates 
    the challenges of allocating resources among multiple processes without causing deadlock or resource starvation. 
    It was first formulated by computer scientist Edsger Dijkstra in 1965.

            PROBLEM DESCRIPTION

    Imagine five philosophers sitting around a circular table. In front of each philosopher is a plate of spaghetti, 
    and between each pair of philosophers is a single fork. Philosophers spend their time thinking and eating. 
    However, a philosopher needs both the left and right forks to eat. The challenge is to design a system 
    where the philosophers can eat without causing a deadlock or starving any philosopher.

                KEY CONCENPTS
    - Resources: The forks represent limited resources that need to be shared among philosophers.
    - Deadlock: Occurs when each philosopher picks up their left fork and waits indefinitely for the right fork, 
            which is held by the neighboring philosopher.
    - Starvation: Occurs if a philosopher is unable to access both forks repeatedly, while others keep eating.

            THE DINING PHILOSOPHERS PROBLEM
    The problem can be visualized as follows:
        - Five philosophers (P1, P2, P3, P4, P5) are sitting around a table.
        - Five forks (F1, F2, F3, F4, F5) are placed between each pair of philosophers.
        - Philosophers need two forks to eat, one from the left and one from the right.
        - Philosophers alternate between thinking and eating.

        CHALLENGES
    - Deadlock: If every philosopher picks up the fork on their left simultaneously, all will wait for 
                the fork on their right, resulting in a deadlock.
    - Starvation: Some philosophers might get the opportunity to eat more often than others, 
                leading to starvation for some.

        SOLUTION TO THE DINING PHILOSOPHER PROBLEM

    1. Arbitrator solution:
        - Use a mediator to limit the number of philosophers trying to pick up forks at the same time to four. 
                    This ensures at least one philosopher can eat.

    2. resource hierarchy solution
        - Number the forks and have each philosopher pick up the lower-numbered fork first. 
                This strict order prevents deadlocks by avoiding circular waiting.

    3. chandy/misra solution
        - Use a token system where each fork is a token. Philosophers can only pick up a fork if they have the token,
                 ensuring deadlock prevention through strict ordering.

    4. Asymmetric solution:
        - Change the behavior of one philosopher to break symmetry.
        -  For example, one philosopher always picks up the right fork first and then the left fork. 
                This breaks the symmetry and helps prevent deadlocks.
*/

//Simple implementation using mutexes
// CAUTION: Deadlock Potential: 
// The below simple solution can still lead to deadlock if all philosophers pick up their left forks simultaneously.
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1); // Simulate thinking

        // Pick up forks
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);

        // Eat
        printf("Philosopher %d is eating.\n", id);
        sleep(1); // Simulate eating

        // Put down forks
        pthread_mutex_unlock(&forks[right]);
        pthread_mutex_unlock(&forks[left]);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

/*
        ASYMMETRIC SOLUTION: which solves the deadlock from the above solution
    CAUTION: this solution only solves the deadlock. it doesn't solve starvation.
*/
#define NUM_PHILOSOPHERS 5  // Define the number of philosophers and forks

pthread_mutex_t forks[NUM_PHILOSOPHERS];  // Declare an array of mutexes representing forks

// Function for philosopher threads
void *philosopher(void *arg) {
    int id = *(int *)arg;  // Get the philosopher's ID from the argument
    int left = id;         // Define the left fork index as the philosopher's ID
    int right = (id + 1) % NUM_PHILOSOPHERS;  // Define the right fork index, wrapping around

    while (1) {  // Loop indefinitely
        printf("Philosopher %d is thinking.\n", id);  // Print thinking status
        sleep(1);  // Simulate thinking with sleep

        if (id % 2 == 0) {  // Check if the philosopher ID is even
            // Even philosopher picks up left fork first
            pthread_mutex_lock(&forks[left]);  // Lock the left fork
            pthread_mutex_lock(&forks[right]); // Then lock the right fork
        } else {
            // Odd philosopher picks up right fork first
            pthread_mutex_lock(&forks[right]); // Lock the right fork
            pthread_mutex_lock(&forks[left]);  // Then lock the left fork
        }

        // Eat
        printf("Philosopher %d is eating.\n", id);  // Print eating status
        sleep(1);  // Simulate eating with sleep

        // Put down forks
        pthread_mutex_unlock(&forks[left]);  // Unlock the left fork
        pthread_mutex_unlock(&forks[right]); // Unlock the right fork
    }
    return NULL;  // Return NULL at the end of the thread function
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];  // Declare an array of thread identifiers
    int ids[NUM_PHILOSOPHERS];  // Declare an array to hold philosopher IDs

    // Initialize mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);  // Initialize each fork mutex
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;  // Set the philosopher ID
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);  // Create a thread for each philosopher
    }

    // Wait for threads to finish (though they run indefinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);  // Wait for each philosopher thread to complete
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);  // Destroy each fork mutex
    }

    return 0;  // Return 0 to indicate successful execution
}

/*
        This solution address starvation.
    - by adding a wait queue.
        - the queue will trach which philosophers are waiting to eat and give priority to those
                who have been waiting the longest
*/
#define NUM_PHILOSOPHERS 5  // Define the number of philosophers and forks

pthread_mutex_t forks[NUM_PHILOSOPHERS];  // Declare an array of mutexes representing forks
pthread_mutex_t access_lock = PTHREAD_MUTEX_INITIALIZER;  // Initialize a mutex for controlling access to the eating order
int eating_order[NUM_PHILOSOPHERS];  // Array to maintain the order in which philosophers should eat
int next_to_eat = 0;  // Index of the next philosopher who should eat

// Function for philosopher threads
void *philosopher(void *arg) {
    int id = *(int *)arg;  // Get the philosopher's ID from the argument
    int left = id;         // Define the left fork index as the philosopher's ID
    int right = (id + 1) % NUM_PHILOSOPHERS;  // Define the right fork index, wrapping around

    while (1) {  // Loop indefinitely
        printf("Philosopher %d is thinking.\n", id);  // Print thinking status
        sleep(1);  // Simulate thinking with sleep

        pthread_mutex_lock(&access_lock);  // Lock the access lock to check the eating order
        // Check if it's this philosopher's turn to eat
        while (eating_order[next_to_eat] != id) {  // If it's not their turn
            pthread_mutex_unlock(&access_lock);  // Unlock access lock and wait
            sleep(1);  // Wait a bit before retrying
            pthread_mutex_lock(&access_lock);  // Lock the access lock again
        }
        pthread_mutex_unlock(&access_lock);  // Unlock access lock after confirming turn

        if (id % 2 == 0) {  // Check if the philosopher ID is even
            pthread_mutex_lock(&forks[left]);  // Lock the left fork first
            pthread_mutex_lock(&forks[right]); // Then lock the right fork
        } else {
            pthread_mutex_lock(&forks[right]); // Lock the right fork first
            pthread_mutex_lock(&forks[left]);  // Then lock the left fork
        }

        // Eat
        printf("Philosopher %d is eating.\n", id);  // Print eating status
        sleep(1);  // Simulate eating with sleep

        pthread_mutex_unlock(&forks[left]);  // Unlock the left fork
        pthread_mutex_unlock(&forks[right]); // Unlock the right fork

        pthread_mutex_lock(&access_lock);  // Lock access lock to update the eating order
        // Update next philosopher to eat
        next_to_eat = (next_to_eat + 1) % NUM_PHILOSOPHERS;  // Move to the next philosopher in order
        pthread_mutex_unlock(&access_lock);  // Unlock access lock after updating
    }
    return NULL;  // Return NULL at the end of the thread function
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];  // Declare an array of thread identifiers
    int ids[NUM_PHILOSOPHERS];  // Declare an array to hold philosopher IDs

    // Initialize mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);  // Initialize each fork mutex
        eating_order[i] = i;  // Set the initial eating order to the natural order of philosophers
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;  // Set the philosopher ID
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);  // Create a thread for each philosopher
    }

    // Wait for threads to finish (though they run indefinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);  // Wait for each philosopher thread to complete
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);  // Destroy each fork mutex
    }

    return 0;  // Return 0 to indicate successful execution
}