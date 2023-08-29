#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#include "qe_solver.h"
#include "qe_solver_interactive.h"
#include "colors.h"
#include "make_logs.h"

static void show_separator();
static void show_kitty();

// ABOB: remove returns after @return
// use size_t instead of int



int main(int argc, char **argv)
{
    // .\main.exe -l error -o console
    // .\main.exe -l message -o file
    // .\main.exe -l message -o file -f aboba.txt

    //    printf(COLOR_BLUE "This program solves quadratic equations!\nVersion: 1.2\n" COLOR_RESET);

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
                if (current_log_level == LOG_LVL_DISABLED)
                    current_log_level = LOG_LVL_MESSAGE;
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

    printf(COLOR_BLUE);
    PRINT_WITH_ANIM(DELAY_FAST, "This program solves quadratic equations!\nVersion: 1.47\n");
    printf(COLOR_RESET);

    while(true)
    {
        show_separator();
        double a = NAN, b = NAN, c = NAN;

        if(ask_coefs(&a,&b,&c))
        {
            double _Complex x1 = NAN, x2 = NAN;
            int num_of_roots = 0;

            if(solve_quadratic_equation(a, b, c, &x1, &x2, &num_of_roots))
            {
                print_roots(x1, x2, num_of_roots);
            }
        }

        if(!ask_for_continue()) break;

    }

    show_separator();
    show_kitty();

    PRINT_WITH_ANIM(DELAY_FAST, "That's all!\n");

//    printf("That's all!\n");

    return 0;
}


static void show_separator()
{
    printf(COLOR_WHITE "=======================================================================\n" COLOR_RESET);
}

static void show_kitty()
{
    printf(COLOR_PURPLE "\
       _                  \n\
       \\`*-.              \n\
        )  _`-.             \n\
       .  : `. .             \n\
       : _   '  \\            \n\
       ; *` _.   `*-._         \n\
       `-.-'          `-.       \n\
         ;       `       `.      \n\
         :.       .        \\     \n\
         . \\  .   :   .-'   .     \n\
         '  `+.;  ;  '      :       \n\
         :  '  |    ;       ;-.      \n\
         ; '   : :`-:     _.`* ;      \n\
      .*' /  .*' ; .*`- +'  `*'        \n\
      `*-*   `*-*  `*-*'                \n" COLOR_RESET);
}
