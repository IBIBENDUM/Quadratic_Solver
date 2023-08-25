#include <stdio.h>
#include <math.h>

#include "qe_solver.h"
#include "qe_solver_interactive.h"
#include "colors.h"

static void show_separator();
static void show_kitty();

int main(int argc, char **argv)
{
    printf(COLOR_BLUE "This program solves quadratic equations!\nVersion: 1.2\n" COLOR_RESET);
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
    printf("That's all!\n");

    return 0;
}


static void show_separator(void)
{
    printf(COLOR_WHITE "=======================================================================\n" COLOR_RESET);
}

static void show_kitty(void)
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
