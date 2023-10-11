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
        sprintf(complex_string, "%.2lf%+.2lfi", creal(a), cimag(a));

    else if (compare_with_zero(creal(a)) != 0 && compare_with_zero(cimag(a)) == 0)
    sprintf(complex_string, "%.2lf", creal(a)); // TODO: align

    else if (compare_with_zero(creal(a)) == 0 && compare_with_zero(cimag(a)) != 0)
        sprintf(complex_string, "%+.2lfi", cimag(a));

    return complex_string;
}


// TODO: delete?
_Complex double complex_from_parts(double real, double imag)
{
    if(std::isnan(real) && std::isnan(imag))
        return NAN;
    else if(std::isnan(real) || std::isnan(imag))
    {
        real = (std::isnan(real)) ? 0 : real;
        imag = (std::isnan(imag)) ? 0 : imag;
    }

    return real + I*imag;
}
