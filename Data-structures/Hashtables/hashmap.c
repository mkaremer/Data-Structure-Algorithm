#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

// Initialize the hashmap
void initHashMap(HashMap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i] = NULL; // Set each slot in the table to NULL
    }
}

// Hash function to map a key to an index
int hashFunction(int key) {
    return key % TABLE_SIZE; // Simple modulo-based hash function
}

// Insert a key-value pair into the hashmap
void insert(HashMap* map, int key, int value) {
    int index = hashFunction(key); // Calculate the index for the key
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode)); // Allocate memory for a new node
    if (!newNode) {
        printf("Memory allocation error\n"); // Print error message if memory allocation fails
        return;
    }
    newNode->key = key; // Set the key for the new node
    newNode->value = value; // Set the value for the new node
    newNode->next = map->table[index]; // Point the new node to the current head of the chain
    map->table[index] = newNode; // Set the new node as the head of the chain
}

// Search for a value by key in the hashmap
int search(HashMap* map, int key) {
    int index = hashFunction(key); // Calculate the index for the key
    HashNode* node = map->table[index]; // Get the head of the chain at the index
    while (node) {
        if (node->key == key) {
            return node->value; // Return the value if the key matches
        }
        node = node->next; // Move to the next node in the chain
    }
    return -1; // Return -1 if the key is not found
}

// Delete a key-value pair from the hashmap
void delete(HashMap* map, int key) {
    int index = hashFunction(key); // Calculate the index for the key
    HashNode* node = map->table[index]; // Get the head of the chain at the index
    HashNode* prev = NULL; // Pointer to the previous node
    while (node) {
        if (node->key == key) {
            if (prev) {
                prev->next = node->next; // Bypass the node to delete it
            } else {
                map->table[index] = node->next; // Set the head of the chain to the next node
            }
            free(node); // Free the memory of the deleted node
            return;
        }
        prev = node; // Move the previous pointer to the current node
        node = node->next; // Move to the next node in the chain
    }
}

// Free the memory allocated for the hashmap
void freeHashMap(HashMap* map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* node = map->table[i]; // Get the head of the chain at the index
        while (node) {
            HashNode* temp = node; // Store the current node in a temporary variable
            node = node->next; // Move to the next node in the chain
            free(temp); // Free the memory of the current node
        }
        map->table[i] = NULL; // Set the head of the chain to NULL
    }
}
