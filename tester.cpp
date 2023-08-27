#include <stdio.h>

#include "qe_solver_tester.h"
#include "colors.h"
#include "make_logs.h"
#include "strings.h"

#include <complex.h>

static void show_separator();

int main(int argc, char **argv)
{
    show_separator();

    if (argc < 3)
    {
        printf(COLOR_BLUE "HOW TO USE: " COLOR_RESET "tester.cpp <filename>");
        return 1;
    }

    if (argc >= 3 && strcmp(argv[2], "-log") == 0) // By default log to console
    {
        current_log_level = LOG_LVL_MESSAGE;

        if (argc >= 4)
        {
            if (strcmp(argv[3], "disable") == 0)
                current_log_level = LOG_LVL_DISABLED;

            else if (strcmp(argv[3], "message") == 0)
                current_log_level = LOG_LVL_MESSAGE;

            else if (strcmp(argv[3], "error") == 0)
                current_log_level = LOG_LVL_ERROR;
            if (argc >= 5)
            {
                if (strcmp(argv[4], "-console") == 0)
                    current_log_mode = TO_CONSOLE;

                else if (strcmp(argv[4], "-file") == 0)
                    current_log_mode = TO_FILE;

                if (argc >= 6)
                    strcpy(log_file_name, argv[5]);
            }
        }

        clear_log_file();
    }

    test_all_equations(argv[1]);
    show_separator();

    return 0;
}

static void show_separator(void)
{
    printf(COLOR_WHITE "=======================================================================\n" COLOR_RESET);
}
