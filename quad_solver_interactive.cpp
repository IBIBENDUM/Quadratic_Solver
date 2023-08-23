#define   TX_COMPILED
#include <TXlib.h>


#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#include "quad_solver_interactive.h"

bool ask_coefs(double *a_ptr, double *b_ptr, double *c_ptr)
{

    printf("Введите коэффициенты через пробел:\n");

    if(read_coefs(a_ptr, b_ptr, c_ptr) != 3)
    {
        printf("Ошибка при вводе коэффициентов\n");
        return false;
    }
    return true;

}
bool ask_for_continue()
{
    int ch;

    printf("Желаете продолжить? (Y для продолжения, что-то другое для выхода)\n");

    while (isspace(ch=getchar()))
        continue;

    skip_line();

    return (toupper(ch) == 'Y');
}


void skip_line()
{
    int ch;
    while ( ((ch=getchar()) != '\n') && (ch != EOF) ) continue;
}

int read_coefs(double *a_ptr, double *b_ptr, double *c_ptr)
{
    assert(a_ptr);
    assert(b_ptr);
    assert(c_ptr);

    assert(!(a_ptr == b_ptr));
    assert(!(a_ptr == c_ptr));
    assert(!(b_ptr == c_ptr));

    int count = scanf("%lf %lf %lf", a_ptr, b_ptr, c_ptr);

    skip_line();

    return count;
}
