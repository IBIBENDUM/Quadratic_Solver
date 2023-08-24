#define   TX_COMPILED
#include <TXlib.h>

#include <stdio.h>
#include <complex.h>

#include "quadratka_test.h"
#include "quad_solver.h"

static int compare_complex_doubles(double _Complex a, double _Complex b);

static void sort_complex_by_ascending(double _Complex *a, double _Complex *b);

static int get_file_size(FILE *file_ptr);

static int count_lines(FILE *file_ptr);

static int complex_isnan(_Complex double x)
{
//    return x!=x;
    return (std::isnan(creal(x)) && std::isnan(cimag(x)));
}

static int compare_complex_doubles(double _Complex a, double _Complex b)
{
    if (cabs(a-b) < PRECISION) return 0; // a == b
    if (cabs(a-b) > 0.0) return 1;               // a > b
    return -1;                         // a < b
}

static void sort_complex_by_ascending(double _Complex *a, double _Complex *b)
{
    if(compare_complex_doubles(*a, *b) > 0) // If a > b swap it
    {
        double _Complex temp = NAN;
        temp = *a;
        *a = *b;
        *b = temp;
    }
}

struct test_values_data {
    double a;
    double b;
    double c;
    double _Complex x1_ref;
    double _Complex x2_ref;
    int num_of_roots_ref;
};

static int get_file_size(FILE *file_ptr)
{
    int prev_pos = ftell(file_ptr);
    fseek(file_ptr, 0, SEEK_END);
    int size = ftell(file_ptr);
    fseek(file_ptr, prev_pos, SEEK_SET);

    return size;
}

static int count_lines(FILE *file_ptr)
{
    assert(file_ptr);

    int n = get_file_size(file_ptr)/(int)sizeof(char);
    char symbols[n];

    fseek(file_ptr, 0, SEEK_SET);

    fread(symbols, sizeof(float), n, file_ptr);

    int lines = 0;
    for(int i = 0; i < n; i++)
    {
        if(symbols[i] == '\n')
            lines++;
    }
    return lines;
}

bool read_reference_values(struct test_values_data *test_values, FILE *file_ptr)
{
    assert(file_ptr);
    double x1_real = NAN, x1_imag = NAN, x2_real = NAN, x2_imag = NAN;
    int aboba = 0;
    if ((aboba = fscanf(file_ptr, "%lf %lf %lf %lf %lf %lf %lf %d",
    &test_values->a,
    &test_values->b,
    &test_values->c,
    &x1_real,
    &x1_imag,
    &x2_real,
    &x2_imag,
    &test_values->num_of_roots_ref)) != 8)
    {
        return 0;
    }
    test_values->x1_ref = x1_real + x1_imag*I;
    test_values->x2_ref = x2_real + x2_imag*I;
    return 1;
}

#define TEST_EQUATION(num_of_test, a, b, c, x1_ref, x2_ref, num_of_roots_ref)\
    if(test_one_equation(num_of_test, a, b, c, x1_ref, x2_ref, num_of_roots_ref))\
        number_of_success += 1;\
    else\
        number_of_failed += 1

void test_all_equations(const char *filename)
{
    int number_of_success = 0, number_of_failed = 0;
    FILE *file_ptr = NULL;

    file_ptr = fopen(filename, "r");
    assert(file_ptr);

    int n = count_lines(file_ptr);
    struct test_values_data test_values;

    fseek(file_ptr, 0, SEEK_SET);

    int test_number = 0;

    for (int i = 0; i < n; i++)
    {
        if (!read_reference_values(&test_values, file_ptr))
            continue;
        test_number++;
        TEST_EQUATION(test_number,
                      test_values.a,
                      test_values.b,
                      test_values.c,
                      test_values.x1_ref,
                      test_values.x2_ref,
                      test_values.num_of_roots_ref);
    }

    printf("success: %d failed: %d\n", number_of_success, number_of_failed);
}
#undef TEST_EQUATION


int test_one_equation(int num_of_test, double a, double b, double c, double _Complex x1_ref, double _Complex x2_ref, int num_of_roots_ref)
{
    double _Complex x1 = NAN, x2 = NAN;
    int num_of_roots = NAN;

    solve_quadratic_equation(a, b, c, &x1, &x2, &num_of_roots);

    sort_complex_by_ascending(&x1_ref,&x2_ref);

    if (num_of_roots == num_of_roots_ref)
    {
        switch(num_of_roots)
        {
            case INFINITE_ROOTS:
            case NO_ROOTS:{
                printf("TEST ¹%d: OK\n", num_of_test); // No need compare values because where is no values
                return 1;
                break;
            }
            case 1:{
                if(compare_complex_doubles(x1, x1_ref) == 0) // Compare only x1 because x2 is NAN
                {
                    printf("TEST ¹%d: OK\n", num_of_test);
                    return 1;
                    break;
                }
            }
            case 2:{
                if(compare_complex_doubles(x1, x1_ref) == 0 && compare_complex_doubles(x2, x2_ref) == 0)
                {
                    printf("TEST ¹%d: OK\n", num_of_test);
                    return 1;
                    break;
                }
            }
            default: break;
        }
    }

    print_failed_values(num_of_test, x1, x2, num_of_roots);
    print_expected_values(x1_ref, x2_ref, num_of_roots_ref);
    return 0;

}

void print_expected_values(_Complex double x1_ref, _Complex double x2_ref, int num_of_roots_ref)
{
    if (compare_with_zero(creal(x1_ref)) != 0 && compare_with_zero(cimag(x1_ref)) != 0)
        printf("EXPECTED: x1 = %.2lf%+.2lfi, x2 = %.2lf%+.2lfi, num_of_roots_ref = %d\n",
        creal(x1_ref), cimag(x1_ref), creal(x2_ref), cimag(x2_ref), num_of_roots_ref);

    else if (compare_with_zero(creal(x1_ref)) == 0 && compare_with_zero(cimag(x1_ref)) != 0)
        printf("EXPECTED: x1 = %+.2lfi, x2 = %+.2lfi, num_of_roots_ref = %d\n",
        cimag(x1_ref), cimag(x2_ref), num_of_roots_ref);

    else if (compare_with_zero(creal(x1_ref)) != 0 && compare_with_zero(cimag(x1_ref)) == 0)
        printf("EXPECTED: x1 = %.2lf, x2 = %.2lf, num_of_roots_ref = %d\n",
        creal(x1_ref), creal(x2_ref), num_of_roots_ref);
}



void print_failed_values(int num_of_test, _Complex double x1, _Complex double x2, int num_of_roots)
{

    if(complex_isnan(x1) && complex_isnan(x2))
        printf("TEST ¹%d FAILED: x1 = NaN, x2 = NaN, num_of_roots = %d\n",
               num_of_test, num_of_roots);

    else if (!complex_isnan(x1) && complex_isnan(x2))
        printf("TEST ¹%d FAILED: x1 = NaN, num_of_roots = %d\n",
               num_of_test, num_of_roots);


    else if (!complex_isnan(x1) && !complex_isnan(x2))
    {
        if (compare_with_zero(creal(x1)) == 0 && compare_with_zero(creal(x2)) == 0)
            printf("TEST ¹%d FAILED: x1 = %+.2lfi, x2 = %+.2lfi, num_of_roots = %d\n",
            num_of_test, cimag(x1), cimag(x2), num_of_roots);

        else if (compare_with_zero(creal(x1)) != 0 && compare_with_zero(cimag(x1)) == 0 &&
                 compare_with_zero(creal(x2)) != 0 && compare_with_zero(cimag(x2)) == 0)
                 printf("TEST ¹%d FAILED: x1 = %.2lf, x2 = %.2lf, num_of_roots = %d\n",
                 num_of_test, creal(x1), creal(x2), num_of_roots);

        else if (compare_with_zero(creal(x1)) != 0 && compare_with_zero(cimag(x2)) != 0 &&
                 compare_with_zero(cimag(x1)) != 0 && compare_with_zero(cimag(x2)) != 0)
                 printf("TEST ¹%d FAILED: x1 = %.2lf%+.2lfi, x2 = %+.2lf%+.2lfi, num_of_roots = %d\n",
                 num_of_test, creal(x1), cimag(x1), creal(x1), cimag(x2), num_of_roots);
    }

}


