#include <stdio.h>
#include <stdlib.h>

// Define the node structure
typedef struct Node {
    int data;               // Integer data field
    struct Node* next;      // Pointer to the next node
} Node;
/*
                tyepedef keword
            -  creates a new name (alias) for an existing type.
            - In the above Node struct typedef allows you to use Node instead of struct Node, 
                    making the code cleaner and easier to read.
*/

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // Allocate memory for a new node
    if (!newNode) {                               // Check if memory allocation failed
        fprintf(stderr, "Memory allocation failed\n");               // Print an error message
        //By using fprintf(stderr, ...), you ensure that error messages are appropriately handled.
        return NULL;                              // Return NULL if memory allocation failed
    }
    newNode->data = data;                         // Set the data field of the new node
    newNode->next = NULL;                         // Initialize the next pointer to NULL
    return newNode;                               // Return the new node
}

// Function to insert a node at the beginning of the list
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);             // Create a new node

    // Check if node creation failed
    if (!newNode){
        return; 
    } 
                           
    newNode->next = *head;                        // Point the new node's next to the current head
    *head = newNode;                              // Update the head to the new node
}

// Function to insert a node at the end of the list
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);             // Create a new node
    if (!newNode){
        return;
    }                         // Check if node creation failed

    if (*head == NULL) {                          // If the list is empty
        *head = newNode;                          // Set the head to the new node
        return;
    }

    Node* temp = *head;                           // Temporary pointer to traverse the list
    while (temp->next != NULL) {                  // Traverse to the last node
        temp = temp->next;
    }
    temp->next = newNode;                         // Set the next of the last node to the new node
}

// Function to delete a node with a specific value
void deleteNode(Node** head, int key) {
    Node* temp = *head;                           // Temporary pointer to traverse the list
    Node* prev = NULL;                            // Pointer to keep track of the previous node

    if (temp != NULL && temp->data == key) {      // If the head node itself holds the key
        *head = temp->next;                       // Update the head to the next node
        free(temp);                               // Free the old head node
        return;
    }

    while (temp != NULL && temp->data != key) {   // Traverse the list to find the key
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {                           // If the key was not found
        printf("Key not found\n");                // Print an error message
        return;
    }

    prev->next = temp->next;                      // Unlink the node from the list
    free(temp);                                   // Free the node
}

// Function to free the entire list
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Function to display the list
void displayList(Node* head) {
    Node* temp = head;                            // Temporary pointer to traverse the list
    while (temp != NULL) {                        // Traverse the list
        printf("%d -> ", temp->data);             // Print the data of each node
        temp = temp->next;
    }
    printf("NULL\n");                             // Print NULL at the end of the list
}

// Main function to test the linked list implementation
int main() {
    Node* head = NULL;                            // Initialize the head to NULL

    insertAtEnd(&head, 10);                       // Insert 10 at the end of the list
    insertAtEnd(&head, 20);                       // Insert 20 at the end of the list
    insertAtEnd(&head, 30);                       // Insert 30 at the end of the list
    displayList(head);                            // Display the list

    insertAtBeginning(&head, 5);                  // Insert 5 at the beginning of the list
    displayList(head);                            // Display the list

    deleteNode(&head, 20);                        // Delete the node with data 20
    displayList(head);                            // Display the list

    //free the allocated memory
    freeList(head);

    return EXIT_SUCCESS;                   // Return 0 to indicate successful execution
}

/*
                    Node** head: WHY DOUBLE POINTER???
        - Pass by value vs passs by reference in C.
        - This basically allows function to modify the head ptr of llist in the caller's scope
                ensuring that the new node is correctly added to the beginning of the list


                LONG EXPLANATION:
        
        Head Pointer Needs to Be Modified:
The head of a linked list is the starting point of the list. If you want to insert a new node at 
the beginning, the head pointer itself needs to be updated to point to the new node.

If the head pointer were passed by value (Node* head), any changes made to it within 
the function would not affect the actual head pointer outside the function. 

This is because passing by value creates a copy of the head pointer, 
and changes to this copy do not affect the original head pointer.
By passing the head pointer by reference (using a double pointer), 
the function can modify the actual head pointer in the caller's scope.
 */