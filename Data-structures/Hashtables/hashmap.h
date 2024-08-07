#ifndef HASHMAP_H
#define HASHMAP_H

#define TABLE_SIZE 100

typedef struct HashNode {
    int key;                // Key for the hash node
    int value;              // Value associated with the key
    // Pointer to the next node in the chain
    // This is helpful for handling collisions in the hashtable
    struct HashNode* next;  
} HashNode;

// Array of pointers to hash nodes, where each pointer points to HashNode
// Each entry in the array represents a bucket in the hash table
typedef struct {
    HashNode* table[TABLE_SIZE];
} HashMap;

void initHashMap(HashMap* map);
int hashFunction(int key);
void insert(HashMap* map, int key, int value);
int search(HashMap* map, int key);
void delete(HashMap* map, int key);
void freeHashMap(HashMap* map);

#endif
