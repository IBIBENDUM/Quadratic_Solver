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
    printf("Эта программа решает квадратные уравнения!\nVersion: ***\n");
    while(true)
    {
        show_separator();
        printf("Введите коэффициенты через пробел:\n");
        double a,b,c;
        a = b = c = 0;

        if(get_coefs(&a,&b,&c) != 3)
        {
            printf("Ошибка при вводе коэффициентов");
            if(!ask_for_continue()) break;
            continue;
        }

        double _Complex x1,x2;
        x1 = x2 = 0;
        int numOfRoots = 0;
        numOfRoots = quadratic_solver(a,b,c,&x1,&x2);

        print_roots(x1,x2, numOfRoots);

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
