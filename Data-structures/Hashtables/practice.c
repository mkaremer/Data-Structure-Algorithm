#define HASH_SIZE = 1000

typedef struct HashNode{
    int data;
    int key;
    struct HashNode* next;
} HashNode;

typedef struct HashMap{
    HashNode* table[HASH_SIZE];
} HashMap;

void initHashMap(HashMap* mp){
    for(int i = 0; i < HASH_SIZE; i++){
        mp->table[i] = NULL;
    }
}
int hashFunction(int key){
    return key % HASH_SIZE;
}

void insert(HashMap* mp, int value, int key){
    int index = hashFunction(key);
    //allocate memo of node
    HashNode* newNode = (HashNode*) malloc(sizeof(HashNode));
    if(newNode == NULL){
        return;
    }
    newNode->data = value;
    newNode->key = key;
    newNode->next = mp->table[index];
    mp->table[index] = newNode;
}

int search(HashMap* mp, int key){
    int index = hashFunction(key);
    HashNode* node = mp->table[index];

    while(node != NULL){
        if(node->key == key){
            return node->value;
        }
        node = node->next;
    }
    return -1;
}

bool delete(HashMap* mp, int key){
    int index = hashFunction(key);
    HashNode* node = mp->table[index];
    HashNode* prev = NULL;

    while(node != NULL){
        if(node->key = key){
            if(prev != NULL){
                prev->next = node->next;
            }
            else{
                mp->table[index] = node->next;
            }
            free(node);
            return true;
        }
        prev = node;
        node = node->next; 
    }
    return false;

}