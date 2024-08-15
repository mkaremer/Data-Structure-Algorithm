#include <stdio.h>     // Include standard input/output library
#include <stdlib.h>    // Include standard library for memory allocation functions
#include <string.h>    // Include string library for string manipulation functions

// Function to convert a decimal number n into binary with k precision
char* convertToBinary(double n, int k) {
    // Separate the integer and fractional parts
    int integerPart = (int)n;          // Extract integer part from n
    double fractionalPart = n - integerPart; // Calculate fractional part by subtracting integer part from n

    // Convert integer part to binary
    char intBinary[64] = {0};          // Create a character array to store binary digits of the integer part
    int index = 0;                     // Index to track the position in intBinary array
    if (integerPart == 0) {            // Special case: if integer part is 0
        intBinary[index++] = '0';      // Store '0' in intBinary array
    } else {
        while (integerPart > 0) {      // Loop to convert integer part to binary
            intBinary[index++] = (integerPart % 2) + '0'; // Get the remainder (0 or 1) and convert it to character
            integerPart /= 2;          // Divide the integer part by 2 for next bit
        }
        // Reverse the integer binary string to get the correct order
        for (int i = 0; i < index / 2; i++) {
            char temp = intBinary[i];              // Swap elements to reverse the order
            intBinary[i] = intBinary[index - 1 - i];
            intBinary[index - 1 - i] = temp;
        }
    }

    // Convert fractional part to binary
    char fracBinary[64] = {0};          // Create a character array to store binary digits of the fractional part
    int fracIndex = 0;                  // Index to track the position in fracBinary array
    while (fracIndex < k) {             // Loop to convert fractional part to binary with k precision
        fractionalPart *= 2;            // Multiply fractional part by 2
        int bit = (int)fractionalPart;  // Get the integer part of the result (0 or 1)
        fracBinary[fracIndex++] = bit + '0'; // Store the bit as a character in fracBinary
        fractionalPart -= bit;          // Subtract the bit to get the remaining fractional part
        if (fractionalPart == 0.0) {    // Stop if the fractional part becomes 0
            break;
        }
    }

    // Calculate total length needed for the combined binary string
    int totalLength = index + 1 + fracIndex + 1; // +1 for dot, +1 for null terminator
    char* result = (char*)malloc(totalLength * sizeof(char)); // Allocate memory for the result string
    if (result == NULL) {                 // Check if memory allocation failed
        fprintf(stderr, "Memory allocation failed\n"); // Print error message
        exit(EXIT_FAILURE);               // Exit the program with failure code
    }

    // Combine the integer and fractional parts into the result string
    snprintf(result, totalLength, "%s.%s", intBinary, fracBinary); // Format and store in result string

    return result;                        // Return the combined binary string
}

int main() {
    double n1 = 2.47;                     // Test input: decimal number
    int k1 = 5;                           // Precision for fractional part
    char* binary1 = convertToBinary(n1, k1); // Convert decimal to binary
    printf("Input: n = %.2f, k = %d\nOutput: %s\n", n1, k1, binary1); // Print result
    free(binary1);                        // Free allocated memory

    double n2 = 6.986;                    // Test input: another decimal number
    int k2 = 8;                           // Precision for fractional part
    char* binary2 = convertToBinary(n2, k2); // Convert decimal to binary
    printf("Input: n = %.3f, k = %d\nOutput: %s\n", n2, k2, binary2); // Print result
    free(binary2);                        // Free allocated memory

    return 0;                             // Return 0 to indicate successful execution
}
