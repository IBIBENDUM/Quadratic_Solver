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
#include "print_with_anim.h"

static double calculate_discriminant(const double a, const double b, const double c);

static bool check_specific_cases(const double a, const double b, const double c, double _Complex *x_ptr, int *num_of_roots_ptr);


// Returns discriminant value
static double calculate_discriminant(const double a, const double b, const double c)
{
    assert(isfinite(a) && isfinite(b) && isfinite(c));

    double d = b*b - 4*a*c;

    LOG(LOG_LVL_MESSAGE, "D = %.3g", d);

    return d;
}

// Check for specific cases of quadratic equation
static bool check_specific_cases(const double a, const double b, const double c, double _Complex *x_ptr, int *num_of_roots_ptr)
{
// Should i check for incomplete quadratic equations? (ax^2 + c = 0) or (ax^2 + bx = 0) TODO: measure and tell me!

// Expects that this function calls only from solve_quadratic_equation() (no asserts)

    assert(x_ptr&& num_of_roots_ptr);
    assert(std::isfinite(a) && std::isfinite(b) && std::isfinite(c));

    if (compare_with_zero(a) == 0 && compare_with_zero(b) != 0 && compare_with_zero(c) != 0)    // Linear equation
    {
        solve_linear_equation(b, c, x_ptr);
        *num_of_roots_ptr = ONE_ROOT;

        LOG(LOG_LVL_MESSAGE, "Equation is linear");

        return false;
    }

    if (compare_with_zero(a) != 0 && compare_with_zero(b) == 0 && compare_with_zero(c) == 0)  // Linear equation with root = 0
    {
        *x_ptr= 0;
        *num_of_roots_ptr = ONE_ROOT;

        LOG(LOG_LVL_MESSAGE, "Equation is linear with root = 0");

        return false;
    }

    if (compare_with_zero(a) == 0 && compare_with_zero(b) == 0)
    {
        if (compare_with_zero(c) == 0)
        {
            *num_of_roots_ptr = INFINITE_ROOTS;                // Root is any number

            LOG(LOG_LVL_MESSAGE, "Root is any number");

            return false;
        }
        else
        {
            *num_of_roots_ptr = NO_ROOTS;

            LOG(LOG_LVL_MESSAGE, "Equation have no roots");

            return false;                                        // No roots
        }
    }

    return true;

}

// Global functions initialization

void solve_linear_equation(const double a, const double b, double _Complex *x_ptr)
{
    assert(x_ptr);

    assert(std::isfinite(a) && std::isfinite(b));

    *x_ptr = -a/b;
}


// Returns the number of roots
bool solve_quadratic_equation(const double a, const double b, const double c, double _Complex *x1_ptr, double _Complex *x2_ptr, int *num_of_roots_ptr)
{
    assert(x1_ptr && x2_ptr && num_of_roots_ptr);

    assert(std::isfinite(a) && std::isfinite(b) && std::isfinite(c));         // assert because ask_coefs() check for finite numbers

    *x1_ptr = *x2_ptr = NAN;
    *num_of_roots_ptr = NO_ROOTS;

    if (check_specific_cases(a, b, c, x1_ptr, num_of_roots_ptr))    // If it isn't specific case move forward otherwise return true
    {
        double d = calculate_discriminant(a,b,c);

        if (std::isfinite(d))
        {

            *x1_ptr = *x2_ptr = -b/(a*2.0);

            if (compare_with_zero(d) == 0)         // D == 0
            {
                char x_str[COMPLEX_STR_LEN] = "";
                complex_number_to_str(x_str, *x1_ptr);

                LOG(LOG_LVL_MESSAGE, "Equation have one root\nx = %S", x_str);

                *num_of_roots_ptr = ONE_ROOT;
            }
            else
            {
                const double d_sqrt_half = sqrt(fabs(d)) / (a*2.0);

                if (compare_with_zero(d) > 0)      // D > 0
                {
                    *x1_ptr -= d_sqrt_half;
                    *x2_ptr += d_sqrt_half;
                }
                else
                {
                    *x1_ptr -= I*d_sqrt_half;          // D < 0
                    *x2_ptr += I*d_sqrt_half;
                }


                *num_of_roots_ptr =  TWO_ROOTS;

                char x1_str[COMPLEX_STR_LEN] = "";
                complex_number_to_str(x1_str, *x1_ptr);

                char x2_str[COMPLEX_STR_LEN] = "";
                complex_number_to_str(x2_str, *x2_ptr);

                LOG(LOG_LVL_MESSAGE, "Equation have two roots\nx1 = %s x2 = %s", x1_str, x2_str);
            }
        }
    }

    return false;
}


/*struct my_string {
    char buffer[64];
    char *external_buffer;

    int len, capacity;
};*/
// TODO: SSO: Small String Optimization

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


            // print_complex(ptr_1, x1);

            // write_complex_stringified(buffer, ptr_1); // write to buffer
            // write_complex_stringified(NULL,   ptr_1); // allocates to buffer

            // snprintf(NULL, 0, "%d", 1); // 2

            char x_str[COMPLEX_STR_LEN] = "";
            complex_number_to_str(x_str, x1);

            print_with_anim(COLOR_STD, "x = %s\n", x_str);
            break;
        }

        case TWO_ROOTS: {
            char x1_str[COMPLEX_STR_LEN] = "";
            complex_number_to_str(x1_str, x1);

            char x2_str[COMPLEX_STR_LEN] = "";
            complex_number_to_str(x2_str, x2);

            print_with_anim(COLOR_STD, "x1 = %s x2 = %s\n", x1_str, x2_str);
            break;
        }

        default: break;
    }
}
