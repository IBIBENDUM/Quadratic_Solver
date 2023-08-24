#include <stdio.h>
#include <complex.h>
#include <assert.h>
#include <stdlib.h>

#include "quadratka_test.h"
#include "quad_solver.h"
#include "comparators.h"


static int get_file_size(FILE *file_ptr);

static int count_lines(FILE *file_ptr);

int get_file_size(FILE *file_ptr)
{
    assert(file_ptr);

    int prev_pos = ftell(file_ptr);

    fseek(file_ptr, 0, SEEK_END);
    int size = ftell(file_ptr);
    fseek(file_ptr, prev_pos, SEEK_SET);

    return size;
}

int count_lines(FILE *file_ptr)
{
    assert(file_ptr);

    int n = get_file_size(file_ptr)/(int)sizeof(char);

    char *symbols = (char *) malloc(n * sizeof(char));

    fseek(file_ptr, 0, SEEK_SET);

    fread(symbols, sizeof(char), n, file_ptr);

    int lines = 1;
    for(int i = 0; i < n; i++)
    {
        if(symbols[i] == '\n')
            lines++;
    }
    return lines;
}

bool read_complex_number(FILE *file_ptr, const char *format, _Complex double *a);
bool read_complex_number(FILE *file_ptr, const char *format, _Complex double *a)
{
    double a_real = NAN, a_imag = NAN;
    if (fscanf(file_ptr, format, &a_real, &a_imag) != get_expected_args_amount(format))
    {
        printf("JUI");
        return false;
    }

    *a = a_real + a_imag*I;

    return true;
}

bool read_reference_values(struct test_values_data *test_values, FILE *file_ptr)
{
    assert(file_ptr);
    assert(test_values);

    const char coeff_format[] = "%lf %lf %lf";
    if (fscanf(file_ptr, coeff_format, &test_values->a, &test_values->b, &test_values->c) == get_expected_args_amount(coeff_format))
    {
        const char complex_format[] = "%lf %lf";
        if (read_complex_number(file_ptr, complex_format, &test_values->x1_ref) && read_complex_number(file_ptr, complex_format, &test_values->x2_ref))
        {
            const char num_of_roots_format[] = "%d";
            if (fscanf(file_ptr, num_of_roots_format, &test_values->num_of_roots_ref) == get_expected_args_amount(num_of_roots_format))
                return false;
        }
    }
    return true;
}

void test_all_equations(const char *filename)
{
    int number_of_succeed = 0, number_of_failed = 0;
    FILE *file_ptr = NULL;

    file_ptr = fopen(filename, "r");
    assert(file_ptr);

    int n = count_lines(file_ptr);
    struct test_values_data test_values;

    fseek(file_ptr, 0, SEEK_SET);


    for (int i = 0, test_number = 0; i < n; i++)
    {
        if (!read_reference_values(&test_values, file_ptr))
            continue;
        test_number++;

        if(test_one_equation(test_number, &test_values))
            number_of_succeed += 1;
        else
            number_of_failed += 1;
    }

    fclose(file_ptr);

    printf("Succeed: %d Failed: %d\n", number_of_succeed, number_of_failed);
}

int test_one_equation(int num_of_test, struct test_values_data *test_values)
{
    double a = test_values->a;
    double b = test_values->b;
    double c = test_values->c;
    _Complex double x1_ref = test_values->x1_ref;
    _Complex double x2_ref = test_values->x2_ref;
    int num_of_roots_ref = test_values->num_of_roots_ref;

    double _Complex x1 = NAN, x2 = NAN;
    int num_of_roots = NAN;
    solve_quadratic_equation(a, b, c, &x1, &x2, &num_of_roots);

//    sort_complex_by_ascending(&x1_ref,&x2_ref);

    if (num_of_roots == num_of_roots_ref)
    {
        switch(num_of_roots)
        {
            case INFINITE_ROOTS: // TODO: Why you repeat 3 times TEST OK?
            case NO_ROOTS:{
                printf("TEST ¹%d: OK\n", num_of_test); // No need compare values because where is no values
                return 1;
                break;
            }
            case 1:{ // TODO: dealt with this cringe
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
//Learn how to write and use makefiles.

// TODO: make it better.................

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
    {
        if (compare_with_zero(creal(x1)) == 0)
            printf("TEST ¹%d FAILED: x = %+.2lfi, num_of_roots = %d\n",
            num_of_test, cimag(x1), num_of_roots);

        else if (compare_with_zero(creal(x1)) != 0 && compare_with_zero(cimag(x1)) == 0)
                 printf("TEST ¹%d FAILED: x = %.2lf, num_of_roots = %d\n",
                 num_of_test, creal(x1), num_of_roots);

        else if (compare_with_zero(creal(x1)) != 0 && compare_with_zero(cimag(x2)) != 0)
                 printf("TEST ¹%d FAILED: x = %.2lf%+.2lfi, num_of_roots = %d\n",
                 num_of_test, creal(x1), cimag(x1), num_of_roots);
    }

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


