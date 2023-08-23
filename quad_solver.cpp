#define   TX_COMPILED
#include <TXlib.h>

#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>

#include "quad_solver.h"

// Constants initialization


// Local functions initialization
static int compare_with_zero(double a);

static int compare_with_zero(double a)
{
    if (fabs(a) < PRECISION) return 0; // a == 0
    if (a > 0.0) return 1;               // a > PRECISION
    return -1;                         // a < PRECISION
}


// Global functions initialization


// Returns discriminant value
double calculate_discriminant(const double a, const double b, const double c)
{
    return (b*b - 4*a*c);
}

void solve_linear_equation(const double b, const double c, double _Complex *x1)
{
    assert(x1);
    *x1 = -b/c;
}


// Returns the number of roots
bool solve_quadratic_equation(const double a, const double b, const double c, double _Complex *x1, double _Complex *x2, int *NumberOfRoots)
{
    assert(x1);
    assert(x2);

    if(!std::isfinite(a) || !std::isfinite(b) || !std::isfinite(c))
    {
        printf("Некорректный коэффициент\n");
        return false;
    }

    if ((compare_with_zero(a) == 0) && compare_with_zero(b) != 0 && compare_with_zero(c) != 0) // Linear equation
    {
        solve_linear_equation(b,c,x1);
        *x2 = NAN;
        *NumberOfRoots = 1;
        return true;
    }

    if (compare_with_zero(a) != 0 && (compare_with_zero(b) == 0) && (compare_with_zero(c) == 0)) // Linear equation with root = 0
    {
        *x1 = 0;
        *x2 = NAN;
        *NumberOfRoots = 1;
        return true;
    }

    if (compare_with_zero(a) == 0 && compare_with_zero(b) == 0)
    {
        if (compare_with_zero(c) == 0)
        {
            *x1 = NAN;
            *x2 = NAN;
            *NumberOfRoots = INFINITE_ROOTS;                // Root is any number
            return true;
        }
        else
        {
            *x1 = NAN;
            *x2 = NAN;
            *NumberOfRoots = NO_ROOTS;
            return true;                                        // No roots
        }
    }

    double d = calculate_discriminant(a,b,c);

    const double d_sqrt_half = sqrt(fabs(d))/(a*2.0);

    *x1 = *x2 = -b/(a*2.0);

    if (compare_with_zero(d) > 0) // D > 0
    {

        *x1 -= d_sqrt_half;
        *x2 += d_sqrt_half;
        *NumberOfRoots = 2;
        return true;
    }
    else if (compare_with_zero(d) == 0) // D == 0
    {
        *x2 = NAN;
        *NumberOfRoots = 1;
        return true;
    }
    else                               // D < 0
    {
        *x1 -= I*d_sqrt_half;
        *x2 += I*d_sqrt_half;
        *NumberOfRoots =  2;
        return true;
    }
    return false;
}

// Show roots on the display
void print_roots(const double _Complex x1, const double _Complex x2, const int NumberOfRoots)
{
    switch(NumberOfRoots)
    {
        case INFINITE_ROOTS: {
            printf("X belongs to R\n");
            break;
        }

        case NO_ROOTS: {
            printf("No roots\n");
            break;
        }

        case 1: {
            printf("x = %.2lf\n",creal(x1));
            break;
        }

        case 2: {
            if(compare_with_zero(cimag(x1)) == 0) // If imaginary part = 0 print only real part
                printf("x1 = %.2lf, x2 = %.2lf\n", creal(x1), creal(x2));
            else
                printf("x1 = %.2lf%+.2lfi, x2 = %.2lf%+.2lfi\n",creal(x1), cimag(x1), creal(x2),cimag(x2));
            break;
        }

        default: break;
    }
}
