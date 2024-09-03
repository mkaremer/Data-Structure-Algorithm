
/*
    5 6 3 4
    - need to keep order: dlist
        4->1->2
    - get elt in constant time: 
    1: ref to node, 2:2, 3:3, 4:4
    key: key
    value: ref to node

*/
#define HASH_SIZE 100

typedef struct DListNode{
    int value;
    int key;
    struct DListNode next;
    struct DListNode prev;
} DListNode;

typedef struct LRUCache{
    int capacity;
    int size;
    DListNode* head;
    DListNode* tail;
    DListNode* hashtable[HASH_SIZE];
} LRUCache;
