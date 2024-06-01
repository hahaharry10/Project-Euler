#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

/*
 * Iterate through the number of total discs.
 * Find the value of ( t(t-1)/2 ), lets say its variable x.
 * Find if there is a size of blue disks, b, where b = x/(b-1)
 * If true then probability is 50%.
 *
 * This method removes the need for floating point comparisons.
 */

#define MAKE128CONST(hi,lo) ((((__uint128_t)hi << 64) | lo))

void getBits( idtype_t number ) {
    int bitCount = sizeof(number) * 8;
    printf("Number of bits: %i\n", bitCount);
    int* bitSequence = (int *) malloc(sizeof(int) * bitCount); // Allocate the appropriate number of bits.

    for( int k = 0; k < sizeof(number); k++ ) {
        int mask =  1 << k;
        int masked_n = number & mask;
        int thebit = masked_n >> k;
        bitSequence[k] = thebit;
    }

    // Make bits little endian for readability:
    int* stack = (int *) malloc(sizeof(int) * number);
    int stackHead = 0;
    for( int i = 0; i < sizeof(number); i++ ) {
        stack[stackHead] = bitSequence[i];
        stackHead++;
    }

    int i = 0;
    while( stackHead < 0 ) {
        bitSequence[i] = stack[stackHead];
        i++;
        stackHead--;
    }
    free(stack);

    for( int i = 0; i < bitCount; i++ )
        printf("%i ", bitSequence[i]);
    printf("\n");
}

void outputBytes( __uint128_t addr ) {
    unsigned char* charAddr = (unsigned char *) &addr;
    for( int i = 0; i < sizeof(addr); i++ )
        printf("%llu\n", *(charAddr+i));
}


typedef union {
    __uint128_t as_128;
    struct {
        uint64_t lo;
        uint64_t hi;
    } as_2x64;
} reinterpret128_t;

// Helper function that will be used to write values to the 128-bit datatype.
__attribute__((always_inline)) static void reg128_write(__uint128_t* addr, __uint128_t data) {
    volatile __uint128_t *as_ptr = (volatile __uint128_t *)addr;
    *as_ptr = (__uint128_t) data;
    return;
}

int main(int argc, char** argv) {
    // Define hi and lo:
    uint64_t hi = 0xFFFFFFFFFFFFFFFFULL;
    uint64_t lo = 0xFFFFFFFFFFFFFFFFULL;
    printf("hi: %llu\nlo: %llu\n", hi, lo);
    printf("hi:\tValue: %llu\tSize: %luB ( %lub )\n", hi, sizeof(hi), sizeof(hi)*8);
    getBits(hi);
    printf("\n");
    printf("lo:\tValue: %llu\tSize: %luB ( %lub )\n", lo, sizeof(lo), sizeof(lo)*8);
    getBits(lo);
    printf("\n");

    // Make 128-bti constant:
    __uint128_t const128 = MAKE128CONST(hi, lo);

    // Allocate memory for the 128-bti constant write to it:
    __uint128_t* addr = (__uint128_t *) malloc(sizeof(__uint128_t));
    printf("Size of __uint128_t: %i\n", sizeof(__uint128_t));
    reg128_write(addr, const128);

    // Output bits:
    printf("\n");
    printf("128-bit + :\tValue: %llu-%llu\tSize: %i\n", (unsigned long long) (*addr >> 64), (unsigned long long) *addr, sizeof(*addr));
    getBits(*addr >> 64);
    getBits(*addr);
    printf("\n");

    return EXIT_SUCCESS;
    for( int i = 0; i < 1000000000; i++ ) {
        *addr += 1;
        getBits(*addr >> 64);
        getBits(*addr);
        printf("\n");
    }


    return EXIT_SUCCESS;
}
