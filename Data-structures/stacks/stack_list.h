#ifndef STACK_LIST_H   // Prevents multiple inclusions of the header file
#define STACK_LIST_H   // Defines the STACK_LIST_H macro

// Structure definition for a node in the linked list
typedef struct Node {
    int data;             // Data stored in the node
    struct Node* next;    // Pointer to the next node in the stack
} Node;

// Structure definition for the stack
typedef struct {
    Node* top;            // Pointer to the top node in the stack
} Stack;

// Function prototypes for stack operations
void initStack(Stack* s);       // Initializes the stack
int isEmpty(Stack* s);          // Checks if the stack is empty
void push(Stack* s, int value); // Pushes an element onto the stack
int pop(Stack* s);              // Pops an element from the stack
int peek(Stack* s);             // Returns the top element of the stack without removing it
void freeStack(Stack* s);       // Frees the memory allocated for the stack

#endif  // End of the conditional inclusion block
