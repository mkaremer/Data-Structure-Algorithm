#include <stdio.h>
#include "hashmap.h"

int main() {
    HashMap map;
    initHashMap(&map);

    insert(&map, 1, 100);
    insert(&map, 2, 200);
    insert(&map, 3, 300);

    printf("Value for key 1: %d\n", search(&map, 1));
    printf("Value for key 2: %d\n", search(&map, 2));
    printf("Value for key 3: %d\n", search(&map, 3));
    printf("Value for key 4: %d\n", search(&map, 4));

    delete(&map, 2);

    printf("Value for key 2 after deletion: %d\n", search(&map, 2));

    freeHashMap(&map);

    return 0;
}
