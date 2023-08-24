#include <math.h>
#include <assert.h>
#include <complex.h>
#include <string.h>

#include "comparators.h"

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
    if (cabs(a-b) < PRECISION) return 0; // a == b
    if (cabs(a-b) > 0.0) return 1;               // a > b
    return -1;                         // a < b
}

int complex_isnan(_Complex double x)
{
    return (std::isnan(creal(x)) && std::isnan(cimag(x)));
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
