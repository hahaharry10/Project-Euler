import numpy as np

def binarySearch(x, array, arr_len):
    start = 0
    end = arr_len - 1
    while (start != end):
        mid = int((start+end) / 2)
        if (array[mid] == x):
            return 0
        elif (array[mid] < x):
            start = mid + 1
        elif (array[mid] > x):
            end = mid - 1
        #ENDIF
    #ENDWHILE

    return 1
#ENDFUNCTION


def calculateTotient(n, primes, primes_len):
    rel_prim = 0

    isPrime = 1
    totient = n

    for i in range(1, primes_len):
        if n%primes[i] == 0:
            totient = totient * (1 - (1/primes[i]))
            isPrime = 0
        #ENDIF
    #ENDFOR

    if (isPrime):
        primes[primes_len] = n
        primes_len += 1
    #ENDIF

    return totient, primes, primes_len
#ENDFUNCTION

userIn = int(input("Enter a number: "))

primes = np.zeros(5761455)
primes_len = 0

for i in range(1, userIn+1):
    totient, primes, primes_len = calculateTotient(i, primes, primes_len)
    if (i == userIn):
        print(f"Totient = {totient}")
    #ENDIF
#ENDFOR