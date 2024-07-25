/**

            BIT MANIPULATION
    - it is a critical skill for firmware engineers.
    - it involves using bitwise operators to perform operations at the bit level.

 */

 // AND (&), Sets each bit to 1 if both bits are 1.
int a = 5;  // 0101
int b = 3;  // 0011
int result = a & b;  // result is 1 (0001)

// OR (|) , Sets each bit to 1 if at least one of the bits is 1.
int a = 5;  // 0101
int b = 3;  // 0011
int result = a | b;  // result is 7 (0111)

// XOR (^), Sets each bit to 1 if only one of the bits is 1.
int a = 5;  // 0101
int b = 3;  // 0011
int result = a ^ b;  // result is 6 (0110)

// NOT (~), Inverts all the bits.
int a = 5;  // 0101
int result = ~a;  // result is -6 (in 2's complement form)

// Left Shift (<<), Shifts bits to the left, filling with zeros.
int a = 5;  // 0101
int result = a << 1;  // result is 10 (1010)

//Right Shift (>>), Shifts bits to the right, discarding bits shifted off.
int a = 5;  // 0101
int result = a >> 1;  // result is 2 (0010)

            //COMMON BIT MANIPULATION TECHNIQUES
// 1. Checking if a Number is Even or Odd
// An even number has its least significant bit (LSB) as 0, and an odd number has its LSB as 1.
bool isEven(int x) {
    return (x & 1) == 0;
}

// 2. Swapping Two Numbers Without a Temporary Variable
// Using XOR to swap values without needing extra space.
//this code is written in c++
// C++ uses references to enable direct modification of original varibles
// to call the f(x) do, swap(a, b)
void swap(int &a, int &b){
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

// the c version, which uses pointers instead to achieve the same functionality
// to call the f(x) do, swap(&a, &b)
void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

//3. Counting the number of set bits (hamming weight)
// Count the number of 1s in the binary representation of a number.
int countSetBits(int n) {
    int count = 0;        // Initialize count to 0
    while (n) {           // Loop until n becomes 0
        count += n & 1;   // Add the least significant bit of n to count
        n >>= 1;          // Right shift n by 1 bit to process the next bit
    }
    return count;         // Return the total count of set bits
}

// 4. Reversing Bits of a Number
// Reverse the order of bits in a number.
unsigned int reverseBits(unsigned int n) {
    unsigned int result = 0;  // Initialize result to 0, this will hold the reversed bits
    for (int i = 0; i < 32; ++i) {  // Iterate through all 32 bits of the unsigned integer
        result <<= 1;  // Left shift result by 1 to make space for the next bit
        if (n & 1) {  // If the least significant bit of n is 1
            result |= 1;  // Set the least significant bit of result to 1
        }
        n >>= 1;  // Right shift n by 1 to process the next bit
    }
    return result;  // Return the result which contains the reversed bits
}

// 5. Reversing Hexadecimla number
uint32_t reverseHexBits(uint32_t n) {
    return ((n >> 24) & 0x000000ff)      // Move the most significant byte to the least significant byte position
           | ((n << 8) & 0x00ff0000)     // Move the second least significant byte to the second most significant byte position
           | ((n >> 8) & 0x0000ff00)     // Move the second most significant byte to the second least significant byte position
           | ((n << 24) & 0xff000000);   // Move the least significant byte to the most significant byte position
}

// 6. checking is a number is a power of 2
// A number is a power of two if it has exactly one set bit.
/*
    The binary representation of powers of two has exactly one 1 bit and the rest are 0s. 
    ex:
    2 ^ 0 = 1 = 0001
    2 ^ 1 = 2 = 0010
    2 ^ 2 = 4 = 0100

    - n has exactly one 1 bit.
    - n−1 flips all the bits after the 1 bit, including the 1 bit itself.
    ex:
        n=4 (binary 0100)
        n−1=3 (binary 0011)
        4 & 3 = 0100 & 0011 = 0000
*/
bool isPowerOfTwo(int n) {
    // A number is a power of two if it is greater than 0 and
    // the bitwise AND of the number and one less than the number is zero
    return n > 0 && (n & (n - 1)) == 0;
}

            // BIT MANIPULATION PRACTICE
// 1. setting a bit
/*
        - use bitwise OR, | to set kth bit with a mask created by left shifting 1 by k positions
        - this operation is used where you need to manage flags, configure hardware registers, etc
*/
int setBit(int n, int k) {
    return n | (1 << k);
}

// 2. clearing a bit
/*
    - use bitwise AND, & to clear kth bit with a mask created by left shifting 1 by k positions and invert it.
*/
int clearBit(int n, int k) {
    return n & ~(1 << k);
}

//clear bits from the most significant bit through i inclusive.
/*
    - we create a mask with a 1 at the kth position bit 
    - then we substract 1 from it, giving us a sequence of zeros followed by i ones. 
    -  we then AND n with the mask
*/
int clearBitsMSBthroughi(int n, int k){
    return n & ((1 << k) - 1);
}
/*
    -1 is respresented as all ones in binary in two's complement system b/c:
        - inverting all bits of 1 and adding 1 results in abinary number with all bits set to 1
*/

// To clear bits from i through 0 inclusive.
/*
    - take a sequence of all ones which is -1 and shift it left by k + 1 bits.
    - This gives us a sequence of ones in MSB followed by k + 1 zeors
*/
int clearBitsKthrough0(int n, int k){
    return n & (-1 << (k + 1));
}
// 3. toggling a bit
/*
    - uset bitwise XOR, ^ to toglle a bit with a mask created by left shifting 1 by k positions
*/
int toggleBit(int n, int k) {
    return n ^ (1 << k);
}

// 4. Checking a bit
/*
    - use bitwise AND, &, to check if a bit is set with a mask created by left shifting 1 by k positions. 
    - the above results in a number with all bits sets to 0 except bit at k position.
    - This bit is compared to 0, if it not equal to 0 then the bit is set, else it is not set
*/
bool isBitSet(int n, int k) {
    return (n & (1 << k)) != 0;
}

// 5. Update a bit
/*
    To set the kth bit to a value v:
        - first clear bit at position k, use mask like 11110111
        - then shift value v left by k bits:
            - this will create a number with bti i equal to v and all other equal to 0
        - finally, we OR these two numbers, updating the kth bit. 
*/
int updateBit(int n, int k, int v) {
    // Create a mask with all bits set to 1 except the k-th bit
    int mask = ~(1 << k);

    // Clear the k-th bit of n
    n = n & mask;

    // Set the k-th bit to the value v
    n = n | (v << k);

    return n;
}

/*
        1. Binary representation of fractions
    steps:
        1. multiply fraction by 2
        2. extract and records the integer part (0 or 1)
        3. repeat with the remaining fractional part until it becomes 0 or repeating pattern is noticed
        4. Combine all the recorded integer parts to get the binary fraction
    
    Ex: converting 0.75 to binary
        1. 0.75 x 2 = 1.5
            int part: 1
            faction part: 0.5
        2. 0.5 x 2 = 1.0
            int part: 1
            fraction part = 0
        3. compine all integers
            0.75 = 0.11

    2. Floating-point Representation

        - Most computers use a format known as floating-point representation to store and 
            manipulate real numbers(including frations)
        - The IEEE 754 standard is the most common way to handle floating-point math. 
            It explains how to represent and work with floating-point numbers in binary.

            a. Components of a Floating-Point Number
                - A floating-point number is composed of three parts:
                    1. Sign Bit: shows the sign of the number (0 for positive, 1 for negative).
                
                    2. Exponent:Encodes the exponent part of the number, typically with a bias added.

                    3. Mantissa (or Significand): Encodes the significant digits of the number.
                - The general form of a floating-point number in binary is:
                (-1)sign x 1.mantissa x 2 ^ exponent-bias

            b. IEEE 754 Formats
                - the most common standards:
                    1. Single Precision (32-bit):
                        - 1 bit for the sign
                        - 8 bits for the exponent
                        - 23 bits for the mantissa
                    2. Double Precision (64-bit):
                        - 1 bit for the sign
                        - 11 bits for the exponent
                        - 52 bits for the mantissa

            c.Example: Storing a Number in Single Precision
                -  Let's see how a number like 0.625 is stored in single precision (32-bit).
                    1. Convert to Binary:
                        - 0.625 in binary is 0.101.

                    2. Normalize the Binary Fraction:
                        - Normalize 0.101 as 1.01 x 2 ^ -1

                    3. Determine Sign, Exponent, and Mantissa:
                        - Sign bit: 0 (positive)

                        - Exponent: The actual exponent is -1.
                            - In IEEE 754 single precision, the bias is 127. 
                            - so the stored exponent is 127 + (-1) = 126, which 0111 1110.
                        - Mantissa: The mantissa is 01 (the part after the binary point in the normalized form).
                            - This is padded with zeros to fill the 23-bit mantissa field: 01000000000000000000000.
                    4. Combine Components:
                        - Sign bit: 0
                        - Exponent: 01111110
                        - Mantissa: 01000000000000000000000
                    5. So, the binary representation of 0.625 in IEEE 754 single precision is:
                        - 0 | 01111110 | 01000000000000000000000
            d. Floating-Point Representation in Memory
                - Here's how the number is stored in a 32-bit memory space:
                    Sign (1 bit) | Exponent (8 bits) | Mantissa (23 bits)
                    0            | 01111110          | 01000000000000000000000
            e. Example: Storing a Number in Double Precision
                - it is the same process, except the bias is 1023
*/

/*
                        Basics of XOR Operation
        - Properties of XOR
            1. Commutative:
                A ^ B = B ^ A
                The order of operands does not matter.
            
            2. Associative:
                A ^ (B ^ C) = (A ^ B) ^ C
                Grouping of operands does not matter.
            
            3. Identity
                A ^ 0 = A
                XOR with zero leaves the number unchanged.
            
            4. Self-inverse:
                A ^ A = 0
                XOR with itself results in zero.
            
            5. Inverse:
                A ^ B ^ B = A
                XOR-ing a number with another number twice returns the original number.
*/

/*
        - Common Uses of XOR
            1. Swapping Two Numbers Without a Temporary Variable
                The XOR operation can swap two numbers without using an extra temporary variable:
*/
void swap(int *a, int *b) {
    if (a != b) { // Ensure the addresses are not the same to avoid zeroing out
        *a = *a ^ *b;
        *b = *a ^ *b; // Now *b = original *a
        *a = *a ^ *b; // Now *a = original *b
    }
}

/*
    2. Finding the Single Non-Repeating Element
        Given an array where every element appears twice except for one, 
        XOR can find the single non-repeating element:
*/
int findSingle(int arr[], int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result ^= arr[i];
    }
    return result;
}

/*
    3. Checking if Two Numbers are Equal
        You can check if two numbers are equal using XOR:
*/
bool areEqual(int a, int b) {
    return (a ^ b) == 0;
}

/*
    4. Binary Addition without a carry
        XOR can be used to add two binary numbers without considering carry:
*/
int addWithoutCarry(int a, int b) {
    return a ^ b;
}

/*
    XOR Tricks and Techniques

    1. XOR for flipping bits
        XOR-ing a bit with 1 flips the bit:
            0 ^ 1 = 1
            1 ^ 1 = 0
    2. XOR for Parity Checking
        XOR can be used to determine the parity (odd or even number of 1-bits) of a binary number. 
        If the XOR of all bits in the number is 0, the number of 1s is even; otherwise, it is odd.

    3. XOR for Cryptography
        XOR is used in simple encryption techniques like the one-time pad. 
        It is because XOR-ing with the same key twice returns the original data

*/
/*
    4. XOR for Bit Masking
        XOR can be used to toggle specific bits. For example, to toggle the k-th bit of a number:
*/
int toggleBit(int n, int k) {
    return n ^ (1 << k);
}

/*
    5. XOR for Finding Missing Number
        Given an array containing numbers from 1 to n with one number missing, 
            XOR can find the missing number:
*/
// Function to find the missing number in an array
int findMissingNumber(int arr[], int n) {
    // Initialize result with n, which is the total number of elements (including the missing one)
    int res = n;

    // Iterate through the array and the range of numbers from 0 to n-1
    for (int i = 0; i < n; i++) {
        // XOR the result with the current index
        res ^= i;
        // XOR the result with the current array element
        res ^= arr[i];
    }

    // The result now holds the missing number
    return res;
}
/*
            Left Shift
    common uses:
        1. Multiplication by powers of two
            Shifting a binary number to the left by n positions is equivalent to multiplying the number by 2^n

*/
int multiplyByEight(int n) {
    return n << 3; // Equivalent to n * 8
}

/*
        Multiply by 7 using leftshift

    To multiply a number by 7 using the bitwise left shift operation, you can utilize the fact that 
    7 = 2 ^ 2 + 2 ^ 1 + 2 ^ 0. This can be broken into: 
    7 x n = (4 + 2 + 1) x n = (2 ^ 2 + 2 ^ 1 + 2 ^ 0) x n
    This means you can shift the number left by 2, left by 1, and then add the original number. 
    Here's the corrected function:

*/
int multiplyBySeven(int n) {
    return (n << 2) + (n << 1) + n;
}

/*
        swap Nibles
    Given an 8 bit binary number swap its nibbles

    Algorithm:
        - left shift one nible to the left by 4 position
        - right shfit the other nibble to the right by 4 position
        - combine the results
*/
//this is much safer if we're not guaranteed to get an 8 bit number
unsigned int swapNible(unsigned int n){
    return (n & 0xF0) >> 4 | (n & 0x0F) << 4;
}

//This is safer is 8 bit number is guaranteed
unsigned int swapNible(unsigned int n){
    return (n >> 4) | (n << 4);
}

/*
    write a function that swaps the highest bits in each nibble of the byte
    ex: 0bAxxxBxxx ==> 0bBxxxAxxx

    Algorithm:
        - extract bits at both positions
        - if they are different:
            toggle each bit at its position using xor
        - return n
*/

uint8_t swapHighestBitsNibble(uint8_t n, int i, int j) {
    // Extract the bit at position i
    uint8_t bitA = (n >> i) & 1;
    // Extract the bit at position j
    uint8_t bitB = (n >> j) & 1;

    // Check if the bits at position i and j are different
    if (bitA != bitB) {
        // Toggle the bit at position i
        n ^= 1 << i;
        // Toggle the bit at position j
        n ^= 1 << j;
    }

    // Return the modified number with bits at positions i and j swapped if they were different
    return n;
}
/*
        Insertion of bits problem
Insertion: You are given two 32-bit numbers, N and M, and two bit positions, i and j. Write a method
to insert M into N such that M starts at bit j and ends at bit i. You can assume that the bits j through
i have enough space to fit all of M. That is, if M = 10011, you can assume that there are at least 5
bits between j and i. You would not, for example, have j = 3 and i = 2, because M could not fully
fit between bit 3 and bit 2.
EXAMPLE
Input:  N = 10000000000, M = 10011, i = 2, j = 6
Output: N = 10001001100

Algo:
    - create a mask to erase bits between i and j
    - AND mask with n
    - OR the result with m left shifted by i

*/
uint32_t insertBits(uint32_t n, uint32_t m, int i, int j) {
    //edge cases
    if(i > j || i < 0 || j >= 32)
        return n;

    // creating the mask:
    // 1. (~0 << (j + 1)): sets all bits from pos 0 to j to 1 and the rest 0
    // 2. ((1 << i) - 1): sets all bits from pos 0 to i - 1 to 1 and the rest to 0
    uint32_t mask = (~0 << (j + 1)) | ((1 << i) - 1);
    // Clear bits j through i in N and shift M into the correct position, then OR the results
    return (n & mask) | (m << i);
}
/*
            SUM LISTS
    * You have two numbers represented by linked list, where each node contains
 * a single digit. Digits are stored in reverse order.(1's digit is at the head)
 * Write a function that adds two such numbers and returns a number in similar
 * list format.
 * example:
 * 7-->1-->6 + 5-->9-->2 = 2-->1-->9
 * which is (617 + 295  = 912)
 * What if digits are not stored in reverse order(i.e 1's digit is at tail)
 * (6--1-->7) + (2-->9-->5) = (9-->1-->2) 
*/
listNode* addTwoNums(ListNode* l1, ListNode* l2){
    ListNode* dummyHead = createNode(0);
    ListNode* l1_ptr = l1;
    ListNode* l2_ptr = l2;
    ListNode* current = dummyHead;
    int carry = 0;

    while(l1_ptr != NULL || l2_ptr != NULL){
        // Get the current values of the nodes, or 0 if the node is NULL
        int x = (l1_ptr != NULL) ? l1->val : 0;
        int y = (l2_ptr != NULL) ? l2->val : 0;

        int sum = carry + x + y; //get the sum

        carry = sum / 10; // update the carry
        
        //create new node with digit part of sum
        current->next = createNode(sum % 10);

        current = current ->next; //move current to point to next node

        //Move to the next nodes in the input lists if available
        if (l1_ptr != NULL) 
            l1_ptr = l1_ptr->next;

        if (l2_ptr != NULL)
            l2_ptr = l2_ptr->next;
            
        //if there is a remaining carry, create a new node for it
        if(carry > 0){
            current->next = createNode(carry);
        }

        return dummyHead->next;
    }
}
// Function to add two numbers represented by linked lists (forward order) without reversing the lists
struct ListNode* addTwoNumbersForward(struct ListNode* l1, struct ListNode* l2) {
    // Create two stacks to hold the digits of the two numbers
    struct ListNode* stack1 = NULL;
    struct ListNode* stack2 = NULL;
    
    // Push all digits of l1 to stack1
    while (l1 != NULL) {
        struct ListNode* newNode = createNode(l1->val); // Create a new node with the current digit
        newNode->next = stack1; // Push the node onto stack1
        stack1 = newNode; // Move the stack1 pointer to the new node
        l1 = l1->next; // Move to the next node in l1
    }
    
    // Push all digits of l2 to stack2
    while (l2 != NULL) {
        struct ListNode* newNode = createNode(l2->val); // Create a new node with the current digit
        newNode->next = stack2; // Push the node onto stack2
        stack2 = newNode; // Move the stack2 pointer to the new node
        l2 = l2->next; // Move to the next node in l2
    }
    
    // Initialize the result list and carry variable
    struct ListNode* result = NULL;
    int carry = 0;
    
    // Pop digits from stacks and add them
    while (stack1 != NULL || stack2 != NULL || carry != 0) {
        int x = (stack1 != NULL) ? stack1->val : 0; // Get the current digit from stack1 or 0 if stack1 is empty
        int y = (stack2 != NULL) ? stack2->val : 0; // Get the current digit from stack2 or 0 if stack2 is empty
        int sum = carry + x + y; // Calculate the sum of the current digits and carry
        carry = sum / 10; // Update the carry for the next iteration
        
        struct ListNode* newNode = createNode(sum % 10); // Create a new node with the digit part of the sum
        newNode->next = result; // Insert the new node at the beginning of the result list
        result = newNode; // Move the result pointer to the new node
        
        if (stack1 != NULL) {
            struct ListNode* temp = stack1; // Temporarily store the current node of stack1
            stack1 = stack1->next; // Move to the next node in stack1
            free(temp); // Free the memory of the current node
        }
        
        if (stack2 != NULL) {
            struct ListNode* temp = stack2; // Temporarily store the current node of stack2
            stack2 = stack2->next; // Move to the next node in stack2
            free(temp); // Free the memory of the current node
        }
    }
    
    // Return the result list
    return result;
}
/*
    Write a function Add() that returns sum of two integers. The function should not use any 
    of the arithmetic operators (+, ++, –, -, .. etc).

    Algorithm:
     - Use XOR to add a and b without the carry.
     - Use AND followed by a left shift to calculate the carry.
     - Repeat the process until there is no carry left.
*/
// Function to add two integers without using arithmetic operators
unsigned int Add(unsigned int a, unsigned int b) {
    while (b != 0) {
        // Calculate the carry using AND and left shift
        unsigned int carry = (a & b) << 1;

        // Sum of bits of a and b where at least one of the bits is not set using XOR
        a = a ^ b;

        // Carry is shifted by one so that adding it to a gives the required sum
        b = carry;
    }
    return a;
}
/*
    write a program to swap odd and even bits in an integer with as few instruction as possible
    eg: bit 0 and bit 1 are swapped, bit 2 and 3 are swapped and so on
*/

