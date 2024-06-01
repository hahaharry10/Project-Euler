#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Exit Codes.h"

/**
 * @brief Implement a binary search to find if a value x is in array.
 * 
 * @param x the value being searched for.
 * @param array array of numbers.
 * @param arr_len length of array.
 * @return int 0 if found. 1 if not found.
 */
int binarySearch(int x, int array[], int arr_len) {
    int start = 0;
    int end = arr_len - 1;
    while (start != end) {
        int mid = (int) (start + end) / 2;
        if (array[mid] == x) return 0; // return FOUND

        else if (array[mid] < x) start = mid + 1;

        else if (array[mid] > x) end = mid - 1;
    }

    return 1; // return NOT FOUND
}

/**
 * @brief Check if the characters in the parameters are a permutation of eachother.
 * 
 * @param n 
 * @param totient 
 * @return int 0 if n is a permutation of totient. 1 otherwise.
 */
int isNotPermutation(char n[], char totient[]) {
    int n_len = strlen(n);
    int tot_len = strlen(totient);

    if (n_len != tot_len) { // are parameters of different size?
        return 1;
    }

    char* N = (char *) calloc(n_len, sizeof(char));
    strcpy(N, n);

    for (int i = 0; i < tot_len; i++) {
        for (int j = 0; j < n_len; j++) {
            if (totient[i] == N[j]) { // if totient and N share a character.
                N[j] = 'V'; // replace character with 'V' to represent a voided entry.
                break;
            }
        }
    }

    for (int i = 0; i < n_len; i++) {
        if (N[i] != 'V') {
            free(N);
            return 1; // return FAIL
        }
    }

    free(N);
    return 0; // return SUCCESS
}

/**
 * @brief Checks if x is not an integer.
 * 
 * @param x
 * @return int 1 if x is not an integer. 0 if x is an integer.
 */
int isNotInteger(char* x) {
    for (int i = 0; i < strlen(x); i++) {
        if (x[i] >= '0' && x[i] <= '9') {
            return 1;
        }
    }

    return 0;
}

/**
 * @brief Checks if x and y are relative primes.
 * 
 * @param x 
 * @param y 
 * @return int 1 if they are relative primes, 0 if not.
 */
int isRelativePrime(int x, int y, int* primes, int* primes_len) {
    int isPrime = 1;
    for (int i = 0; i < *primes_len; i++) {
        if ( (x % primes[i] == 0) && (y % primes[i] == 0) ) {
            return 0; // return NOT RELATIVE PRIMES
        } else if (x % primes[i] == 0) {
            isPrime = 0;
        }
    }

    if (isPrime) {
        primes[*primes_len] = x;
        *primes_len = *primes_len + 1;
    }

    return 1; // return ARE RELATIVE PRIMES
}



/**
 * @brief calculate the totient function of value x.
 * 
 * @param x 
 * @return int the totient function.
 */
int calculateTotient(int n, int* primes, int* primes_len) {
    int rel_prim = 0; // The number of relative primes.
    int* rel_prim_ptr = &rel_prim;

    int isPrime = 1;
    double totient = n;

    for (int i = 1; i < *primes_len; i++) {
        if (n % primes[i] == 0) {
            totient = totient * (1 - ( (double) 1 / primes[i]));
            isPrime = 0;
        }
    }
    if (isPrime) {
        primes[*primes_len] = n;
        *primes_len = *primes_len + 1;
    }

    return totient;
    

}

int smain(int argc, char* argv[]) {

    int* primes = (int *) calloc(5761455, sizeof(int)); // There are 5,761,455 primes less than 10^7
    int primes_len = 0;
    if (!primes) {
        printf("ERROR: Calloc Failed.\n");
        return EXIT_ERROR;
    }

    int min = 1;
    int min_n = 1;
    int print = 1;
    for (int n = 1; n < pow(10, 7); n = n + 2) { // scan every odd number where 1 < n < 10^7.
        if ((n % (int) pow(10, print)) == 0) {
            printf("%i\n", n);
            print++;
        }
        int ratio = (double) n / calculateTotient(n, primes, &primes_len);
        if (ratio < min) {
            min = ratio;
            min_n = n;
        }
    }

    printf("%i\n", min_n);
    return EXIT_NO_ERRORS;
}

int main() {
    double input;
    printf("Enter a number: ");
    scanf("%lf", &input);

    int* primes = (int *) calloc(5761455, sizeof(int)); // There are 5,761,455 primes less than 10^7
    int primes_len = 0;
    if (!primes) {
        printf("ERROR: Calloc Failed.\n");
        return EXIT_ERROR;
    }

    // Declare time tracking variables:
    clock_t start, stop;
    double cpu_time_used;

    start = clock();

    for (double i = 1; i < input+1; i++) {
        if (i == input)
            printf("%d\n", calculateTotient(i, primes, &primes_len));
        else
            calculateTotient(i, primes, &primes_len);
    }

    stop = clock();
    cpu_time_used = ((double) (stop - start)) / CLOCKS_PER_SEC;
    printf("%lfs\n", cpu_time_used);
    free(primes);
    return EXIT_NO_ERRORS;
}