#include <stdio.h>
#include "stack_array.h"

int main() {
    Stack s;
    initStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("Top element is %d\n", peek(&s));
    printf("Stack: ");

    while (!isEmpty(&s)) {
        printf("%d ", pop(&s));
    }
    printf("\n");

    return 0;
}
