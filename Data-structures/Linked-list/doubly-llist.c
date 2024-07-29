#include <stdio.h>
#include <stdlib.h>

// Define a node structure for the doubly linked list
typedef struct Node {
    int data;               // Data part of the node
    struct Node* prev;      // Pointer to the previous node
    struct Node* next;      // Pointer to the next node
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Allocate memory for a new node
    if (newNode == NULL) {                       // Check if memory allocation failed
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;    // Initialize the data part of the node
    newNode->prev = NULL;    // Initialize the prev pointer to NULL
    newNode->next = NULL;    // Initialize the next pointer to NULL
    return newNode;          // Return the created node
}

// Function to insert a node at the end of the list
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data); // Create a new node
    if (newNode == NULL) {            // Check if node creation failed
        return;
    }

    if (*head == NULL) {              // If the list is empty
        *head = newNode;              // Set the new node as the head
        return;
    }

    Node* temp = *head;               // Temporary pointer to traverse the list
    while (temp->next != NULL) {      // Traverse to the last node
        temp = temp->next;
    }
    temp->next = newNode;             // Set the next of the last node to the new node
    newNode->prev = temp;             // Set the prev of the new node to the last node
}

// Function to insert a node at the beginning of the list
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data); // Create a new node
    if (newNode == NULL) {            // Check if node creation failed
        return;
    }

    if (*head == NULL) {              // If the list is empty
        *head = newNode;              // Set the new node as the head
        return;
    }

    newNode->next = *head;            // Set the next of the new node to the current head
    (*head)->prev = newNode;          // Set the prev of the current head to the new node
    *head = newNode;                  // Update the head to the new node
}

// Function to delete a node with a specific value
void deleteNode(Node** head, int key) {
    Node* temp = *head;               // Temporary pointer to traverse the list

    while (temp != NULL && temp->data != key) { // Traverse to find the node with the given key
        temp = temp->next;
    }

    if (temp == NULL) {               // If the node with the key was not found
        fprintf(stderr, "Node with data %d not found\n", key);
        return;
    }

     // If the node to be deleted is not the first node
    if (temp->prev != NULL) {
        // Set the next of the previous node to the next node 
        Node* prevNode = temp->prev;       
        prevNode>next = temp->next;
        // If the node to be deleted is the first node
    } else {
        // Update the head to the next node                         
        *head = temp->next;           
    }

    // If the node to be deleted is not the last node
    if (temp->next != NULL) {
        // Set the prev of the next node to the previous node         
        Node* nextNode = temp->next;
        nextNode->prev = temp->prev;
    }

    free(temp);                       // Free the memory of the deleted node
}

// Function to display the list in forward direction
void displayListForward(Node* head) {
    Node* temp = head;                // Temporary pointer to traverse the list
    while (temp != NULL) {            // Traverse the list
        printf("%d -> ", temp->data); // Print the data of each node
        temp = temp->next;            // Move to the next node
    }
    printf("NULL\n");                 // Print NULL at the end
}

// Function to display the list in backward direction
void displayListBackward(Node* head) {
    if (head == NULL) {               // If the list is empty, do nothing
        return;
    }

    Node* temp = head;                // Temporary pointer to traverse the list
    while (temp->next != NULL) {      // Traverse to the last node
        temp = temp->next;
    }

    while (temp != NULL) {            // Traverse the list backward
        printf("%d -> ", temp->data); // Print the data of each node
        temp = temp->prev;            // Move to the previous node
    }
    printf("NULL\n");                 // Print NULL at the end
}

// Main function to test the doubly linked list implementation
int main() {
    Node* head = NULL;                // Initialize the head to NULL

    // Insert elements at the end of the list
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);

    // Insert elements at the beginning of the list
    insertAtBeginning(&head, 5);
    insertAtBeginning(&head, 1);

    // Display the list in forward direction
    printf("List in forward direction:\n");
    displayListForward(head);

    // Display the list in backward direction
    printf("List in backward direction:\n");
    displayListBackward(head);

    // Delete a node and display the list again
    deleteNode(&head, 20);
    printf("List after deleting node with data 20:\n");
    displayListForward(head);

    // Free the list
    while (head != NULL) {            // Traverse the list
        Node* temp = head;            // Temporary pointer to hold the current node
        head = head->next;            // Move to the next node
        free(temp);                   // Free the memory of the current node
    }

    return EXIT_SUCCESS;              // Return success
}
