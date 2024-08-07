/*
                    LRU Cache Problem

Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

    - LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
    - int get(int key) Return the value of the key if the key exists, otherwise return -1.
    - void put(int key, int value) Update the value of the key if the key exists. 
            Otherwise, add the key-value pair to the cache. If the number of keys exceeds 
            the capacity from this operation, evict the least recently used key.
    - The functions get and put must each run in O(1) average time complexity.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 1000  // Define the size of the hash table

// Definition of a doubly linked list node
typedef struct DListNode {
    int key;  // Key stored in the node
    int value;  // Value associated with the key
    struct DListNode* prev;  // Pointer to the previous node in the list
    struct DListNode* next;  // Pointer to the next node in the list
    struct DListNode* hashNext; // Pointer for handling hash collisions
} DListNode;

// Definition of the LRU Cache
typedef struct {
    int capacity;  // Maximum capacity of the cache
    int size;  // Current size of the cache
    DListNode* head;  // Pointer to the head of the doubly linked list
    DListNode* tail;  // Pointer to the tail of the doubly linked list
    DListNode* hashTable[HASH_SIZE];  // Hash table for fast access to nodes
} LRUCache;

// Function to create a new doubly linked list node
DListNode* createNode(int key, int value) {
    DListNode* node = (DListNode*)malloc(sizeof(DListNode));  // Allocate memory for the new node
    if (node == NULL) {  // Check for successful memory allocation
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    node->key = key;  // Set the key
    node->value = value;  // Set the value
    node->prev = node->next = node->hashNext = NULL;  // Initialize pointers to NULL
    return node;  // Return the newly created node
}

// Function to initialize the LRU Cache
LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));  // Allocate memory for the cache
    if (cache == NULL) {  // Check for successful memory allocation
        perror("Failed to allocate memory for LRUCache");
        exit(EXIT_FAILURE);
    }
    cache->capacity = capacity;  // Set the capacity
    cache->size = 0;  // Initialize the current size to 0
    cache->head = createNode(0, 0);  // Create a dummy head node
    cache->tail = createNode(0, 0);  // Create a dummy tail node
    cache->head->next = cache->tail;  // Link the head to the tail
    cache->tail->prev = cache->head;  // Link the tail to the head
    /*
        'memset': it is a standard f(x) in c that sets a block of memory to a specific value
        void* memset(void* ptr, int value, size_t num);
            ptr: pointer to a block of memory to fill
            value: the value to be set. this value is interpreted as an unsigned char and the function
                            sets each byte of block to this value
                            In thi struct the value zero is used here. in context of ptrs setting a memory block to zero
                                initializes all pointers to NULL which is represented by zero in C
            num: the number of bytes to be set to the value
    */
    memset(cache->hashTable, 0, sizeof(cache->hashTable));  // Initialize the hash table to NULL
    return cache;  // Return the initialized cache
}

// Helper function to add a node right after the head
void addNode(LRUCache* cache, DListNode* node) {
    node->next = cache->head->next;  // Set the node's next pointer to the first real node
    node->prev = cache->head;  // Set the node's previous pointer to the head
    cache->head->next->prev = node;  // Update the first real node's previous pointer
    cache->head->next = node;  // Update the head's next pointer to the new node
}

// Helper function to remove a node from the linked list
void removeNode(DListNode* node) {
    DListNode* prev = node->prev;  // Get the previous node
    DListNode* next = node->next;  // Get the next node
    prev->next = next;  // Bypass the current node
    next->prev = prev;  // Update the next node's previous pointer
}

// Helper function to move a node to the head
void moveToHead(LRUCache* cache, DListNode* node) {
    removeNode(node);  // Remove the node from its current position
    addNode(cache, node);  // Add it right after the head
}

// Helper function to remove the tail node
DListNode* popTail(LRUCache* cache) {
    DListNode* res = cache->tail->prev;  // Get the node before the tail (LRU node)
    removeNode(res);  // Remove this node from the list
    return res;  // Return the removed node
}

// Hash function for keys
int hashFunc(int key) {
    return key % HASH_SIZE;  // Return the hash index for a given key
}

// Function to get the value of the key if the key exists in the cache
int lRUCacheGet(LRUCache* cache, int key) {
    int hashIndex = hashFunc(key);  // Calculate the hash index
    DListNode* node = cache->hashTable[hashIndex];  // Get the list head at this index

    // Traverse the linked list at this hash index
    while (node != NULL) {
        if (node->key == key) {  // If the key is found
            moveToHead(cache, node);  // Move the accessed node to the head
            return node->value;  // Return the value associated with the key
        }
        node = node->hashNext;  // Move to the next node in the chain
    }
    return -1; // Return -1 if the key is not found
}

// Function to add a key-value pair to the cache
void lRUCachePut(LRUCache* cache, int key, int value) {
    int hashIndex = hashFunc(key);  // Calculate the hash index
    DListNode* node = cache->hashTable[hashIndex];  // Get the list head at this index

    // Check if the key exists in the hash table
    while (node != NULL) {
        if (node->key == key) {  // If the key is found
            node->value = value;  // Update the value
            moveToHead(cache, node);  // Move the node to the head
            return;  // Return after updating
        }
        node = node->hashNext;  // Move to the next node in the chain
    }

    // Create a new node if the key is not found
    DListNode* newNode = createNode(key, value);  // Create a new node
    addNode(cache, newNode);  // Add it to the front of the list

    // Insert the node into the hash table (handling collisions)
    newNode->hashNext = cache->hashTable[hashIndex];  // Chain it at the current index
    cache->hashTable[hashIndex] = newNode;  // Update the head of the chain

    cache->size++;  // Increase the cache size

    // If the cache size exceeds the capacity, remove the LRU item
    if (cache->size > cache->capacity) {
        DListNode* tail = popTail(cache);  // Pop the tail node
        int tailHashIndex = hashFunc(tail->key);  // Calculate the hash index of the tail node

        // Remove from hash table
        DListNode* cur = cache->hashTable[tailHashIndex];  // Get the head of the chain
        DListNode* prev = NULL;  // Previous node pointer
        while (cur != NULL) {  // Traverse the chain
            if (cur == tail) {  // If the current node is the tail
                if (prev != NULL) {
                    prev->hashNext = cur->hashNext;  // Bypass the current node
                } else {
                    cache->hashTable[tailHashIndex] = cur->hashNext;  // Update the head of the chain
                }
                break;  // Exit the loop once the node is found
            }
            prev = cur;  // Move prev to cur
            cur = cur->hashNext;  // Move to the next node in the chain
        }

        free(tail);  // Free the memory of the tail node
        cache->size--;  // Decrease the cache size
    }
}

// Function to free the LRU Cache
void lRUCacheFree(LRUCache* cache) {
    DListNode* current = cache->head;  // Start from the head
    while (current != NULL) {
        DListNode* temp = current;  // Temporary pointer to the current node
        current = current->next;  // Move to the next node
        free(temp);  // Free the current node
    }
    free(cache);  // Free the cache structure itself
}

// Example usage
int main() {
    LRUCache* lRUCache = lRUCacheCreate(2);  // Create a new LRU cache with capacity 2
    lRUCachePut(lRUCache, 1, 1);  // Insert key-value pair (1, 1)
    lRUCachePut(lRUCache, 2, 2);  // Insert key-value pair (2, 2)
    printf("Get 1: %d\n", lRUCacheGet(lRUCache, 1)); // returns 1
    lRUCachePut(lRUCache, 3, 3);  // Insert key-value pair (3, 3), evict key 2
    printf("Get 2: %d\n", lRUCacheGet(lRUCache, 2)); // returns -1 (not found)
    lRUCachePut(lRUCache, 4, 4);  // Insert key-value pair (4, 4), evict key 1
    printf("Get 1: %d\n", lRUCacheGet(lRUCache, 1)); // returns -1 (not found)
    printf("Get 3: %d\n", lRUCacheGet(lRUCache, 3)); // returns 3
    printf("Get 4: %d\n", lRUCacheGet(lRUCache, 4)); // returns 4

    lRUCacheFree(lRUCache);  // Free the cache
    return 0;  // Return 0 to indicate successful execution
}
