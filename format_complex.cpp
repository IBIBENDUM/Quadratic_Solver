#include <stdio.h>
#include <complex.h>
#include <stdlib.h>
#include <assert.h>

#include "format_complex.h"
#include "comparators.h"

// TODO: delete?
char* complex_number_to_str(_Complex double a)
{
    char *complex_string = (char *) calloc(COMPLEX_STR_LEN, sizeof(char));

    if (complex_isnan(a))
        sprintf(complex_string, "NaN");

    else if (compare_with_zero(creal(a)) != 0 && compare_with_zero(cimag(a)) != 0)
        sprintf(complex_string, "%.2lg%+.2lgi", creal(a), cimag(a));

    else if (compare_with_zero(creal(a)) != 0 && compare_with_zero(cimag(a)) == 0)
    sprintf(complex_string, "%.2lf", creal(a)); // TODO: align

    else if (compare_with_zero(creal(a)) == 0 && compare_with_zero(cimag(a)) != 0)
        sprintf(complex_string, "%+.2lgi", cimag(a));

    return complex_string;
}


// TODO: delete?
_Complex double complex_from_parts(double real, double imag)
{
    if(isnan(real) && isnan(imag))                  // If the test enters NAN
        return NAN;                                 // (assuming that if there is no part then it is equal to NAN)
    else if(isnan(real) || isnan(imag))             // converts NAN to 0
    {
        real = (isnan(real)) ? 0 : real;
        imag = (isnan(imag)) ? 0 : imag;
    }

    return real + I*imag;
}
