#include <stdio.h>
#include <math.h>
#include <string.h>
#include <Windows.h>

#include "qe_solver.h"
#include "qe_solver_interactive.h"
#include "colors.h"
#include "make_logs.h"

static void show_separator();
static void show_kitty();

int main(int argc, char **argv)
{
    // .\main.exe -log error -console
    // .\main.exe -log message -file
    // .\main.exe -log message -file aboba.txt

    // TODO: TAKE A LOOK HOW TO MAKE FLAGS BETTER (it's working but looks terrible)


    // getopt() man
    if (argc >= 2 && strcmp(argv[1], "-log") == 0) // By default log to console
    {
        current_log_level = LOG_LVL_MESSAGE;

        if (argc >= 3)
        {
            if (strcmp(argv[2], "disable") == 0)
                current_log_level = LOG_LVL_DISABLED;

            else if (strcmp(argv[2], "message") == 0)
                current_log_level = LOG_LVL_MESSAGE;

            else if (strcmp(argv[2], "error") == 0)
                current_log_level = LOG_LVL_ERROR;
            if (argc >= 4)
            {
                if (strcmp(argv[3], "-console") == 0)
                    current_log_mode = TO_CONSOLE;

                else if (strcmp(argv[3], "-file") == 0)
                    current_log_mode = TO_FILE;

                if (argc >= 5)
                    strcpy(log_file_name, argv[4]);  // TODO: assign pointer to argv[n]
            }
        }

        clear_log_file();
    }
//    printf(COLOR_BLUE "This program solves quadratic equations!\nVersion: 1.2\n" COLOR_RESET);
    printf(COLOR_BLUE);
    PRINT_WITH_ANIM(DELAY_FAST, "This program solves quadratic equations!\nVersion: 1.2\n");
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
