/* компилировать вместе с quad_solver.cpp и TXLib.cpp и quad_solver_interactive*/
#define   TX_COMPILED
#include <TXlib.h>

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "quad_solver.h"
#include "quad_solver_interactive.h"
#include "quadratka_test.h"

void show_separator();
void show_kitty();

int main(int argc, char **argv)
{
    printf("Эта программа решает квадратные уравнения!\nVersion: 1.2\n");
    while(true)
    {
        show_separator();
        double a = NAN, b = NAN, c = NAN;

        if (argc == 3 && !strcmp(argv[1],"--test"))
        {
            test_all_equations(argv[2]);
            break;
        }
        else
        {
            if(ask_coefs(&a,&b,&c))
            {
                double _Complex x1 = NAN, x2 = NAN;
                int num_of_roots = 0;

                if(solve_quadratic_equation(a, b, c, &x1, &x2, &num_of_roots))
                {
                    print_roots(x1, x2, num_of_roots);
                }
            }

            if(!ask_for_continue()) break;
        }

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
