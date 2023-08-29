#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "qe_solver_interactive.h"
#include "comparators.h"
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


static int get_expected_args_amount(const char *format)
{
    MY_ASSERT(format);
    int expected_args_amount = 0;
    for (unsigned int i = 0; format[i]; i++)
    {
        if(format[i] == '%')
            expected_args_amount++;
    }
    return expected_args_amount;
}


bool ask_coefs(double *a_ptr, double *b_ptr, double *c_ptr)
{

    PRINT_WITH_ANIM(DELAY_FAST, "Enter the coefficients separated by a space:\n");
//    printf("Enter the coefficients separated by a space:\n");

    if(!read_coefs(a_ptr, b_ptr, c_ptr))
    {
        printf(COLOR_RED);
        PRINT_WITH_ANIM(DELAY_FAST, "Error at coefficients input\n");
        printf(COLOR_RESET);
//        printf(COLOR_RED "Error at coefficients input\n" COLOR_RESET);
        skip_line();
        return false;
    }

    skip_line();
    return true;

}

bool ask_for_continue()
{
//    printf("Do you want to continue? (Y for continue, something else for exit)\n");
    PRINT_WITH_ANIM(DELAY_FAST, "Do you want to continue? (Y for continue, something else for exit)\n");

    skip_space_symbols();
    int ch = getchar();
    skip_line();

    return (tolower(ch) == 'y');
}

int read_coefs(double *a_ptr, double *b_ptr, double *c_ptr)
{
    MY_ASSERT(a_ptr);
    MY_ASSERT(b_ptr);
    MY_ASSERT(c_ptr);

    MY_ASSERT(a_ptr != b_ptr);
    MY_ASSERT(a_ptr != c_ptr);
    MY_ASSERT(b_ptr != c_ptr);

    const char format[] = "%lg %lg %lg";

    return(scanf(format, a_ptr, b_ptr, c_ptr) == get_expected_args_amount(format));

}
