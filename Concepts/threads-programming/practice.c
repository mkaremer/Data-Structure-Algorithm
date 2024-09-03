/*
   p, p, p ----- c

    1. race condition: mutex
    2. if buffer is full : semaphores, 3
    3. if buffer is empty: 10 empty slots sem_empty = 0
*/

#define NUM_THREADS 2
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
sem_t = isEmpty;
sem_t = isFull;

int buffer[10];
int count = 0;

void* producer(void* args){
    int y = 9;
    sem_wait(isEmpty);
    pthread_mutex_lock(&lock);
    //produce
    buffer[count] = y;
    count++;
    pthread_mutex_unlock(&lock);
    sem_post(isFull);

    return NULL;
}

void* consumer(void* args){
    //consume
    sem_wait(isFull);
    pthread_mutex_lock(&lock);
    printf("%d\n", buffer[count]);
    count--;

    return NULL;
    pthread_mutex_unlock(&lock);
    sem_post(isEmpty);
}

int main(){
    
    sem_init(&isEmpty, 0, 10);
    sem_init(&isFull, 0, 0);

    pthread_t threads[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++){
        if(i % 2 == 0){
            if (pthread_create(&threads[i], NULL, producer, NULL) != 0){
                perror("Thread creation faile\n");
                return 2;
            }
        }
        else{
            if (pthread_create(&threads[i], NULL, consumer, NULL) != 0){
                perror("Thread creation faile\n");
                return 2;
            }
        }
    }

    for(int i = 0; i < NUM_THREADS; i++){
        if(pthread_join(threads[i], NULL)){
            perror("Thread fail to join\n");
            return 2;
        }
    }

    sem_destroy(isEmpty);
    sem_destroy(isFull);

    return 0;
}
