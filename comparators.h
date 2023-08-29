#ifndef COMPARATORS_H_
#define COMPARATORS_H_

#include <stdbool.h>
const double PRECISION = 0.0000001;
const double SMALL_PRECISION = 0.01;

/// Return true if complex real part is NAN
bool complex_isnan(_Complex double x);

/// Compare double with zero
/// ### Example
/// ~~~~~~~~~~~~~~~~~~~.cpp
/// compare_with_zero(a) > 0 // true if a > 0
/// compare_with_zero(a) == 0
/// compare_with_zero(a) < 0
/// ~~~~~~~~~~~~~~~~~~~
/// @return -1 if a < 0@n 0 if a == 0@n 1 if a > 0
int compare_with_zero(const double a);

/// Compare complex doubles
///
/// If a == b return 1@n
/// If one of the numbers is NAN compare other number with NAN@n
/// It's considered that NAN is greater than any number
/// ### Example
/// ~~~~~~~~~~~~~~~.cpp
/// compare_complex_doubles(a, NAN) // return -1
/// compare_complex_doubles(NAN, b) // return 1
/// compare_complex_doubles(NAN, NAN) // return 0
/// compare_complex_doubles(a, b) // return 0
/// ~~~~~~~~~~~~~~~
/// @attention If a != NAN && b != NAN always return 0
/// @param a, b Complex numbers
/// @param precision Precision with
int compare_complex_doubles(const double _Complex a, const double _Complex b);

/// Sort complex number by ascending
void sort_complex_by_ascending(double _Complex *a, double _Complex *b);

int compare_doubles(const double a, const double b);

#endif
