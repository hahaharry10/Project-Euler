#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int check(char* number) {
    int digitPowers = 0;
    int* digitPowers_ptr = &digitPowers;

    for (int i = 0; i < strlen(number); i++) {
        *digitPowers_ptr += pow(number[i]-48, 5);
    }

    if (digitPowers == atoi(number)) {
        return 1;
    } else {
        return 0;
    }
}


int main(int argc, char** argv) {

    char* stringNum = (char *) calloc(7, sizeof(char));
    int* successfulNums = (int *) calloc(10, sizeof(int));
    int numOfSuccessful = 0;
    int* numOfSuccessful_ptr = &numOfSuccessful;

    for (int number = 2; number < 10000000; number++) {
        sprintf(stringNum, "%i", number);

        int result = check(stringNum);

        if (result == 1) {
            successfulNums[numOfSuccessful] = number;
            *numOfSuccessful_ptr += 1;
        }
    }

    int sum = 0;
    int* sum_ptr = &sum;

    for (int i = 0; i < numOfSuccessful; i++) {
        *sum_ptr += successfulNums[i];
    }

    printf("%i\n", sum);

    return 0;
}