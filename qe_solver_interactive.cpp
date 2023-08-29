#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>

#include "qe_solver_interactive.h"
#include "make_logs.h"
#include "colors.h"

static void skip_line();
static void skip_space_symbols();
static size_t get_expected_args_amount(const char *format);
static bool read_formated(const char *format, ...);

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

static size_t get_expected_args_amount(const char *format)
{
    MY_ASSERT(format);

    size_t expected_args_amount = 0;
    for (size_t i = 0; format[i]; i++)
    {
        if (format[i] == '%')
            expected_args_amount++;
    }

    return expected_args_amount;
}


bool ask_coefs(double *a_ptr, double *b_ptr, double *c_ptr)
{

    PRINT_WITH_ANIM("Enter the coefficients separated by a space:\n");

    if (read_coefs(a_ptr, b_ptr, c_ptr))
    {
        PRINT_WITH_ANIM(PAINT_TEXT(COLOR_RED, "Error at coefficients input\n"));
        skip_line();

        return true;
    }

    skip_line();

    return false;

}

bool ask_if_continue()
{
    PRINT_WITH_ANIM("Do you want to continue? (Y for continue, something else for exit)\n");

    skip_space_symbols();
    int ch = getchar();
    skip_line();

    return (tolower(ch) == 'y');
}


// TODO: __attribute__((printf))


static bool read_formated(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int n = vscanf(format, args);
    va_end(args);

    return n != get_expected_args_amount(format);
}

int read_coefs(double *a_ptr, double *b_ptr, double *c_ptr)
{
    MY_ASSERT(a_ptr);
    MY_ASSERT(b_ptr);
    MY_ASSERT(c_ptr);

    MY_ASSERT(a_ptr != b_ptr);
    MY_ASSERT(a_ptr != c_ptr);
    MY_ASSERT(b_ptr != c_ptr);

    return read_formated("%lf %lf %lf", a_ptr, b_ptr, c_ptr);
}

#undef SCANF_WITH_CHECKER
