#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "quad_solver.h"
#include "quadratka_test.h"
#include "comparators.h"
#include "quadratka_test.h"
#include "colors.h"

void show_separator();
void show_kitty();

int main()
{
    test_all_equations("tests.bin");
    return 0;
}

