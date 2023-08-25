#include <stdio.h>

#include "qe_solver_tester.h"
#include "colors.h"

#include <complex.h>

static void show_separator();

int main(int argc, char **argv)
{
    show_separator();

    if (argc != 2)
    {
        printf(COLOR_BLUE "HOW TO USE: " COLOR_RESET "tester.cpp <filename>");
        return 1;
    }

    test_all_equations(argv[1]);
    show_separator();

    return 0;
}

static void show_separator(void)
{
    printf(COLOR_WHITE "=======================================================================\n" COLOR_RESET);
}
