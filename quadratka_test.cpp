#define   TX_COMPILED
#include <TXlib.h>

#include <stdio.h>
#include <complex.h>

#include "quadratka_test.h"
#include "quad_solver.h"

static int compare_complex_doubles(double _Complex a, double _Complex b)
{
    if (cabs(a-b) < PRECISION) return 0; // a == b
    if (cabs(a-b) > 0.0) return 1;               // a > b
    return -1;                         // a < b
}

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

struct test_values_data {
    int num_of_test;
    double a;
    double b;
    double c;
    double _Complex x1_ref;
    double _Complex x2_ref;
    int num_of_roots_ref;
};

int count_lines(FILE *file_ptr)
{
    assert(file_ptr);   // почитать про file_stat для размера файла
                        // можно сразу же прочитать файл в буфер и потом в нем символы \n считать
    int lines = 0;
    int ch = 0;

    while(true)
    {
        ch = fgetc(file_ptr);
        if(ch == '\n')
            lines++;
        if(ch == EOF)
        {
            lines++;
            break;
        }
    }
    fseek(file_ptr, 0, SEEK_SET);
    return lines;
}

bool read_reference_values(struct test_values_data *test_values, FILE *file_ptr)
{
    assert(file_ptr);
    double x1_real = NAN, x1_imag = NAN, x2_real = NAN, x2_imag = NAN;
    ///
    if (fscanf(file_ptr, "%d %lf %lf %lf %lf %lf %lf %lf %d",
    &test_values->num_of_test,
    &test_values->a,
    &test_values->b,
    &test_values->c,
    &x1_real,
    &x1_imag,
    &x2_real,
    &x2_imag,
    &test_values->num_of_roots_ref) != 9)
//        return 0;

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
    // TODO: Make cases with 1 root work correctly
    int number_of_success = 0, number_of_failed = 0;
    FILE *file_ptr = NULL;

    file_ptr = fopen(filename, "r");
    assert(file_ptr);

    int n = count_lines(file_ptr);
    struct test_values_data test_values;


    for (int i = 0; i < n; i++)
    {
        if (!read_reference_values(&test_values, file_ptr))
            continue;
        TEST_EQUATION(test_values.num_of_test,
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

    swap_complex(&x1,&x2);
    swap_complex(&x1_ref,&x2_ref);

    /// TODO: Make NAN cases work correctly
    if (num_of_roots == num_of_roots_ref)
    {
        if(compare_complex_doubles(x1, x1_ref) == 0 && compare_complex_doubles(x2, x2_ref) == 0)
        {
            printf("TEST №%d: OK\n", num_of_test);
            return 1;
        }
    }

    // TODO: Add imaginary value display (if imaginary is null dont print it)
    printf("TEST №%d FAILED: x1 = %lf, x2 = %lf, num_of_roots = %d\n"
           "      EXPECTED: x1_ref = %lf, x2_ref = %lf, num_of_roots_ref = %d\n",\
         num_of_test, creal(x1), creal(x2), num_of_roots, creal(x1_ref), creal(x2_ref), num_of_roots_ref);
    return 0;

}


