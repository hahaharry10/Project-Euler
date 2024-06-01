import numpy as np


def createCoeficientsOfE(limit):
    coeff = np.array([2, 1]) # Start off array

    for i in range(1, int(limit / 2) + 1):
        coeff = np.append(coeff, (i*2, 1, 1))
    #ENDFOR
    
    return coeff
#ENDFUNCTION

# return value is in form: (numerator, denominator)
def fraction(coeff, ptr, limit):
    if (ptr == limit):
        return np.double( 1 ), np.double( coeff[ptr] )
    else:
        num1, den1 = fraction(coeff, ptr+1, limit)
        num2 = np.double( coeff[ptr] )
        den2 = np.double( 1 )

        # cross multiply both fractions:
        num3 = np.double( (num1 * den2) + (num2 * den1) )
        den3 = np.double( den1 * den2 )

        return den3, num3
    #ENDIF
#ENDFUNCTION


def addDigits(x):
    x = str(int(x))

    sum = 0

    for digit in x:
        sum += int(digit)
    #ENDFOR

    return sum
#ENDFUNCTION


def calculateFraction(limit):

    coeff = createCoeficientsOfE(limit)

    den, num = fraction(coeff, 0, limit)

    sum = addDigits(num)

    return sum
#ENDFUNCTION


np.set_printoptions(suppress=True, formatter={'float_kind':'{:16.3f}'.format}, linewidth=130)

if __name__ == "__main__":
    conv = np.double(100)
    print(calculateFraction(conv-1))
#ENDIF
