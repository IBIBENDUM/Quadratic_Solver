#include <stdio.h>
#include <unistd.h>
#include <strings.h>

#include "qe_solver_tester.h"
#include "colors.h"
#include "make_logs.h"
#include "print_with_anim.h"

static void print_help();
static bool handle_cmd_args(int argc, char **argv);
static void show_separator();

static const char *test_file_name = "tests.txt";

int main(int argc, char **argv)
{

    if (handle_cmd_args(argc, argv))
        return 1;

    show_separator();
    test_all_equations(test_file_name);
    show_separator();

    return 0;
}


static bool handle_cmd_args(int argc, char **argv)
{
    int arg = 0;

    while ( (arg = getopt(argc, argv, "l:o:f:t:h")) != -1)
    {
        switch(arg)
        {
            case 'l': {
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

            case 'o': {
                if (optarg)
                {
                    if (strcmp(optarg, "console") == 0)
                        current_log_mode = TO_CONSOLE;

                    else if (strcmp(optarg, "file") == 0)
                        current_log_mode = TO_FILE;

                    else
                    {
                        print_help();

                        return 1;
                    }

                }
                break;
            }

            case 'f': {
                current_log_mode = TO_FILE;
                log_file_name = optarg;
                break;
            }

            case 't': {
                if (optarg)
                    test_file_name = optarg;
                break;
            }

            case 'h': {
                print_help();

                return 1;
            }

            default: {            // I know about '?'
                print_with_anim(COLOR_RED,"Wrong option found\n");
                print_help();

                return 1;
            }
        }
    }

    return 0;
}

static void print_help()
{
    show_separator();
    printf("OPTIONS:\n");
    printf("-h             Display help message\n");
    printf("-t             Choose tests file (requires argument)\n");
    printf("               Default file is ""tests.txt""\n");
    printf("-l             Display logs (by default print message logs to console)\n");
    printf("-o             Choose output (requires argument)\n");
    printf("-f             Choose output file (requires argument)\n");
    printf("\n");
    printf("EXAMPLES:\n");
    printf("               -t baobab.txt\n");
    printf("               -h disable -h message -h error\n");
    printf("               -o console -o file\n");
    printf("               -f aboba.txt\n");
    show_separator();
}

static void show_separator(void)
{
    printf(COLOR_WHITE "=======================================================================\n" COLOR_RESET);
}
