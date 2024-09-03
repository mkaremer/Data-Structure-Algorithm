typedef struct Node{
    int val;
    struct Node* next;
} Node;

typedef struct Stack{
    Node* top;
} Stack;

void stackInit(Stack* s){
    s->top = NULL;
}

bool isEmpty(Stack* s){
    return s->top == NULL;
}

void push(Stack* s, int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        fprintf(strr, "Mem alloc failed\n");
        return;
    }
    newNode->value = data;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack* s){
    if(s->top == NULL){
        printf("Stack empty\n");
        return;
    }
    Node* tmp = s->top;
    int popped = tmp->data;
    s->top = tmp->next;
    free(tmp);

    return popped;
}

void freeStack(Stack* s){
    Node* current = NULL;
    while(s->top != NULL){
        current = s->top;
        s->top = current->next;
        free(current);
    }
}