/* компилировать вместе с quad_solver.cpp и TXLib.cpp*/
#define   TX_COMPILED
#include <TXlib.h>

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "quad_solver.h"

bool ask_for_continue(void);

void show_separator(void);
void clean_buffer(void);
void show_kitty(void);

int main(void)
{
    int count;
    double a,b,c,d;
    bool is_complex;
    union root x1,x2;

    while(true)
    {
        show_separator();
        printf("Введите коэффициенты через пробел:\n");

        count = get_coefs(&a,&b,&c);

        if(!validate_coefs(a,b,c, count))
        {
            if(!ask_for_continue()) break;
            continue;
        }

        d = discr_solver(a,b,c);
        is_complex = quadratic_solver(a,b,d,&x1,&x2);

        print_roots(x1,x2,is_complex);

        if(!ask_for_continue()) break;
    }

    show_separator();
    show_kitty();
    printf("А всё!");

    return 0;
}

void show_separator(void)
{
    printf("=======================================================================\n");
}

bool ask_for_continue(void)
{
    int ch;

    printf("Желаете продолжить? (Y для продолжения, что-то другое для выхода)\n");

    while (isspace(ch=getchar())) continue;
    clean_buffer();

    if (toupper(ch) == 'Y')
        return true;

    return false;
}

void clean_buffer(void)
{
    int ch;
    while ( ((ch=getchar()) != '\n') && (ch != EOF)) continue;
}

void show_kitty(void)
{
    printf(" /\\_/\\ \n( o.o )\n > ^ <\n");
}
