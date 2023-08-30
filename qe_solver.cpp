#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "qe_solver.h"
#include "comparators.h"
#include "colors.h"
#include "format_complex.h"
#include "make_logs.h"

static double calculate_discriminant(const double a, const double b, const double c);

static bool check_specific_cases(const double a, const double b, const double c, double _Complex *x1, double _Complex *x2, int *num_of_roots);


// Returns discriminant value
static double calculate_discriminant(const double a, const double b, const double c)
{
    double d = NAN;
    if (std::isfinite(a) && std::isfinite(b) && std::isfinite(c))
        d = b*b - 4*a*c;

    LOG(LOG_LVL_MESSAGE, "D = %.3g", d);

    return d;
}

// Check for specific cases of quadratic equation
static bool check_specific_cases(const double a, const double b, const double c, double _Complex *x1, double _Complex *x2, int *num_of_roots)
{
// Should i check for incomplete quadratic equations? (ax^2 + c = 0) or (ax^2 + bx = 0) TODO: measure and tell me!

// Expects that this function calls only from solve_quadratic_equation() (no asserts)

    if (compare_with_zero(a) == 0 && compare_with_zero(b) != 0 && compare_with_zero(c) != 0)    // Linear equation
    {
        solve_linear_equation(b,c,x1);
        *num_of_roots = ONE_ROOT;

        LOG(LOG_LVL_MESSAGE, "Equation is linear");

        return false;
    }

    if (compare_with_zero(a) != 0 && compare_with_zero(b) == 0 && compare_with_zero(c) == 0)  // Linear equation with root = 0
    {
        *x1 = 0;
        *num_of_roots = ONE_ROOT;

        LOG(LOG_LVL_MESSAGE, "Equation is linear with root = 0");

        return false;
    }

    if (compare_with_zero(a) == 0 && compare_with_zero(b) == 0)
    {
        if (compare_with_zero(c) == 0)
        {
            *num_of_roots = INFINITE_ROOTS;                // Root is any number

            LOG(LOG_LVL_MESSAGE, "Root is any number");

            return false;
        }
        else
        {
            *num_of_roots = NO_ROOTS;

            LOG(LOG_LVL_MESSAGE, "Equation have no roots");

            return false;                                        // No roots
        }
    }

    return true;

}

// Global functions initialization

void solve_linear_equation(const double b, const double c, double _Complex *x1)
{
    assert(x1);

    assert(std::isfinite(b));
    assert(std::isfinite(c));

    *x1 = -b/c;
}


// Returns the number of roots
bool solve_quadratic_equation(const double a, const double b, const double c, double _Complex *x1, double _Complex *x2, int *num_of_roots)
{
    assert(x1);
    assert(x2);
    assert(num_of_roots);

    *x1 = *x2 = NAN;
    *num_of_roots = NO_ROOTS;

    if (std::isfinite(a) && std::isfinite(b) && std::isfinite(c))    // If number is finite move forward
    {
        if (check_specific_cases(a, b, c, x1, x2, num_of_roots))    // If it isn't specific case move forward otherwise return true
        {
            double d = calculate_discriminant(a,b,c);

            if (std::isfinite(d))
            {

                *x1 = *x2 = -b/(a*2.0);

                if (compare_with_zero(d) == 0)         // D == 0
                {
                    LOG(LOG_LVL_MESSAGE, "Equation have one root\nx = ", complex_number_to_str(*x1));

                    *num_of_roots = ONE_ROOT;
                }
                else
                {
                    const double d_sqrt_half = sqrt(fabs(d)) / (a*2.0);

                    if (compare_with_zero(d) > 0)      // D > 0
                    {
                        *x1 -= d_sqrt_half;
                        *x2 += d_sqrt_half;
                    }
                    else
                    {
                        *x1 -= I*d_sqrt_half;          // D < 0
                        *x2 += I*d_sqrt_half;
                    }


                    *num_of_roots =  TWO_ROOTS;

                    LOG(LOG_LVL_MESSAGE, "Equation have two roots\n%s %s", complex_number_to_str(*x1), complex_number_to_str(*x2));
                }
            }
        }

        return false;
    }

    print_with_anim(COLOR_STD, "Coefficients aren't finite\n");

    return true;
}

// Show roots on the display
void print_roots(const double _Complex x1, const double _Complex x2, const int num_of_roots)
{
    switch (num_of_roots)
    {
        case INFINITE_ROOTS: {
            print_with_anim(COLOR_STD, "X belongs to R\n");
            break;
        }

        case NO_ROOTS: {
            print_with_anim(COLOR_STD, "No roots\n");
            break;
        }

        case ONE_ROOT: {

            char *ptr_1 = complex_number_to_str(x1);
            print_with_anim(COLOR_STD, "x = %s\n", ptr_1);
            free(ptr_1);
            break;
        }

        case TWO_ROOTS: {
            char *ptr_1 = complex_number_to_str(x1);
            char *ptr_2 = complex_number_to_str(x2);
            print_with_anim(COLOR_STD, "x1 = %s x2 = %s\n", ptr_1, ptr_2);
            free(ptr_1);
            free(ptr_2);
            break;
        }

        default: break;
    }
}
