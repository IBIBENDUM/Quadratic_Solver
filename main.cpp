#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

#include "qe_solver.h"
#include "qe_solver_interactive.h"
#include "colors.h"
#include "make_logs.h"
#include "time_utils.h"

static void print_help();
static bool handle_cmd_args(int argc, char **argv);
static void show_separator();
static void show_kitty();



// TODO: projecti dolzhni rabotat' (v tom chisle compilirovats'a)
int main(int argc, char **argv)
{
    if (handle_cmd_args(argc, argv))
        return 1;

    print_with_anim(COLOR_BLUE, "This program solves quadratic equations!\nVersion: 1.47\n");

    while (true)
    {
        show_separator();
        double a = NAN, b = NAN, c = NAN;

        if (!ask_coefs(&a, &b, &c))
        {
            double _Complex x1 = NAN, x2 = NAN;
            int num_of_roots = 0;

            // TODO: what is this negation "!", if we can't solve equation than celebrate?
            if(!solve_quadratic_equation(a, b, c, &x1, &x2, &num_of_roots))
                print_roots(x1, x2, num_of_roots);
        }

        if (!ask_if_continue()) break;

    }

    show_separator();
    show_kitty();

    print_with_anim(COLOR_STD, "That's all!\n");

    return 0;
}

static bool handle_cmd_args(int argc, char **argv)
{
    int arg = 0;

    while ((arg = getopt(argc, argv, "l:o:f:a:h")) != -1)
    {
        switch (arg)
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

                if (clear_log_file())
                    exit(EXIT_FAILURE);
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
                if (current_log_level == LOG_LVL_DISABLED)
                    current_log_level = LOG_LVL_MESSAGE;
                current_log_mode = TO_FILE;
                log_file_name = optarg;
                break;
            }

            case 'a': {
                if (optarg)
                {
                    if (strcmp(optarg, "disabled") == 0)
                        current_anim_mode = ANIM_DISABLED;

                    else if (strcmp(optarg, "enabled") == 0)
                        current_anim_mode = ANIM_ENABLED;

                    else
                    {
                        print_help();

                        return 1;
                    }
                }

                break;
            }

            case 'h': {
                print_help();

                return 1;
            }

            default: {            // I know about '?'
                print_with_anim(COLOR_RED, "Wrong option found\n");
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
    printf("-l             Display logs (by default print message logs to console)\n");
    printf("-o             Choose output (requires argument)\n");
    printf("-f             Choose output file (requires argument)\n");
    printf("\n");
    printf("EXAMPLES:\n");
    printf("               -h disable -h message -h error\n");
    printf("               -o console -o file\n");
    printf("               -f aboba.txt\n");
    show_separator();
}

static void show_separator()
{
    printf(PAINT_TEXT(COLOR_WHITE, "=======================================================================\n"));
}

static void show_kitty()
{
    // TODO: Make this animation BAH: I could not get
    size_t sl = 10;
    printf(COLOR_PURPLE);
    printf("   _                  \n");               Sleep(sl);
    printf("   \\`*-.              \n");              Sleep(sl);
    printf("    )  _`-.             \n");             Sleep(sl);
    printf("   .  : `. .             \n");            Sleep(sl);
    printf("   : _   '  \\            \n");           Sleep(sl);
    printf("   ; *` _.   `*-._         \n");          Sleep(sl);
    printf("   `-.-'          `-.       \n");         Sleep(sl);
    printf("     ;       `       `.      \n");        Sleep(sl);
    printf("     :.       .        \\     \n");       Sleep(sl);
    printf("     . \\  .   :   .-'   .     \n");      Sleep(sl);
    printf("     '  `+.;  ;  '      :       \n");     Sleep(sl);
    printf("     :  '  |    ;       ;-.      \n");    Sleep(sl);
    printf("     ; '   : :`-:     _.`* ;      \n");   Sleep(sl);
    printf("  .*' /  .*' ; .*`- +'  `*'        \n");  Sleep(sl);
    printf("  `*-*   `*-*  `*-*'                \n");
    printf(COLOR_RESET);
}
