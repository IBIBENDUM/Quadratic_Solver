#ifndef QUAD_SOLVER_H
#define QUAD_SOLVER_H


// ��������:    ���������� �������������
// �����������: ������� ���������� �������� �������������
double calculate_discriminant(const double a, const double b, const double c);

// ��������:    Calculate roots
// �����������: x1 and x2 gets roots values,
//              function returns 1 if coeffs are incorrect,
//              0 if coeffs are correct
bool solve_quadratic_equation(const double a, const double b, const double c, double _Complex *x1, double _Complex *x2, int *NumberOfRoots);

// ��������:    ���������� �������� ����� ��������� ���������
// �����������: x1 �������� �������� �����
void solve_linear_equation(const double b, const double c, double _Complex *x1);

// ��������:    ����� �������� �� �����
void print_roots(const double _Complex x1, const double _Complex x2, int n);

#endif
