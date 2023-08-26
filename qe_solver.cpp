#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "qe_solver.h"
#include "comparators.h"
#include "format_complex.h"
#include "make_logs.h"

static double calculate_discriminant(const double a, const double b, const double c);

static bool check_specific_cases(const double a, const double b, const double c, double _Complex *x1, double _Complex *x2, int *num_of_roots);

// Local functions initialization

// Returns discriminant value
static double calculate_discriminant(const double a, const double b, const double c)
{
    MY_ASSERT(std::isfinite(a));
    MY_ASSERT(std::isfinite(b));
    MY_ASSERT(std::isfinite(c));

//    char str[5] = {};
//    strcpy(str,"D = ");

    double d = b*b - 4*a*c;
//    my_printf("aboba %f\n", d);
//    LOG(strcat(str ,complex_number_to_str(d + I*0)), LOG_MESSAGE);

    return d;
}

// Check for specific cases of quadratic equation
static bool check_specific_cases(const double a, const double b, const double c, double _Complex *x1, double _Complex *x2, int *num_of_roots)

// Should i check for incomplete quadratic equations? (ax^2 + c = 0) ) (ax^2 + bx = 0)

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

    if(std::isfinite(a) && std::isfinite(b) && std::isfinite(c)) // If number is finite move forward
    {
        if(!check_specific_cases(a, b, c, x1, x2, num_of_roots))    // If it isn't specific case move forward otherwise return true
        {
            double d = calculate_discriminant(a,b,c);

            *x1 = *x2 = -b/(a*2.0);

            if (compare_with_zero(d) == 0)         // D == 0
            {
                *num_of_roots = ONE_ROOT;
            }
            else
            {
                const double d_sqrt_half = sqrt(fabs(d))/(a*2.0);

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
            }
        }

        return true;
    }

    return false;
}

// Return string in root form
char* cast_to_root_format(int n, _Complex double root)
{
    char *root_string = (char *) malloc(50 * sizeof(char));

    sprintf(root_string, "x%c = %s", (n == 0) ? ' ' : n + '0', complex_number_to_str(root));

    return root_string;
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
            printf("%s\n", cast_to_root_format(0, x1));
            break;
        }

        case TWO_ROOTS: {

            printf("%s %s\n", cast_to_root_format(1, x1), cast_to_root_format(2, x2));
            break;
        }

        default: break;
    }
}
