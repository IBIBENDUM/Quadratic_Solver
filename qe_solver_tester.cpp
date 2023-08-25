#include <stdio.h>
#include <complex.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "qe_solver_tester.h"
#include "qe_solver.h"
#include "comparators.h"
#include "format_complex.h"
#include "colors.h"


static int get_file_size(FILE *file_ptr);

static int count_lines(FILE *file_ptr);

static int count_values_in_line(char *line);


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

static int count_values_in_line(char *line)
{
    int args_count = 0;
    char *ptr = strtok(line, " ");     // strtok replace " " with \0
    while (ptr != NULL)
    {
        if(strcmp(ptr, "//") == 0)
            break;
        args_count++;
        ptr = strtok(NULL, " ");
    }

    return args_count;
}

double strtod_with_negative(char *ptr, char **endptr)
{
    if (ptr[0] == '-')
    {
        return -strtod(ptr+1,endptr);
    }
    return strtod(ptr,endptr);

}

bool read_reference_values(struct test_values_data *test_values, FILE *file_ptr)
{
    assert(file_ptr);
    assert(test_values);

    char line[MAX_LINE_LEN] = {};
    fgets(line, MAX_LINE_LEN, file_ptr);

    const int values_amount = 7;// Without num_of_roots (because it's int)
    enum value_id { a, b, c, x1_real, x1_imag, x2_real, x2_imag };
    double values[values_amount] = {};

    if (values_amount + 1 == count_values_in_line(line))
    {
        char *ptr = line;
        for (int i = 0; i < values_amount; i++)
        {
            if ((ptr == NULL) || (strcmp(ptr,"//") == 0))  // Check if line ended too early or for comment line
                return false;
            values[i] = (strcmp(ptr,"NAN") == 0) ? NAN : strtod_with_negative(ptr, NULL);  // if arg isn't value return 0
            ptr += strlen(ptr) + 1;  // Skip \0
            ptr += strspn(ptr, " "); // Skip spaces
        }

        test_values->a = values[a];
        test_values->b = values[b];
        test_values->c = values[c];
        test_values->x1_ref = write_complex_value_to_var(values[x1_real], values[x1_imag]);
        test_values->x2_ref = write_complex_value_to_var(values[x2_real], values[x2_imag]);
        test_values->num_of_roots_ref = (strcmp(ptr,"NAN") == 0) ? NAN : strtol(ptr, NULL, 10);

        return true;
    }

    return false;

}

void test_all_equations(const char *filename)
{
    FILE *file_ptr = fopen(filename, "rt");
    assert(file_ptr);

    int n = count_lines(file_ptr);
    struct test_values_data test_values;

    fseek(file_ptr, 0, SEEK_SET);

    int number_of_succeed = 0, number_of_failed = 0;
    for (int i = 0, test_number = 0; i < n-1; i++)
    {
        if(!read_reference_values(&test_values, file_ptr))
            continue;
        test_number++;
        if(test_one_equation(test_number, &test_values))
        {
            number_of_succeed += 1;
        }
        else
        {
            number_of_failed += 1;
        }
    }

    printf(COLOR_GREEN "Succeed: %d " COLOR_RED "Failed: %d\n" COLOR_RESET, number_of_succeed, number_of_failed);

    fclose(file_ptr);

}


bool test_one_equation(int num_of_test, struct test_values_data *test_values)
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

    sort_complex_by_ascending(&x1_ref,&x2_ref);

    if (num_of_roots == num_of_roots_ref)
    {
        if (compare_complex_doubles(x1, x1_ref, SMALL_PRECISION) == 0 && compare_complex_doubles(x2, x2_ref, SMALL_PRECISION) == 0)
        {
//            printf(COLOR_GREEN "TEST N%d: OK!\n" COLOR_RESET, num_of_test);

            return true;
        }
    }

    print_failed_values(num_of_test, x1, x2, num_of_roots);
    print_expected_values(x1_ref, x2_ref, num_of_roots_ref);
    return false;

}

void print_failed_values(int num_of_test, _Complex double x1, _Complex double x2, int num_of_roots)
{
    printf(COLOR_RED "TEST N%d FAILED: " COLOR_RESET "x1 = %s, x2 = %s, num_of_roots = %d\n",
           num_of_test, complex_number_to_str(x1), complex_number_to_str(x2), num_of_roots);
}

void print_expected_values(_Complex double x1_ref, _Complex double x2_ref, int num_of_roots_ref)
{
    printf(COLOR_BLUE "EXPECTED: " COLOR_RESET "x1 = %s, x2 = %s, num_of_roots_ref = %d\n",
           complex_number_to_str(x1_ref), complex_number_to_str(x2_ref), num_of_roots_ref);
}

