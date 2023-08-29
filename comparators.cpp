#include <math.h>
#include <assert.h>
#include <complex.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "make_logs.h"
#include "comparators.h"

bool complex_isnan(_Complex double x)
{
    return (std::isnan(creal(x)));                   // _Complex double a=NAN;
                                                     // creal(a) == NAN; true
                                                     // cimag(a) == 0;   true
}

int compare_with_zero(const double a)
{
    assert(std::isfinite(a));

    if (fabs(a) < PRECISION)                         // a is 0
        return 0;

    if (a > 0.)                                      // a > PRECISION
        return 1;

    return -1;                                       // a < PRECISION
}

int compare_complex_doubles(const double _Complex a, const double _Complex b)  // compare only real part
{
    if(complex_isnan(a) && complex_isnan(b))         // NAN equals to NAN
        return 0;

    if(complex_isnan(a) && !complex_isnan(b))        // NAN > b
        return 1;

    if(!complex_isnan(a) && complex_isnan(b))        // a < NAN
        return -1;

    if (fabs(creal(a) - creal(b)) < SMALL_PRECISION) // a equals to b
        return 0;

    if (creal(a) - creal(b) > 0)                     // a > b
        return 1;

    return -1;
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
    if(compare_complex_doubles(*a, *b) > 0)          // If a > b swap it
        SWAP_VARIABLES(*a,*b);
}
#undef SWAP_VARIABLES
