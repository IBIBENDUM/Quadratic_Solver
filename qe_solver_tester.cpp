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
    assert(size != -1);
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

    assert(prev_pos != -1);
    assert(!fseek(file_ptr, 0, SEEK_SET));

    fread(symbols, sizeof(char), n, file_ptr);// TODO: correctness

    int lines = 1;
    for(int i = 0; i < n; i++)
    {
        if(symbols[i] == '\n' || symbols[i] == 0)
            lines++;
    }

    assert(!fseek(file_ptr, prev_pos, SEEK_SET));

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

bool read_reference_values(struct test_values_data *tv_ptr, FILE *file_ptr)
{
    assert(file_ptr);
    assert(tv_ptr);

    char line[MAX_LINE_LEN] = {};
    fgets(line, MAX_LINE_LEN, file_ptr);

    const size_t values_amount = 8;
    double values[values_amount - 1] = {};              // Without num_of_roots (because it's int)

    if (values_amount == count_values_in_line(line))
    {
        char *ptr = line;
        for (size_t i = 0; i < values_amount - 1; i++)       // num_of_roots_ref handle separately
        {
            if ((ptr == NULL) || (strcmp(ptr, "//") == 0))  // Check if line ended too early or for comment line
                return false;
            values[i] = (strcmp(ptr, "NAN") == 0) ? NAN : strtod_with_negative(ptr, NULL);  // if arg isn't value return 0
            ptr += strlen(ptr) + 1;  // Skip \0
            ptr += strspn(ptr, " "); // Skip spaces
        }

        *tv_ptr = test_values_data
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
//    assert(file_ptr);
    if (!file_ptr)
        RETURN_WITH_STRERROR();

    int n = count_lines(file_ptr);
    struct test_values_data test_values = {};

    if (fseek(file_ptr, 0, SEEK_SET))
        RETURN_WITH_STRERROR();

    int number_of_succeed = 0, test_number = 0;

    for (int i = 0; i < n-1; i++)                                           // n != test_number
    {                                                                       // n increments every line
        if(read_reference_values(&test_values, file_ptr))                  // test_number increments only if line consist args
        {
            test_number++;
            if(test_one_equation(test_number, &test_values))
                number_of_succeed++;
        }
    }

    int number_of_failed = test_number - number_of_succeed;
    printf(PAINT_TEXT(COLOR_GREEN, "Succeed: %d " COLOR_RED "Failed: %d\n"), number_of_succeed, number_of_failed);

    fclose(file_ptr);

}



bool test_one_equation(const int num_of_test, struct test_values_data *tv_ptr)
{
    assert(tv_ptr);

    double _Complex x1 = NAN, x2 = NAN;
    int num_of_roots = NAN;
    solve_quadratic_equation(tv_ptr->a, tv_ptr->b, tv_ptr->c, &x1, &x2, &num_of_roots);

    sort_complex(&tv_ptr->x1_ref,&tv_ptr->x2_ref);

    if (num_of_roots == tv_ptr->num_of_roots_ref)
    {
        if (compare_complex_doubles(x1, tv_ptr->x1_ref) == 0 && compare_complex_doubles(x2, tv_ptr->x2_ref) == 0)
        {
            char x1_str[COMPLEX_STR_LEN] = "";
            complex_number_to_str(x1_str, x1);

            char x2_str[COMPLEX_STR_LEN] = "";
            complex_number_to_str(x2_str, x2);

            LOG(LOG_LVL_MESSAGE, "TEST N%d SUCCEED: x1 = %s, x2 = %s, num_of_roots = %d",
            num_of_test, x1_str, x2_str, num_of_roots);
            printf(PAINT_TEXT(COLOR_GREEN, "TEST N%d: OK!\n"), num_of_test);

            return true;
        }
    }

    print_failed_values(num_of_test, x1, x2, num_of_roots);
    print_expected_values(tv_ptr->x1_ref, tv_ptr->x2_ref, tv_ptr->num_of_roots_ref);

    return false;

}

void print_failed_values(const int num_of_test, const _Complex double x1, const _Complex double x2, const int num_of_roots)
{

    char x1_str[COMPLEX_STR_LEN] = "";
    complex_number_to_str(x1_str, x1);

    char x2_str[COMPLEX_STR_LEN] = "";
    complex_number_to_str(x2_str, x2);

    printf(COLOR_RED "TEST N%d FAILED: " COLOR_RESET "x1 = %s, x2 = %s, num_of_roots = %d\n",
           num_of_test, x1_str, x2_str, num_of_roots);
}

void print_expected_values(const _Complex double x1_ref, const _Complex double x2_ref, const int num_of_roots_ref)
{
    char x1_ref_str[COMPLEX_STR_LEN] = "";
    complex_number_to_str(x1_ref_str, x1_ref);

    char x2_ref_str[COMPLEX_STR_LEN] = "";
    complex_number_to_str(x2_ref_str, x2_ref);

    printf(COLOR_BLUE "EXPECTED: " COLOR_RESET "x1 = %s, x2 = %s, num_of_roots_ref = %d\n",
           x1_ref_str, x2_ref_str, num_of_roots_ref);
}

