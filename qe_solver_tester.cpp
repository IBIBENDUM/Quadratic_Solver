#include <stdio.h>
#include <complex.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#include "qe_solver_tester.h"
#include "qe_solver.h"
#include "comparators.h"
#include "format_complex.h"
#include "colors.h"
#include "make_logs.h"


static int get_file_size(FILE *file_ptr);

static int count_lines(FILE *file_ptr);

static int count_values_in_line(char *line);

static double strtod_with_negative(char *ptr, char **endptr);



static int get_file_size(FILE *file_ptr) // TODO: useful, extract in a separate file
{
    assert(file_ptr);

    size_t prev_pos = ftell(file_ptr);

    assert(!fseek(file_ptr, 0, SEEK_END));
    int size = ftell(file_ptr);
    assert(size > -1);
    assert(!fseek(file_ptr, prev_pos, SEEK_SET));

    LOG(LOG_LVL_MESSAGE, "File %d have %d symbols", fileno(file_ptr), size);

    return size;
}

static int count_lines(FILE *file_ptr) // TODO: useful, extract in a separate file
{
    assert(file_ptr);

    int n = get_file_size(file_ptr);

    const int BUF_SIZE = 256;
    int symbols[BUF_SIZE] = {};

    int prev_pos = ftell(file_ptr);

    assert(!fseek(file_ptr, 0, SEEK_SET)); // TODO: ...

    fread(symbols, sizeof(char), n, file_ptr);// TODO: correctness

    int lines = 1;
    for(int i = 0; i < n; i++)
    {
        if(symbols[i] == '\n' || symbols[i] == 0)
            lines++;
    }

    assert(!fseek(file_ptr, prev_pos, SEEK_SET)); // TODO: what if assert gets disabled?

    LOG(LOG_LVL_MESSAGE, "File have %d lines", lines);

    return lines;
}

static int count_values_in_line(char *line)
{
    int args_count = 0;
    char *ptr = strtok(line, " ");
    while (ptr != NULL)
    {
        if(strcmp(ptr, "//") == 0)
            break;
        args_count++;
        ptr = strtok(NULL, " ");
    }

    return args_count;
}

static double strtod_with_negative(char *ptr, char **endptr)
{
    if (ptr[0] == '-')
    {
        return -strtod(ptr+1, endptr);
    }

    return strtod(ptr, endptr);
}

bool read_reference_values(struct test_values_data *test_values, FILE *file_ptr)
{
    assert(file_ptr);       // TODO: too complex, can you make it simpler?
    assert(test_values);

    char line[MAX_LINE_LEN] = {};
    fgets(line, MAX_LINE_LEN, file_ptr);

    const int values_amount = 8;
    double values[values_amount - 1] = {};  // Without num_of_roots (because it's int)

    if (values_amount == count_values_in_line(line))
    {
        char *ptr = line;
        for (int i = 0; i < values_amount - 1; i++)       // num_of_roots_ref handle separately
        {
            if ((ptr == NULL) || (strcmp(ptr,"//") == 0))  // Check if line ended too early or for comment line
                return false;

            // TODO: doesn't strtod accept NANs?
            values[i] = (strcmp(ptr,"NAN") == 0) ? NAN : strtod_with_negative(ptr, NULL);  // if arg isn't value return 0
            ptr += strlen(ptr) + 1;  // Skip \0
            ptr += strspn(ptr, " "); // Skip spaces
        }

        *test_values = test_values_data // TODO: formatting
        {values[a], values[b], values[c],
        complex_from_parts(values[x1_real], values[x1_imag]),
        complex_from_parts(values[x2_real], values[x2_imag]),
        (strcmp(ptr,"NAN") == 0) ? 0 : strtol(ptr, NULL, 10)};

        return true;
    }

    return false;

}

void test_all_equations(const char *filename)
{
    assert(filename);
    FILE *file_ptr = fopen(filename, "rt"); // RT RT RT RT RT
    assert(file_ptr);

    int n = count_lines(file_ptr);
    struct test_values_data test_values = {};

    assert(!fseek(file_ptr, 0, SEEK_SET));

    int number_of_succeed = 0, test_number = 0;

    for (int i = 0; i < n-1; i++)                                           // n != test_number
    {                                                                       // n increments every line
        if(!read_reference_values(&test_values, file_ptr))                  // test_number increments only if line consist args
            continue;
        test_number++;
        if(test_one_equation(test_number, &test_values))
            number_of_succeed += 1;
    }

    int number_of_failed = test_number - number_of_succeed;
    printf(PAINT_TEXT(COLOR_GREEN, "Succeed: %d " COLOR_RED "Failed: %d\n"), number_of_succeed, number_of_failed);

    fclose(file_ptr);

}


bool test_one_equation(const int num_of_test, struct test_values_data *tv)
{
    assert(tv);

    double _Complex x1 = NAN, x2 = NAN;
    int num_of_roots = NAN;
    solve_quadratic_equation(tv->a, tv->b, tv->c, &x1, &x2, &num_of_roots);

    sort_complex(&tv->x1_ref,&tv->x2_ref);

    if (num_of_roots == tv->num_of_roots_ref)
    {
        if (compare_complex_doubles(x1, tv->x1_ref) == 0 && compare_complex_doubles(x2, tv->x2_ref) == 0)
        {
            LOG(LOG_LVL_MESSAGE, "TEST N%d SUCCEED: x1 = %s, x2 = %s, num_of_roots = %d",
            num_of_test, complex_number_to_str(x1), complex_number_to_str(x2), num_of_roots);
            printf(COLOR_GREEN "TEST N%d: OK!\n" COLOR_RESET, num_of_test);

            return true;
        }
    }

    print_failed_values(num_of_test, x1, x2, num_of_roots);
    print_expected_values(tv->x1_ref, tv->x2_ref, tv->num_of_roots_ref);

    return false;

}

void print_failed_values(const int num_of_test, const _Complex double x1, const _Complex double x2, const int num_of_roots)
{
    printf(COLOR_RED "TEST N%d FAILED: " COLOR_RESET "x1 = %s, x2 = %s, num_of_roots = %d\n",
           num_of_test, complex_number_to_str(x1), complex_number_to_str(x2), num_of_roots);
}

void print_expected_values(const _Complex double x1_ref, const _Complex double x2_ref, const int num_of_roots_ref)
{
    printf(COLOR_BLUE "EXPECTED: " COLOR_RESET "x1 = %s, x2 = %s, num_of_roots_ref = %d\n",
           complex_number_to_str(x1_ref), complex_number_to_str(x2_ref), num_of_roots_ref);
}

