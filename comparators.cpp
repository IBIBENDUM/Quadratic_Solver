#include <math.h>
#include <assert.h>
#include <complex.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "make_logs.h"
#include "comparators.h"

bool complex_isnan(_Complex double x)
{
    return (std::isnan(creal(x)));                   // _Complex double a=NAN;
                                                     // creal(a) == NAN; true
                                                     // cimag(a) == 0;   true
    // TODO:                                        ^~ why so far?
    // TODO:                                        it's not aligned anyway
}

int compare_with_zero(const double a)
{
//    assert(std::isfinite(a));

    compare_doubles(a, 0); // TODO: ?? return??
    // TODO: Bahtiyar ka ti testiruesh svoi cod?
    // TODO: Bahtiyar jak ti testiruesh tviy cod?
    // TODO: Bahtiyar how did you test your code?
    // TODO: Bahtiyar Wie haben Sie Ihren Code getestet?
    // TODO: Bahtijar, sez yz kodygyzny nicek synadygyz?
    // TODO: バチヤどのようにコードをテストしましたか？
}

int compare_doubles(const double a, const double b)
{
    assert(std::isfinite(a));
    assert(std::isfinite(b));

    if (fabs(a - b) < SMALL_PRECISION)               // a equals to b
        return 0;

    if (a - b > 0)                                   // a > b
        return 1;

    return -1;                                       // a < b
}

int compare_complex_doubles(const double _Complex a, const double _Complex b)
{
    if (complex_isnan(a) && complex_isnan(b))                       // NAN equals to NAN
        return 0;

    if (complex_isnan(a) && !complex_isnan(b))                      // NAN > b
        return 1;

    if (!complex_isnan(a) && complex_isnan(b))                      // a < NAN
        return -1;

    if (compare_doubles(fabs(cimag(a)), fabs(cimag(b))) == 0)       // 1.23+4i ~ 5.67+5i if there attempt compare complex return -1
    {                                                               //
        if (compare_with_zero(cimag(a)) == 0)                       // 1.23 < 4.56
            return compare_doubles(creal(a), creal(b));             //
                                                                    //
        if (compare_doubles(creal(a), creal(b)) == 0)               //
            return compare_doubles(cimag(a), cimag(b));             // 3.45-i < 3.45+i
    }                                                               //
                                                                    //
    return -1;
}


// TODO: align "\"
// TODO: is this swap variables? rename!
#define SWAP_VARIABLES(A, B)     \
    do                            \
    {				               \
        double _Complex temp = NAN;	\
        temp = (A);			         \
        (A) = (B);			          \
        (B) = temp;			           \
    }                                   \
    while(0)

void sort_complex(double _Complex *a, double _Complex *b)
{
    if(compare_complex_doubles(*a, *b) > 0)          // If a > b swap it
        SWAP_VARIABLES(*a,*b);
    //                    ^ TODO: space
}

#undef SWAP_VARIABLES
