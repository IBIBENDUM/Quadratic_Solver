#define   TX_COMPILED
#include <TXlib.h>


#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#include "quad_solver_interactive.h"

bool ask_coefs(double *a_ptr, double *b_ptr, double *c_ptr)
{

    printf("������� ������������ ����� ������:\n");

    if(read_coefs(a_ptr, b_ptr, c_ptr) != 3)
    {
        printf("������ ��� ����� �������������\n");
        return false;
    }
    return true;

}
bool ask_for_continue()
{
    int ch;

    printf("������� ����������? (Y ��� �����������, ���-�� ������ ��� ������)\n");

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
