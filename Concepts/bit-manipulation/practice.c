//isEven
// 10 & 1 = 0
// 11 & 1 = 1
bool isEven(unsigned int n){
    return (n & 1) == 0;
}

// swap
void swap(int* a, int* b){
    a* = a* ^ *b;
    b* = a* ^ *b;
    a* = a* ^ *b;
}

//countSetBits
// 1010 & 1 = 0
// count = 2
// 0101 & 1 = 1
// 0010 & 1 = 0
// 0001 & 1 = 1
// 0000
int countSetBits(unsigned int n){
    int count = 0;
    while(n){
        count += n & 1;
        n >> 1;
    }
    return count;
}

//reverseBits
/*
    1010 0000 => 0000 0101
    res = 0000 0000 
    1010 0000 & 1 = 0
    0101 0000 & 1 = 0
    0010 1000 & 1 = 0
    0000 0101 & 1 = 1
    
*/
uint32_t reverseBits(uint32_t n){
    uint32_t res = 0;
    while(n){
        res <<= 1;
        if(n & 1){
            res | 1;
        }
        n >> 1;
    }
    return res;
}

// reverse hex bits
/*
    0x12345678 =>0x78563412
    12345678 >> 24 =00000012
    12345678 >> 8 = 00123456 
    12345678 << 8 = 34567800
    12345678 << 24 = 78000000

    
*/
uint32_t reverseHexBits(uint32_t n){
   return   (n >> 24) && 0x000000FF |
            (n >> 8) && 0x0000FF00  |
            (n << 8) && 0x00FF0000  |
            (n << 24) && 0xFF000000
}
/*
    100
    011
    000
*/
bool isPowerOfTwo(unsigned int n){
    return (n >= 0) && (n & (n - 1) == 0);
}

unsigned int setBit(unsigned int n, int pos){
    return n | (1 << pos);
}

unsigned int clearBit(unsigned int n, int pos){
    return n & ~(1 << pos);
}

/*
    1010 0101 => 1010 0000
    1010 0101 & 1111 0000
    1111 0000
*/
unsigned int clearBitsKthrough0(unsigned int n, int pos){
    return n & (~0 << pos + 1);
}

/*
    1010 0101
    0000 1111
    1 << pos = 3 = 1000
    1000
    -  1
    0111

*/
unsigned int clearBitsMSBthroughi(unsigned int n, int pos){
    return n & ((1 << pos) - 1);
}

unsigned int toggleBits(unsigned int n, int pos){
    return n ^ (1 << pos);
}

bool isSet(unsigned int n, int pos){
    return (n & (1 << pos)) != 0
}
/*
    1010 0010
    
*/
unsigned int updateBit(unsigned int n, unsigned int m, int i, int j){

}