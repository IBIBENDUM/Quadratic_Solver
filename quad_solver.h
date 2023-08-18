#ifndef QUAD_SOLVER_H
#define QUAD_SOLVER_H

union root
{
    double real_n;
    double _Complex complex_n;
};

// ��������:    ��������� �������� �������������
// �����������: a,b,c �������� ��������� ��������
int get_coefs(double * a, double * b, double * c);

// ��������:    ���������� �������������
// �����������: ������� ���������� �������� �������������
double discr_solver(const double a, const double b, const double c);

// ��������:    �������� ������������� �� ������������
// �����������: ������� ���������� true, ���� ������������
//              ������ ��������, � false � ��������� ������
bool validate_coefs(const double a,const double b, const double c, const int count);

// ��������:    ���������� �������� ������
// �����������: x1 � x2 �������� �������� ������,
//              ������� ���������� true, ���� ����� �����������,
//              � false � ��������� ������
bool quadratic_solver(const double a, const double b, const double d,union root *x1,union root *x2);

// ��������:    ����� �������� �� �����
void print_roots(const union root x1,const union root x2, const bool is_complex);

#endif
