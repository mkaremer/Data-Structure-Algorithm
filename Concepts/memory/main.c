/**
                            C TUTORIAL
            1. SEGMANTATION FAULT
    - aka segfault: it is an error that happens when the program tries to access a memory location 
                        that is not allowed to access.
    
            a. CAUSES OF SEGFAULT
 */

 //  1. Dereferencing Null or Uninitialized Pointers:
 // Accessing memory through a pointer that has not been initialized or has been set to NULL 
int *ptr = NULL;
*ptr = 10; // This will cause a segmentation fault


// 2. Buffer Overflow:
int arr[5];
arr[10] = 1; // This will cause a segmentation fault

// 3. Stack Overflow: recursion without base case
void recursiveFunction() {
    recursiveFunction();
}

// 4. Accessing Freed Memory:
// Using a pointer after the memory it points to has been freed (also known as a "dangling pointer") 
int *ptr = (int *)malloc(sizeof(int));
free(ptr);
*ptr = 10; // This will cause a segmentation fault


// 5. Invalid Memory Access:
int *ptr = (int *)0x12345678; // Invalid memory address
*ptr = 10; // This will cause a segmentation fault


            // b. How to debug segfaults
// 1. Use Debuggers: like gdb
gdb ./your_program
run
backtrace

// 2. Check Pointer Initialization:
// Ensure all pointers are properly initialized before use and are set to NULL after freeing the memory.

// 3. Use Memory Checking Tools:
// Tools like Valgrind can help detect memory-related errors such as invalid memory access, 
//              memory leaks, and buffer overflows.
// valgrind ./your_program


        // Example program that causes segfault
#include <stdio.h>

int main() {
    int *ptr = NULL; // Pointer is not initialized
    *ptr = 10; // Dereferencing null pointer causes segmentation fault
    return 0;
}

    // Running the above program causes segfault b/c it attempts to derefence a null pointer.
    // This can be fixed by propertly initializing the ptr to valid memory like this:
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(sizeof(int)); // Allocate memory
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    *ptr = 10; // Valid memory access
    printf("%d\n", *ptr);
    free(ptr); // Free allocated memory
    return 0;
}
  
    /*
                                ALL ABOUT MEMORY ALLOCATION
        - memory allocation, involves managing memory for your program
        - Types of memory allocation:
            - static memory: Memory is allocated during compile time
                - ex: Global variables, static variables, and local variables with fixed size.
            - Dynamic memory: Memory is allocated at runtime.
                - f(x) used: malloc(), calloc(), realloc(), free()
    
    */

    // EXAMPLE OF STATIC MEMORY ALLOCATION
#include <stdio.h>

int global_var;  // Global variable
static int static_var;  // Static variable

int main() {
    int local_var;  // Local variable
    printf("Static Memory Allocation Example\n");
    return 0;
}

        // EXAMPLE OF DYNAMIC MEMORY ALLOCATION
// 1. malloc() (Memory Allocation)
    - Allocates a block of memory of specified size.
    - Returns a pointer to the beginning of the block.
    - Memory is not initialized.

#include <stdlib.h>

int *ptr = (int *)malloc(sizeof(int) * 5); // Allocate memory for 5 integers
if (ptr == NULL) {
    // Handle memory allocation failure
}

// 2. calloc() (Contiguous Allocation)
    - Allocates memory for an array of elements, initializes all bytes to zero.
    - Returns a pointer to the beginning of the block
    
#include <stdlib.h>

int *ptr = (int *)calloc(5, sizeof(int)); // Allocate memory for 5 integers and initialize to 0
if (ptr == NULL) {
    // Handle memory allocation failure
}

// 3. realloc() (Re-allocation)
    - Changes the size of previously allocated memory.
    - Can shrink or expand the memory block.
#include <stdlib.h>

int *ptr = (int *)malloc(sizeof(int) * 5); // Allocate memory for 5 integers
if (ptr == NULL) {
    // Handle memory allocation failure
}
ptr = (int *)realloc(ptr, sizeof(int) * 10); // Reallocate memory for 10 integers
if (ptr == NULL) {
    // Handle memory allocation failure
}

// 4. free() (Deallocation)
    - Frees the previously allocated memory.
    - Prevents memory leaks
#include <stdlib.h>

int *ptr = (int *)malloc(sizeof(int) * 5); // Allocate memory
if (ptr == NULL) {
    // Handle memory allocation failure
}
free(ptr); // Free allocated memory


/*
                        MEMORY LAYOUT IN C
    - Understanding the memory layout helps in better management of memory.
   
    1. Text Segment: Contains compiled code of the program.
    2. Data Segment:
        - initialized data segment: Contains global and static variables initialized by the programmer.
        - uninitialized data segment (BSS): Contains global and static variables initialized to zero or not initialized.
    3. Heap: Used for dynamic memory allocation. Memory is allocated and freed by the programmer.
    4. Stack: Used for function call management, local variables, and control flow. Grows and 
                                        shrinks as functions are called and return.


                        BEST PRACTICES FOR MEMORY ALLOCATION

    1. Check for Allocation Failures: Always check if malloc(), calloc(), or realloc() returns NULL
    2. Use free() to Prevent Memory Leaks: Always free dynamically allocated memory when it’s no longer needed.
    3. Avoid Memory Overwrites: Ensure array bounds and allocated sizes are respected.
    4. Use calloc() for Zero Initialization: If you need initialized memory, use calloc() instead of malloc()
    5. Initialize Pointers: Set pointers to NULL after freeing them to avoid dangling pointers
    6. Limit Dynamic Allocation: Minimize the use of dynamic memory allocation, especially in embedded systems or real-time applications.

                        COMMON ISSUES IN MEMORY ALLOCATION
                        
    1. Memory Leaks: Forgetting to free allocated memory.
    2. Dangling Pointers: Accessing memory after it has been freed.
    3. Buffer Overflow: Writing beyond the allocated memory bounds.
    4. Double Free: Freeing memory that has already been freed.
    5. Uninitialized Memory: Using memory before it is initialized.

                        TOOLS FOR DEBUGGING MEMROY ISSUES
    1. Valgrind: Detects memory leaks, improper memory access, and other memory-related errors
        - valgrind --leak-check=full ./your_program
    2. GDB (GNU Debugger): Debugs segmentation faults and other runtime errors.
        - gdb ./your_program
        - run
        - backtrace


 */



                 
