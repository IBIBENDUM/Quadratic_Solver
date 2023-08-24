#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#include "quad_solver_interactive.h"
#include "comparators.h"

static void skip_line();
static void skip_space_symbols();

void skip_line()
{
    int ch = 0;
    while ( ((ch=getchar()) != '\n') && (ch != EOF) )
        continue;
}

bool ask_coefs(double *a_ptr, double *b_ptr, double *c_ptr)
{

    printf("Enter the coefficients separated by a space:\n");

    if(!read_coefs(a_ptr, b_ptr, c_ptr))
    {
        printf("Error at coefficients input\n");
        skip_line();
        return false;
    }
    skip_line();
    return true;

}

bool ask_for_continue()
{
    printf("Do you want to continue? (Y for continue, something else for exit)\n");

    skip_space_symbols();
    int ch = getchar();
    skip_line();

    return (toupper(ch) == 'Y');
}

void skip_space_symbols()
{
    int ch = 0;
    while (isspace(ch = getchar()))
        continue;
    ungetc(ch, stdin);
}


int read_coefs(double *a_ptr, double *b_ptr, double *c_ptr)
{
    assert(a_ptr);
    assert(b_ptr);
    assert(c_ptr);

    assert(a_ptr != b_ptr);
    assert(a_ptr != c_ptr);
    assert(b_ptr != c_ptr);

    char format[] = "%lf %lf %lf";

    return(scanf(format, a_ptr, b_ptr, c_ptr) == get_expected_args_amount(format));

}
