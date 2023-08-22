//@



/* ������������� ������ � quad_solver.cpp � TXLib.cpp*/
#define   TX_COMPILED
#include <TXlib.h>

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "quad_solver.h"

bool ask_for_continue(void);
bool ask_coefs(double *a, double *b, double *c); // TODO: better name? Maybe read
void show_separator(void);
void show_kitty(void);

int main(void)
{
    printf("��� ��������� ������ ���������� ���������!\nVersion: ***\n");
    while(true)
    {
        double a = NAN, b = NAN, c = NAN;
        if(!ask_coefs(&a,&b,&c))
        {
            if(!ask_for_continue()) break;  // TODO: think
            continue;
        }

        double _Complex x1 = NAN, x2 = NAN;
        int numOfRoots = NAN;
        if(!solve_quadratic_equation(a, b, c, &x1, &x2, &numOfRoots))
        {
            if(!ask_for_continue()) break;
            continue;
        }

        print_roots(x1, x2, numOfRoots);

        if(!ask_for_continue()) break;
    }

    show_separator();
    show_kitty();
    printf("� ��!\n");

    return 0;
}

void show_separator(void)
{
    printf("=======================================================================\n");
}

void show_kitty(void)
{
    printf(" /\\_/\\ \n( o.o )\n > ^ <\n");  // TODO: make kitty bigger
}
