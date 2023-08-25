#include <stdio.h>
#include <complex.h>
#include <assert.h>
#include <string.h>
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

    int n = get_file_size(file_ptr)/(char)sizeof(char);

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

_Complex double write_complex_value(double real, double imag);

_Complex double write_complex_value(double real, double imag)
{
    if(std::isnan(real) && std::isnan(imag))
        return NAN;
    else if(std::isnan(real) || std::isnan(imag))
    {
        real = (std::isnan(real)) ? 0 : real;
        imag = (std::isnan(imag)) ? 0 : imag;
    }

    return real + I*imag;
}


bool read_complex_number(FILE *file_ptr, const char *format, _Complex double *a);
bool read_complex_number(FILE *file_ptr, const char *format, _Complex double *a)
{
    double a_real = NAN, a_imag = NAN;
    if (fscanf(file_ptr, format, &a_real, &a_imag) != get_expected_args_amount(format))
    {
        return false;
    }

    *a = write_complex_value(a_real, a_imag);

    return true;
}

const int MAX_LINE_LEN = 256;

void read_reference_values(struct test_values_data *test_values, FILE *file_ptr)
{
    assert(file_ptr);
    assert(test_values);

    char line[MAX_LINE_LEN] = {};
    fgets(line, MAX_LINE_LEN, file_ptr);

    const int values_count = 7;
    enum value_id { a, b, c, x1_real, x1_imag, x2_real, x2_imag };
    double values[values_count] = {};
    char *ptr = NULL;

    ptr = strtok(line, " ");
    for (int i = 0; i < values_count; i++)
    {
        values[i] = (strcmp(ptr,"NAN") == 0) ? NAN : strtod(ptr, NULL);
        ptr = strtok(NULL, " ");
    }

    test_values->a = values[a];
    test_values->b = values[b];
    test_values->c = values[c];
    test_values->x1_ref = write_complex_value(values[x1_real], values[x1_imag]);
    test_values->x2_ref = write_complex_value(values[x2_real], values[x2_imag]);
    test_values->num_of_roots_ref = (strcmp(ptr,"NAN") == 0) ? NAN : atoi(ptr);

}

void test_all_equations(const char *filename)
{
    int number_of_succeed = 0, number_of_failed = 0;
    FILE *file_ptr = NULL;

    file_ptr = fopen(filename, "rt");
    assert(file_ptr);

    int n = count_lines(file_ptr);
    struct test_values_data test_values;

    fseek(file_ptr, 0, SEEK_SET);


    for (int i = 0, test_number = 0; i < n; i++)
    {
        read_reference_values(&test_values, file_ptr);
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
        if (compare_complex_doubles(x1, x1_ref) && compare_complex_doubles(x2, x2_ref))
        {
            printf("TEST ¹%d: OK!", num_of_test);
        }
    }

    print_failed_values(num_of_test, x1, x2, num_of_roots);
    print_expected_values(x1_ref, x2_ref, num_of_roots_ref);
    return 0;

}

void print_failed_values(int num_of_test, _Complex double x1, _Complex double x2, int num_of_roots)
{
    printf("TEST ¹%d FAILED: x1 = %s, x2 = %s, num_of_roots = %d\n", num_of_test, complex_number_to_str(x1), complex_number_to_str(x2), num_of_roots);
}

void print_expected_values(_Complex double x1_ref, _Complex double x2_ref, int num_of_roots_ref)
{
    printf("EXPECTED: x1 = %s, x2 = %s, num_of_roots_ref = %d\n", complex_number_to_str(x1_ref), complex_number_to_str(x2_ref), num_of_roots_ref);
}

