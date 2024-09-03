/*
        Threads
    def: it lightweigh process and it is a unit of a process
    threads share the same recourses
    need to be syncronized

*/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_THREADS 10

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int num = 10;

//thread function
void* printSomething(void* args){
    // int num = *(int*)args;
    pthread_mutex_lock(&lock);
    num++;
    printf("%d, after number incremented\n", num);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(){
    pthread_t mythread[NUM_THREADS];
    // pthread_mutex_init(&lock, NULL);
    //create threads
    for(int i = 0; i < NUM_THREADS; i++){
        if(pthread_create(&mythread[i], NULL, printSomething, NULL)){
            printf("Theread creation failed\n");
            return 2;
        }
    }
    

    //wait threads
    for(int i = 0; i < NUM_THREADS; i++){
        if(pthread_join(mythread[i], NULL)){
            printf("Theread join failed\n");
            return 2;
        }
    }
    
    return 0;
}