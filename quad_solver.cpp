#define   TX_COMPILED
#include <TXlib.h>

#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>
#include <limits.h>

#include "quad_solver.h"

// Constants initialization

const int INFINITE_ROOTS = INT_MAX;
const int NO_ROOTS = 0;
const double PRECISION = 0.001;


// Local functions initialization
static int compare_with_zero(double a);

static int compare_with_zero(double a)
{
    if (fabs(a) < PRECISION) return 0; // a == 0
    if (a > 0.0) return 1;               // a > PRECISION
    return -1;                         // a < PRECISION
}

static int compare_complex_doubles(double _Complex a, double _Complex b);

static int compare_complex_doubles(double _Complex a, double _Complex b)
{
    if (cabs(a-b) < PRECISION) return 0; // a == b
    if (cabs(a-b) > 0.0) return 1;               // a > b
    return -1;                         // a < b
}

static void swap_complex(double _Complex *a, double _Complex *b);

static void swap_complex(double _Complex *a, double _Complex *b)
{
    if(compare_complex_doubles(*a, *b) > 0) // If a > b swap it
    {
        double _Complex temp = NAN;
        temp = *a;
        *a = *b;
        *b = temp;
    }

}


// Global functions initialization


int test_all_equations()
{
    int number_of_success = 0;
    number_of_success += test_one_equation(1, 1,-7,12,3,4,2);
    return number_of_success;
}

int test_one_equation(int num_of_test, double a, double b, double c, double _Complex x1_ref, double _Complex x2_ref, int num_of_roots_ref)
{
    double _Complex x1 = NAN, x2 = NAN;
    int num_of_roots = NAN;

    solve_quadratic_equation(a, b, c, &x1, &x2, &num_of_roots);

    swap_complex(&x1,&x2);
    swap_complex(&x1_ref,&x2_ref);

    if (num_of_roots == num_of_roots_ref)
    {
        if(compare_complex_doubles(x1, x1_ref) == 0 || compare_complex_doubles(x2, x2_ref) == 0)
        {
            printf("TEST №%d: OK\n", num_of_test);
            return 1;
        }
    }

    printf("TEST №%d FAILED: x1 = %lf, x2 = %lf, num_of_roots = %d\n"
           "      EXPECTED: x1_ref = %lf, x2_ref = %lf, num_of_roots_ref = %d\n",\
         num_of_test, creal(x1), creal(x2), num_of_roots, creal(x1_ref), creal(x2_ref), num_of_roots_ref);
    return 0;

}


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
        *NumberOfRoots = 1;
        return true;
    }

    if (compare_with_zero(a) != 0 && (compare_with_zero(b) == 0) && (compare_with_zero(c) == 0)) // Linear equation with root = 0
    {
        *x1 = 0;
        *NumberOfRoots = 1;
        return true;
    }

    if (compare_with_zero(a) == 0 && compare_with_zero(b) == 0)
    {
        if (compare_with_zero(c) == 0)
        {
            *NumberOfRoots = INFINITE_ROOTS;                // Root is any number
            return true;
        }
        else
        {
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
            printf("X принадлежит R\n");
            break;
        }

        case NO_ROOTS: {
            printf("Нет корней\n");
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
