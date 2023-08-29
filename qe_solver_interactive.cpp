#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "qe_solver_interactive.h"
#include "comparators.h" // TODO: unused
#include "make_logs.h"
#include "colors.h"

static void skip_line();
static void skip_space_symbols();
static int get_expected_args_amount(const char *format);

static void skip_line()
{
    int ch = 0;
    while ( ((ch=getchar()) != '\n') && (ch != EOF) )
        continue;
}

static void skip_space_symbols()
{
    int ch = 0;
    while (isspace(ch = getchar()))
        continue;
    ungetc(ch, stdin);
}

static int get_expected_args_amount(const char *format) // klass
{
    MY_ASSERT(format);

    int expected_args_amount = 0;
    for (unsigned int i = 0; format[i]; i++)
    {
        if (format[i] == '%')
            expected_args_amount++;
    }

    return expected_args_amount;
}


bool ask_coefs(double *a_ptr, double *b_ptr, double *c_ptr)
{

    PRINT_WITH_ANIM(DELAY_FAST, "Enter the coefficients separated by a space:\n");

    if (read_coefs(a_ptr, b_ptr, c_ptr))
    {
        printf(COLOR_RED);
        PRINT_WITH_ANIM(DELAY_FAST, "Error at coefficients input\n");
        printf(COLOR_RESET);
        skip_line();

        return true;
    }

    skip_line();

    return false;

}

bool ask_for_continue()
{
    PRINT_WITH_ANIM(DELAY_FAST, "Do you want to continue? (Y for continue, something else for exit)\n");

    skip_space_symbols();
    int ch = getchar();
    skip_line();

    return (tolower(ch) == 'y');
}


// TODO: vscanf, thanks to vargs you can make your wrapper

//  1 #include <stdarg.h>
//  2 
//  3 bool read_formatted(const char *format, ...) {
//  4     va_list args;
//  5     va_start(args, format);
//  6 
//  7     vscanf(format, args);
//  8 
//  9     va_end(args);
// 10 }

// TODO: __attribute__((printf))

#define SCANF_WITH_CHECKER(FORMAT, ...)\
({scanf(FORMAT, __VA_ARGS__) == get_expected_args_amount(FORMAT);})


int read_coefs(double *a_ptr, double *b_ptr, double *c_ptr)
{
    MY_ASSERT(a_ptr);
    MY_ASSERT(b_ptr);
    MY_ASSERT(c_ptr);

    MY_ASSERT(a_ptr != b_ptr);
    MY_ASSERT(a_ptr != c_ptr);
    MY_ASSERT(b_ptr != c_ptr);


    return !SCANF_WITH_CHECKER("%lf %lf %lf", a_ptr, b_ptr, c_ptr);
}

#undef SCANF_WITH_CHECKER
