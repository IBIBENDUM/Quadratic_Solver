#define   TX_COMPILED
#include <TXlib.h>

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>

#include "quad_solver.h"

#define PRECISION 0.01

#define EQUALS_ZERO(X) ((fabs((X)) < PRECISION)? 1:0)
#define LARGER_ZERO(X) ((fabs((X)) > PRECISION)? 1:0)

int get_coefs(double * a_ptr, double * b_ptr, double *c_ptr)
{
    int count;
    count = scanf("%lf %lf %lf", a_ptr, b_ptr, c_ptr);

    while (getchar() != '\n') continue; // Очистка буфера

    return count;
}

// Возвращает значение дискриминанта
double discr_solver(const double a, const double b, const double c)
{
    return (b*b - 4*a*c);
}

void linear_solver(const double b, const double c, double _Complex *x1)
{
    *x1 = -b/c;
}


// Возвращает количество корней
int quadratic_solver(const double a,const double b,const double c,double _Complex *x1,double _Complex *x2)
{
    if(EQUALS_ZERO(a)) // Линейное уравнение
    {
        linear_solver(b,c,x1);
        return 1;
    }

    if(!EQUALS_ZERO(a) && EQUALS_ZERO(b) && EQUALS_ZERO(c)) // Линейное уравнение
    {
        *x1 = 0;
        return 1;
    }

    if(EQUALS_ZERO(a) && EQUALS_ZERO(b) && EQUALS_ZERO(c)) // Корень принадлежит R
    {
        return -1;
    }

    if((EQUALS_ZERO(a) && EQUALS_ZERO(b) && !EQUALS_ZERO(c))) // Нет корней
    {
        return 0;
    }

    double d = 0;
    d = discr_solver(a,b,c);

    const double d_sqrt_half = sqrt(fabs(d))/(a*2.0);

    const double x_const = -b/(a*2.0);
    *x1 = *x2 = x_const;

    if (LARGER_ZERO(d))
    {

        *x1 -= d_sqrt_half;
        *x2 += d_sqrt_half;
        return 2;
    }
    else if (EQUALS_ZERO(d))
    {
        *x1 = 0;
        return 1;
    }
    else
    {
        *x1 -= I*d_sqrt_half;
        *x2 += I*d_sqrt_half;
        return 2;
    }
}

// Выводит значения корней на экран
void print_roots(const double _Complex x1, const double _Complex x2, int n)
{
    switch(n)
    {
        case -1: printf("X принадлежит R");
                 break;

        case 0: printf("Нет корней");
                break;

        case 1: printf("x = %.2lf",creal(x1));
                break;

        case 2: if(EQUALS_ZERO(cimag(x1))) // Если мнимая часть равна нулю, выводить только действительную
                    printf("x1 = %.2lf, x2 = %.2lf", creal(x1), creal(x2));
                else
                    printf("x1 = %.2lf%+.2lfi, x2 = %.2lf%+.2lfi\n",creal(x1), cimag(x1), creal(x2),cimag(x2));
                break;

        default: break;
    }


}
