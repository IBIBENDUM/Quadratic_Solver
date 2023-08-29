#include <stdio.h>
#include <complex.h>
#include <stdlib.h>

#include "format_complex.h"
#include "comparators.h"

char* complex_number_to_str(_Complex double a)
{
    char *complex_string = (char *) malloc(MAX_LEN * sizeof(char));

    if (complex_isnan(a))
        sprintf(complex_string, "NaN");

    else if (compare_with_zero(creal(a)) != 0 && compare_with_zero(cimag(a)) != 0)
        sprintf(complex_string, "%.2lf%+.2lfi", creal(a), cimag(a));

    else if (compare_with_zero(creal(a)) != 0 && compare_with_zero(cimag(a)) == 0)
    sprintf(complex_string, "%.2lf", creal(a)); // TODO: clean this up, this is the same

    else if (compare_with_zero(creal(a)) == 0 && compare_with_zero(cimag(a)) != 0)
        sprintf(complex_string, "%+.2lfi", cimag(a));

    else if (compare_with_zero(creal(a)) == 0 && compare_with_zero(cimag(a)) == 0)
        sprintf(complex_string, "0.00");          //        ...as this

    return complex_string;
}


_Complex double write_complex_value_to_var(double real, double imag)
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
