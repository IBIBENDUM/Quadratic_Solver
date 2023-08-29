#include <stdio.h>
#include <unistd.h>

#include "qe_solver_tester.h"
#include "colors.h"
#include "make_logs.h"
#include "strings.h"

#include <complex.h>

static void show_separator();

int main(int argc, char **argv)
{
    show_separator();

    int arg = 0;

    while ( (arg = getopt(argc, argv, "lo::f:")) != -1)
    {
        switch(arg)
        {
            case 'l':
            {
                if (optarg)
                {
                    if (strcmp(optarg, "disable") == 0)
                        current_log_level = LOG_LVL_DISABLED;

                    else if (strcmp(optarg, "message") == 0)
                        current_log_level = LOG_LVL_MESSAGE;

                    else if (strcmp(optarg, "error") == 0)
                        current_log_level = LOG_LVL_ERROR;
                }

                else
                    current_log_level = LOG_LVL_MESSAGE;

                clear_log_file();
                break;
            }

            case 'o':
            {
                if (optarg)
                {
                    if (strcmp(optarg, "console") == 0)
                        current_log_mode = TO_CONSOLE;

                    else if (strcmp(optarg, "file") == 0)
                        current_log_mode = TO_FILE;
                }
                break;
            }

            case 'f':
            {
                current_log_mode = TO_FILE;
                log_file_name = optarg;
                break;
            }

            case '?':
            {
                printf(COLOR_RED);
                PRINT_WITH_ANIM(DELAY_FAST, "Error found\n");
                printf(COLOR_RESET);
                return 1;
            }

            default:
                break;
        }
    }

    test_all_equations(argv[1]);
    show_separator();

    return 0;
}

static void show_separator(void)
{
    printf(COLOR_WHITE "=======================================================================\n" COLOR_RESET);
}
