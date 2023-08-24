#include <math.h>
#include <assert.h>
#include <complex.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "comparators.h"
// rename heading

int compare_with_zero(const double a)
{
//    assert(!std::isfinite(a));

    if (fabs(a) < PRECISION)           // a == 0
        return 0;

    if (a > 0.)                        // a > PRECISION
        return 1;

    return -1;                         // a < PRECISION
}

int compare_complex_doubles(const double _Complex a, const double _Complex b)
{
    if(complex_isnan(a) && complex_isnan(b))  // NAN == NAN
        return 0;

    if(complex_isnan(a) && !complex_isnan(b)) // NAN < b
        return -1;

    if(!complex_isnan(a) && complex_isnan(b)) // a > NAN
        return 1;

    if (cabs(a-b) < PRECISION)          // a == b
        return 0;
                                        // a > b
    if (cabs(a-b) > 0.0)
        return 1;                       // a < b
    return -1;
}

int complex_isnan(_Complex double x)
{
    return (std::isnan(creal(x)) ||  std::isnan(cimag(x)));
}


#define SWAP_VARIABLES(A, B)\
do {\
double _Complex temp = NAN;\
temp = (A);\
(A) = (B);\
(B) = temp;\
} while(0)
void sort_complex_by_ascending(double _Complex *a, double _Complex *b)
{
/*     assert(!std::isfinite(creal(*a)));
 *     assert(!std::isfinite(cimag(*a)));
 *
 *     assert(!std::isfinite(creal(*b)));
 *     assert(!std::isfinite(cimag(*b)));
 */
    if(compare_complex_doubles(*a, *b) > 0) // If a > b swap it
        SWAP_VARIABLES(*a,*b);
}
#undef SWAP_VARIABLES

int get_expected_args_amount(const char *format)
{
    int expected_args_amount = 0;
    for (unsigned int i = 0; i < strlen(format); i++)
    {
        if(format[i] == '%')
            expected_args_amount++;
    }
    return expected_args_amount;

}


const int MAX_LEN = 11;
char* complex_number_to_str(_Complex double a)
{
    char *complex_string = (char *) malloc(MAX_LEN * sizeof(char));

    if (complex_isnan(a))
        sprintf(complex_string, "NaN");

    else if (compare_with_zero(cimag(a)) != 0 && compare_with_zero(cimag(a)) != 0)
        sprintf(complex_string, "%.2lf%+.2lfi", creal(a), cimag(a));

    else if (compare_with_zero(cimag(a)) != 0 && compare_with_zero(cimag(a)) == 0)
        sprintf(complex_string, "%.2lf", creal(a));

    else if (compare_with_zero(cimag(a)) == 0 && compare_with_zero(cimag(a)) != 0)
        sprintf(complex_string, "%+.2lfi", cimag(a));

    return complex_string;
}

