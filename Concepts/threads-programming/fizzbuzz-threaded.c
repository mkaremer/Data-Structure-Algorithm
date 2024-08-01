/*
        MULTITHREADED FIZZBUZZ PROBLEM
        
    In the classic problem fizzbuzz you are told to print numbers from 1 to n. 
    however when the number is divisible by 3, print "fizz", when it is divisible by 5,
    print "buzz". when it is divisible by 3 and 5, print "FizzBuzz". in this problem
    you area sked to dod this in a multithreaded way. implement a multithreaded version of fizzbuzz.
    one thread checks for divisibility of 3 and prints "fizz", another thread is responsible for 
    divisibility of 3 and 5 and prints "fizzBuzz". A fourth thread does the numbers.
*/
#include <pthread.h>  
#include <stdio.h>    
#include <stdlib.h>   
#include <unistd.h>  

#define MAX_NUMBER 30 // Define the maximum number for the FizzBuzz sequence

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;  // Initialize a mutex lock for thread synchronization
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;    // Initialize a condition variable for thread synchronization
int current_number = 1;                            // Initialize the starting number for the sequence

// Function for the 'fizz' thread to print "Fizz"
void *fizz(void *arg) {
    while (1) {  // Loop indefinitely until break
        pthread_mutex_lock(&lock); // Lock the mutex to ensure exclusive access to shared data
        while (current_number <= MAX_NUMBER && (current_number % 3 != 0 || current_number % 5 == 0)) {
            // Wait for the condition variable if the current number is not divisible by 3
            // or if it's divisible by 5 (since it should print FizzBuzz instead)
            pthread_cond_wait(&cond, &lock);
        }
        if (current_number > MAX_NUMBER) { // Check if the current number exceeds the limit
            pthread_mutex_unlock(&lock); // Unlock the mutex before breaking
            break; // Exit the loop
        }
        printf("Fizz\n"); // Print "Fizz" for numbers divisible by 3 but not by 5
        current_number++; // Increment the current number
        pthread_cond_broadcast(&cond); // Signal all waiting threads to wake up
        pthread_mutex_unlock(&lock); // Unlock the mutex
    }
    return NULL; // Return NULL at the end of the thread function
}

// Function for the 'buzz' thread to print "Buzz"
void *buzz(void *arg) {
    while (1) { // Loop indefinitely until break
        pthread_mutex_lock(&lock); // Lock the mutex to ensure exclusive access to shared data
        while (current_number <= MAX_NUMBER && (current_number % 5 != 0 || current_number % 3 == 0)) {
            // Wait for the condition variable if the current number is not divisible by 5
            // or if it's divisible by 3 (since it should print FizzBuzz instead)
            pthread_cond_wait(&cond, &lock);
        }
        if (current_number > MAX_NUMBER) { // Check if the current number exceeds the limit
            pthread_mutex_unlock(&lock); // Unlock the mutex before breaking
            break; // Exit the loop
        }
        printf("Buzz\n"); // Print "Buzz" for numbers divisible by 5 but not by 3
        current_number++; // Increment the current number
        pthread_cond_broadcast(&cond); // Signal all waiting threads to wake up
        pthread_mutex_unlock(&lock); // Unlock the mutex
    }
    return NULL; // Return NULL at the end of the thread function
}

// Function for the 'fizzbuzz' thread to print "FizzBuzz"
void *fizzbuzz(void *arg) {
    while (1) { // Loop indefinitely until break
        pthread_mutex_lock(&lock); // Lock the mutex to ensure exclusive access to shared data
        while (current_number <= MAX_NUMBER && current_number % 15 != 0) {
            // Wait for the condition variable if the current number is not divisible by 3 and 5
            pthread_cond_wait(&cond, &lock);
        }
        if (current_number > MAX_NUMBER) { // Check if the current number exceeds the limit
            pthread_mutex_unlock(&lock); // Unlock the mutex before breaking
            break; // Exit the loop
        }
        printf("FizzBuzz\n"); // Print "FizzBuzz" for numbers divisible by both 3 and 5
        current_number++; // Increment the current number
        pthread_cond_broadcast(&cond); // Signal all waiting threads to wake up
        pthread_mutex_unlock(&lock); // Unlock the mutex
    }
    return NULL; // Return NULL at the end of the thread function
}

// Function for the 'number' thread to print numbers not divisible by 3 or 5
void *number(void *arg) {
    while (1) { // Loop indefinitely until break
        pthread_mutex_lock(&lock); // Lock the mutex to ensure exclusive access to shared data
        while (current_number <= MAX_NUMBER && (current_number % 3 == 0 || current_number % 5 == 0)) {
            // Wait for the condition variable if the current number is divisible by 3 or 5
            pthread_cond_wait(&cond, &lock);
        }
        if (current_number > MAX_NUMBER) { // Check if the current number exceeds the limit
            pthread_mutex_unlock(&lock); // Unlock the mutex before breaking
            break; // Exit the loop
        }
        printf("%d\n", current_number); // Print the current number
        current_number++; // Increment the current number
        pthread_cond_broadcast(&cond); // Signal all waiting threads to wake up
        pthread_mutex_unlock(&lock); // Unlock the mutex
    }
    return NULL; // Return NULL at the end of the thread function
}

int main() {
    pthread_t fizz_thread, buzz_thread, fizzbuzz_thread, number_thread; // Declare thread identifiers

    // Create threads for each task
    pthread_create(&fizz_thread, NULL, fizz, NULL); // Create fizz thread
    pthread_create(&buzz_thread, NULL, buzz, NULL); // Create buzz thread
    pthread_create(&fizzbuzz_thread, NULL, fizzbuzz, NULL); // Create fizzbuzz thread
    pthread_create(&number_thread, NULL, number, NULL); // Create number thread

    // Wait for all threads to finish
    pthread_join(fizz_thread, NULL); // Wait for fizz thread to finish
    pthread_join(buzz_thread, NULL); // Wait for buzz thread to finish
    pthread_join(fizzbuzz_thread, NULL); // Wait for fizzbuzz thread to finish
    pthread_join(number_thread, NULL); // Wait for number thread to finish

    // Clean up
    pthread_mutex_destroy(&lock); // Destroy the mutex
    pthread_cond_destroy(&cond); // Destroy the condition variable

    return 0; // Return 0 to indicate successful execution
}
