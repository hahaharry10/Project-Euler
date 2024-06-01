#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Exit Codes.h"

int endienneReverser(char* number, char* result) {
    int max_ptr = strlen(number) - 1;   // Store the pointer to the last element of the number.

    for (int i = max_ptr; i >= 0; i--) {
        result[max_ptr-i] = number[i];
    }

    result[max_ptr+1] = '\0';

    return EXIT_NO_ERRORS;
}

int add(char* num1, char* num2, char* result, int sizeOfcalloc) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    // Create little endienne (LE) variables of the numbers:
    char* LEnum1 = (char *) calloc(sizeOfcalloc, sizeof(char));
    char* LEnum2 = (char *) calloc(sizeOfcalloc, sizeof(char));
    char* LEresult = (char *) calloc(sizeOfcalloc, sizeof(char));


    endienneReverser(num1, LEnum1);
    endienneReverser(num2, LEnum2);


    if (len1 > len2) {
        // Add padding to LEnum2 to equalise lengths:
        for (int i = len2; i < len1; i++) {
            LEnum2[i] = '0';
        }
        LEnum2[len1] = '\0';

    } else if (len1 < len2) {
        // Add padding to LEnum1 to equalise lengths:
        for (int i = len1; i < len2; i++) {
            LEnum1[i] = '0';
        }
        LEnum1[len2] = '\0';
    }


    if (strlen(LEnum1) != strlen(LEnum2)) {
        free(LEnum1);
        free(LEnum2);
        free(LEresult);
        return EXIT_ERROR;
    }

    strcpy(LEresult, LEnum1);

    for (int i = 0; i < strlen(LEresult); i++) {
        int digit1 = LEresult[i] - 48;
        int digit2 = LEnum2[i] - 48;
        int sum = digit1 + digit2;
        int *sum_ptr = &sum;
        int carry = 0;
        int *carry_ptr = &carry;

        if (sum > 9) {
            *sum_ptr -= 10;
            *carry_ptr = 1;
        }

        LEresult[i] = sum + 48;

        if (carry) {
            if ((i + 1) == strlen(LEnum1)) {
                LEresult[i+1] = '1';
                LEresult[i+2] = '\0';

            } else {
                LEresult[i+1]++;
                for (int j = i+1; j < strlen(LEresult) - 1; j++) {
                    if (LEresult[j] > '9') {
                        LEresult[j] -= 10;
                        LEresult[j+1] += 1;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    endienneReverser(LEresult, result);
    free(LEnum1);
    free(LEnum2);
    free(LEresult);
    return EXIT_NO_ERRORS;
}

int multiply(char* num1, char* num2, char* result, int sizeOfcalloc) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    char* LEnum1 = (char *) calloc(sizeOfcalloc, sizeof(char));     
    char* LEnum2 = (char *) calloc(sizeOfcalloc, sizeof(char));
    char* LEresult = (char *) calloc(sizeOfcalloc, sizeof(char));

    char** LEmultiples = (char **) calloc(len1, sizeof(char *));
    char** multiples = (char **) calloc(len1, sizeof(char *));
    for (int i = 0; i < len1; i++) {
        LEmultiples[i] = (char *) calloc(2*sizeOfcalloc, sizeof(char));
        multiples[i] = (char *) calloc(2*sizeOfcalloc, sizeof(char));
    }


    endienneReverser(num1, LEnum1);
    endienneReverser(num2, LEnum2);


    for (int i = 0; i < len1; i++) {
        int next_ptr = 0;
        int* next_ptr_ptr = &next_ptr;

        char operand1 = LEnum1[i];
        for (int j = 0; j < i; j++) {
            LEmultiples[i][next_ptr] = '0';
            *next_ptr_ptr += 1;
        }

        int digit1 = LEnum1[i] - 48;
        for (int j = 0; j < len2; j++) {
            int digit2 = LEnum2[j] - 48;
            int product = digit1 * digit2;
            int carry = product / 10;
            int* carry_ptr = &carry;
            product -= carry * 10;


            LEmultiples[i][next_ptr] += product;


            if (LEmultiples[i][next_ptr] > 9) {
                *carry_ptr += LEmultiples[i][next_ptr] / 10;
                LEmultiples[i][next_ptr] -= (LEmultiples[i][next_ptr] / 10) * 10;
            }


            LEmultiples[i][next_ptr+1] = carry;

            LEmultiples[i][next_ptr] += 48;

            *next_ptr_ptr += 1;

        }

        LEmultiples[i][next_ptr] += 48;


        if (LEmultiples[i][next_ptr] > '9') {
            LEmultiples[i][next_ptr+1] = (LEmultiples[i][next_ptr] - 48) / 10;
            LEmultiples[i][next_ptr] -= ((LEmultiples[i][next_ptr] - 48) / 10) * 10;
            LEmultiples[i][next_ptr+2] = '\0';
        } else {
            LEmultiples[i][next_ptr+1] = '\0';
        }
    }


    if (len1 > 1) {
        for (int i = 0; i < len1; i++) {
            endienneReverser(LEmultiples[i], multiples[i]);
        }

        add(multiples[0], multiples[1], result, sizeOfcalloc);
        for (int i = 2; i < len1; i++) {
            add(result, multiples[i], result, sizeOfcalloc);
        }
    } else {
        endienneReverser(LEmultiples[0], result);
    }

    free(LEnum1);
    free(LEnum2);
    free(LEresult);
    for (int i = 0; i < len1; i++)
        free(LEmultiples[i]);
    
    free(LEmultiples);
    return EXIT_NO_ERRORS;
    
}

int calculateFactorial(char* StrNumber, int number, char* result, int sizeOfCalloc) {

    char* currentNum = (char *) calloc(sizeOfCalloc, sizeof(char));

    strcpy(currentNum, StrNumber);
    sprintf(result, "%i", number - 1);
    multiply(StrNumber, result, result, sizeOfCalloc);



    for (int i = number-2; i > 1; i--) {
        sprintf(currentNum, "%i", i);

        multiply(currentNum, result, result, sizeOfCalloc);
    }


    free(currentNum);
    return EXIT_NO_ERRORS;
}

int removePrecedingZeros(char* number, char* result, int sizeOfCalloc) {
    int len1 = strlen(number);
    int lastDigit = 0;
    int* lastDigit_ptr = &lastDigit;

    char* LEnumber = (char *) calloc(sizeOfCalloc, sizeof(char));

    endienneReverser(number, LEnumber);

    for (int i = len1-1; i >= 0; i--) {
        if (i == 0) {
            free(LEnumber);
            return EXIT_ERROR;
        } else if (LEnumber[i] != '0') {
            LEnumber[i+1] = '\0';
            break;
        }
    }

    endienneReverser(LEnumber, result);

    free(LEnumber);
    return EXIT_NO_ERRORS;
}

int AddDigits(char* number, int* result) {
    int len = strlen(number);
    *result = 0; 

    for (int i = 0; i < len; i++) {
        if ((number[i] < '0') || (number[i] > '9')) {
            return EXIT_ERROR;
        }

        *result += (int) (number[i] - 48);
    }

    return EXIT_NO_ERRORS;
}


int main(int argc, char** argv) {
    // Print use case:
    if (argc == 1) {
        printf("Usage: %s Number\n", argv[0]);
        return EXIT_ERROR;
    }

    // Check arg count:
    if (argc != 2) {
        printf("Error: Incorrect Argument Count.");
        return EXIT_ERROR;
    }

    // Make sure the argument is valid:
    for (char* current_letter = argv[1]; current_letter < argv[1] + strlen(argv[1]); current_letter++) {
        if ((*current_letter > '9') || (*current_letter < '0')) {
            printf("Error: Invalid Argument.\n");
            return EXIT_ERROR;
        }
    }

    int number = atoi(argv[1]);

    char* strNumber = (char *) calloc(strlen(argv[1])+1, sizeof(char));
    char* factorial = (char *) calloc(5 * number, sizeof(char));

    strcpy(strNumber, argv[1]);

    if (!factorial) {
        free(strNumber);
        free(factorial);

        printf("Error: Number malloc failed (arg may be too large).\n");
        return EXIT_ERROR;
    }

    int sizeOfCalloc = 5 * number;

    calculateFactorial(strNumber, number, factorial, sizeOfCalloc);
    removePrecedingZeros(factorial, factorial, sizeOfCalloc);

    int result = 0;

    AddDigits(factorial, &result);

    printf("%i\n", result);

    free(strNumber);
    free(factorial);

    return EXIT_NO_ERRORS;
}