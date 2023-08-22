#ifndef QUAD_SOLVER_H
#define QUAD_SOLVER_H


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
//              ������� ���������� ���������� ������
int quadratic_solver(const double a, const double b, const double c, double _Complex *x1,double _Complex *x2);

// ��������:    ���������� �������� ����� ��������� ���������
// �����������: x1 �������� �������� �����
void linear_solver(const double b, const double c, double _Complex *x1);

// ��������:    ����� �������� �� �����
void print_roots(const double _Complex x1, const double _Complex x2, int n);

#endif
