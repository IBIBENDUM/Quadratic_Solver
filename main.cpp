
/* компилировать вместе с quad_solver.cpp и TXLib.cpp и quad_solver_interactive*/
#define   TX_COMPILED
#include <TXlib.h>

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "quad_solver.h"
#include "quad_solver_interactive.h"

void show_separator();
void show_kitty();

int main(void)
{
    printf("Эта программа решает квадратные уравнения!\nVersion: 1.2\n");
    while(true)
    {
        double a = NAN, b = NAN, c = NAN;
        show_separator();
        if(ask_coefs(&a,&b,&c))
        {
            double _Complex x1 = NAN, x2 = NAN;
            int numOfRoots = NAN;

            if(solve_quadratic_equation(a, b, c, &x1, &x2, &numOfRoots))
            {
                print_roots(x1, x2, numOfRoots);
            }
        }
        if(!ask_for_continue()) break;
    }

    show_separator();
    show_kitty();
    printf("А всё!\n");

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
