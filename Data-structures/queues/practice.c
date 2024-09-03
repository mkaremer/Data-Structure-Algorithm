typedef struct Node{
    int value;
    struct Node* next;
} Node;

typedef struct Queue{
    Node* front;
    Node* rear;
} Queue;

Node* createNode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode){
        fprintf(sterror, "Mem alloc failed\n");
        return NULL;
    }
    newNode->value = data;
    newNode->next = NULL;

    return newNode;
}

//create a queue
Queue* createQueue(){
    
}
//enqueue
void enqueue(Queue* q, int data){
    Node* newNode = createNode(data);
    if(!newNode){
        return;
    }
    //if queue empty
    if(q->rear == NULL){
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;  
}
// Function to remove an element from the queue (dequeue)
int dequeue(Queue* q) {
    if (q->front == NULL) {  // If the queue is empty
        fprintf(stderr, "Queue is empty\n");
        return -1;  // Return an error value
    }
    Node* temp = q->front;  // Store the front node
    int data = temp->data;  // Get the data from the front node
    q->front = q->front->next;  // Move the front to the next node

    if (q->front == NULL) {  // If the queue becomes empty
        q->rear = NULL;  // Set rear to NULL as well
    }
    free(temp);  // Free the old front node
    return data;  // Return the dequeued data
}
//dequeue
int dequeue(Queue q){
    //check empty
    if(q->front == NULL){
        return -1;
    }

    Node* tmp = q->front;
    q->front = tmp->next;
    int rtn = tmp->data;

    //fi queue becomes empty
    if(q->front == NULL){
        q->rear = NULL;
    }
    
    free(tmp);
    return rtn;
}