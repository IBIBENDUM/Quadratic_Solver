#define   TX_COMPILED
#include <TXlib.h>

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>

#include "quad_solver.h"

#define TOLERANCE 0.01

#define ISEQUAL(X, Y) ((fabs((X)-(Y)) < TOLERANCE)? 1:0)

int get_coefs(double * a_ptr, double * b_ptr, double *c_ptr)
{
    int count;
    count = scanf("%lf %lf %lf", a_ptr, b_ptr, c_ptr);

    while (getchar() != '\n') continue; // ������� ������

    return count;
}

// ���������� �������� �������������
double discr_solver(const double a, const double b, const double c)
{
    return (b*b - 4*a*c);
}

// ���������� true, ���� ������������ ������ ��������
bool validate_coefs(const double a,const double b,const double c, const int count)
{
    if(count != 3)                      // �������� �� ������������ �����
    {
        printf("������ ��� ������ �������������\n");
        return false;
    }

    if( (ISEQUAL(a,0)) ||
        (ISEQUAL(b,0) && ISEQUAL(c,0))) // �������� �� �������� ��-���
    {
        printf("��� ��������� ��������\n");
        return false;
    }

    if((ISEQUAL(a,0) && ISEQUAL(b,0) && !ISEQUAL(c,0))) // �������� �� ������� �������
    {
        printf("��� ��������� �� ����� �������\n");
        return false;
    }

    if((ISEQUAL(a,0) && ISEQUAL(b,0) && ISEQUAL(c,0))) // ��� ������ ����� ����
    {
        printf("� ����������� R\n");
        return false;
    }

    return true;
}


// ���������� true, ���� ������� �����������
bool quadratic_solver(const double a,const double b,const double d,union root *x1,union root *x2)
{
    const double x_const = -b/(a*2.0);
    const double d_sqrt_half = sqrt(fabs(d))/(a*2.0);

    if (d>0 || ISEQUAL(d,0))  // ���� D>=0
    {
        x1->real_n = x2->real_n = x_const;
        x1->real_n -= d_sqrt_half;
        x2->real_n += d_sqrt_half;

        return false;
    }
    else
    {
        x1->complex_n = x2->complex_n = x_const;
        x1->complex_n -= I*d_sqrt_half;
        x2->complex_n += I*d_sqrt_half;

        return true;
    }
}

// ������� �������� ������ �� �����
void print_roots(const union root x1,const union root x2, const bool is_complex)
{
    if (!is_complex)
        printf("x1 = %.2lf, x2 = %.2lf\n",x1.real_n, x2.real_n);
    else
        if(!ISEQUAL(creal(x1.complex_n),0)) // �������� �������������� �����, ������ ���� ��� �� ����� 0
            printf("x1 = %.2lf%+.2lfi, x2 = %.2lf%+.2lfi\n",creal(x1.complex_n), cimag(x1.complex_n),
                                                            creal(x2.complex_n),cimag(x2.complex_n));
        else
            printf("x1 = %+.2lfi, x2 = %+.2lfi\n", cimag(x1.complex_n), cimag(x2.complex_n));

}
