#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

#include "quad_solver.h"
#include "comparators.h"

static double calculate_discriminant(const double a, const double b, const double c);

static bool check_specific_cases(const double a, const double b, const double c, double _Complex *x1, double _Complex *x2, int *num_of_roots);

// Global functions initialization

// Returns discriminant value

double calculate_discriminant(const double a, const double b, const double c)
{
    assert(std::isfinite(a));
    assert(std::isfinite(b));
    assert(std::isfinite(c));
    return (b*b - 4*a*c);
}

void solve_linear_equation(const double b, const double c, double _Complex *x1)
{
    assert(x1);

    assert(std::isfinite(b));
    assert(std::isfinite(c));

    *x1 = -b/c;
}

bool check_specific_cases(const double a, const double b, const double c, double _Complex *x1, double _Complex *x2, int *num_of_roots)
{
    *x1 = *x2 = NAN;

    if ((compare_with_zero(a) == 0) && compare_with_zero(b) != 0 && compare_with_zero(c) != 0) // Linear equation
    {
        solve_linear_equation(b,c,x1);
        *num_of_roots = ONE_ROOT;
        return true;
    }

    if (compare_with_zero(a) != 0 && (compare_with_zero(b) == 0) && (compare_with_zero(c) == 0)) // Linear equation with root = 0
    {
        *x1 = 0;
        *num_of_roots = ONE_ROOT;
        return true;
    }

    if (compare_with_zero(a) == 0 && compare_with_zero(b) == 0)
    {
        if (compare_with_zero(c) == 0)
        {
            *num_of_roots = INFINITE_ROOTS;                // Root is any number
            return true;
        }
        else
        {
            *num_of_roots = NO_ROOTS;
            return true;                                        // No roots
        }
    }

    return false;

}


// Returns the number of roots
bool solve_quadratic_equation(const double a, const double b, const double c, double _Complex *x1, double _Complex *x2, int *num_of_roots)
{
    assert(x1);
    assert(x2);

    *x1 = *x2 = NAN;

    if(!std::isfinite(a) || !std::isfinite(b) || !std::isfinite(c))
    {
        return false;
    }
    if(check_specific_cases(a, b, c, x1, x2, num_of_roots))
        return true;

    double d = calculate_discriminant(a,b,c);


    *x1 = *x2 = -b/(a*2.0);

    if (compare_with_zero(d) == 0) // D == 0
    {
        *num_of_roots = ONE_ROOT;
        return true;
    }

    const double d_sqrt_half = sqrt(fabs(d))/(a*2.0);

    if (compare_with_zero(d) > 0) // D > 0
    {
        *x1 -= d_sqrt_half;
        *x2 += d_sqrt_half;
        *num_of_roots = TWO_ROOTS;
        return true;
    }

    *x1 -= I*d_sqrt_half;        // D < 0
    *x2 += I*d_sqrt_half;
    *num_of_roots =  TWO_ROOTS;
    return true;
}

// Show roots on the display
void print_roots(const double _Complex x1, const double _Complex x2, const int num_of_roots)
{
    switch(num_of_roots)
    {
        case INFINITE_ROOTS: {
            printf("X belongs to R\n");
            break;
        }

        case NO_ROOTS: {
            printf("No roots\n");
            break;
        }

        case ONE_ROOT: {
            printf("x = %s\n", complex_number_to_str(x1));
            break;
        }

        case TWO_ROOTS: {

            printf("x1 = %s x2 = %s\n", complex_number_to_str(x1), complex_number_to_str(x2));
            break;
        }

        default: break;
    }
}
