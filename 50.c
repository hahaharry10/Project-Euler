#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_NO_ERRORS 0
#define EXIT_ERROR 1

/**
 * @brief Find the number of consecutive pries that add to create a number.
 * 
 * @param primes An array of primes.
 * @param primeLength The number of numbers in primes.
 * @param consecutivePrimes Array to hold the consecutive primes.
 * @param number The number being tested.
 * @param highestNumOfConsec The highest consecutive prime sum found.
 * @return int The number of consecutive primes. 0 if none.
 */
int ConsecutivePrimeSumFinder(int* primes, int primeLength, int* consecutivePrimes, int number, int highestNumOfConsec) {

    int start_ptr = 0;
    int* start_ptr_ptr = &start_ptr;
    int end_ptr = 0;
    int* end_ptr_ptr = &end_ptr;
    int highest_sum = 0;
    int* highest_sum_ptr = &highest_sum;


    for (int start = 0; start < primeLength - 1; start++) {
//        printf("START = %i\n", primes[start]);
        int sum = primes[start];
        for (int end = start+1; end < primeLength; end++) {
            sum += primes[end];
//            printf("\t%i\t\tSUM = %i", primes[end], sum);
            if ((sum == number) && ((end - start + 1) > highestNumOfConsec)) {
//                printf("\t\t <--");
                *start_ptr_ptr = start;
                *end_ptr_ptr = end;
                *highest_sum_ptr = end - start + 1;

                for (int i = start; i < end+1; i++) {
                    consecutivePrimes[i-start] = primes[i];
                }
            } else if (sum > number) {
//                printf("\n-------------------------------------------------------\n");
                break;
            }

//            printf("\n");
        }
    }

    return highest_sum;

}


/**
 * @brief Checks if a number is a prime number.
 * 
 * @param primes Array of previously found prime numbers.
 * @param primesLength Number of previous primes found.
 * @param number The number being checked.
 * @return int 0 if number isnt a prime, 1 if number is.
 */
int isPrime(int* primes, int primesLength, int number) {

    for (int i = 0; i < primesLength; i++) {
        if ((number % primes[i]) == 0) {
            return 0;
        }
    }

    return 1;
}



int main() {

    int* primes = (int *) calloc(75000, sizeof(int));

    if (primes == NULL) {
        return EXIT_ERROR;
    }

    int primesLength = 0;
    int* primesLength_ptr = &primesLength;

    for (int i = 2; i < 1000000; i++) {
        if (isPrime(primes, primesLength, i)) {
            primes[primesLength] = i;
            *primesLength_ptr += 1;
        }
    }

    int* consecutive_primes = (int *) calloc(100, sizeof(int));
    if (consecutive_primes == NULL) {
        return EXIT_ERROR;
    }


    int mostConsecutivePrime = 0;                               // Number with the highest consecutive prime sum.
    int* mostConsecutivePrime_ptr = &mostConsecutivePrime;
    int numOfConsecPrimes = 0;                                  // Number of consecutive primes summed to make 'mostConsecutivePrime'
    int* numOfConsecPrimes_ptr = &numOfConsecPrimes;

    for (int i = 0; i < primesLength; i++) {
        int currentConsecPrimeNum = ConsecutivePrimeSumFinder(primes, i, consecutive_primes, primes[i], numOfConsecPrimes);

        if (currentConsecPrimeNum > *numOfConsecPrimes_ptr) {
            *numOfConsecPrimes_ptr = currentConsecPrimeNum;
            *mostConsecutivePrime_ptr = primes[i];
        }
    }



    printf("RESULTS:\n\tNumber:\t%i\n", mostConsecutivePrime);
    printf("\tNumber of Consecutive Primes:\t%i\n", numOfConsecPrimes);
    printf("\tConsecutive primes:\n");
    for (int* i = consecutive_primes; i < consecutive_primes+numOfConsecPrimes; i++) {
        printf("\t\t%i\n", *i);
    }


    free(primes);
    free(consecutive_primes);
    return EXIT_NO_ERRORS;

}