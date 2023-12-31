#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <complex.h>
#include <math.h>
#include <errno.h>
#include <assert.h>

#include "print_with_anim.h"
#include "make_logs.h"
#include "colors.h"
#include "time_utils.h"

#define RETURN_WITH_STRERROR(X)\
{                               \
        printf(COLOR_RED "%s" COLOR_RESET, strerror(errno)); \
        return X;\
}
// TODO: do...while?

size_t current_anim_mode = ANIM_ENABLED; // TODO: size_t??

// TODO: Why even create enum types if you then never use them?

// LOG_MODE current_log_mode = TO_CONSOLE;
// ^~~~~~~~ also, what is with this naming style? 



int current_log_mode = TO_CONSOLE;
int current_log_level = LOG_LVL_DISABLED;
char const *log_file_name = "qe_solver.log"; // TODO: hardcoded file name with related project's name embeded in it?

static char* current_time_to_str(); // TODO: Man...

static char* current_time_to_str()
{
    static char time_buf[] = "%H:%M:%S";

    time_t current_time = time(0);
    struct tm* tm_info = localtime(&current_time);

    strftime(time_buf, sizeof(time_buf), "%H:%M:%S", tm_info);
    return time_buf;
}

void write_log(const int log_level, const char file[], const char func[], const int line, const char *format, ...)
{
    if (log_level <= current_log_level)
    {
        FILE *file_ptr = NULL;

        if (current_log_mode == TO_CONSOLE) // TODO: this should be gone after changes
        {
            file_ptr = stdout;
            if (log_level == LOG_LVL_MESSAGE)
                printf(COLOR_YELLOW);
            else
                printf(COLOR_RED);
        }

        else  // TO_FILE
        {
            file_ptr = fopen(log_file_name, "a");

            if (!file_ptr)
                RETURN_WITH_STRERROR();
        }



        fprintf(file_ptr, "[%s] (FILE: %s, FUNC: %s, LINE: %d)\n", current_time_to_str(), file, func, line);

        // printf message
        va_list args;
        va_start(args, format);
        vfprintf(file_ptr, format, args);
        va_end(args);
        putc('\n', file_ptr);

        if (current_log_mode == TO_FILE)
        {
            if (fclose(file_ptr))
                RETURN_WITH_STRERROR();
        }
        else
            printf(COLOR_RESET);
    }
}

bool clear_log_file() // TODO: Why is your user even exposed to this?
{
    FILE *file_ptr = fopen(log_file_name, "w");
    if (!file_ptr)
        RETURN_WITH_STRERROR(true); // TODO: And what would you do if clear log failed?...

    if (fclose(file_ptr))
        RETURN_WITH_STRERROR(true);

    return false; // TODO: false if success, why?
}

void print_with_anim(const char color[], const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char message[LOG_STR_LEN] = {};
    vsnprintf(message, LOG_STR_LEN, format, args);

    va_end(args);

    switch (current_anim_mode)
    {
        case ANIM_DISABLED: { // TODO: isn't this an "if"?
            printf("%s%s%s", color, message, COLOR_RESET);
            break;
        }

        case ANIM_ENABLED: {
            printf(color);
            for (size_t i = 0; message[i]; i++)
            {
                printf("%c", toupper(message[i]));

                // TODO: shouldn't this animation's delay be an explicit parameter instead of a global variable?
                Sleep(ANIM_DELAY);
                if (islower(message[i]))
                    printf("\b%c", message[i]);
                Sleep(ANIM_DELAY);
            }
            printf(COLOR_RESET);
            break;
        }

        default: {
            break; // TODO: As it wasn't obviouse already
            // TODO: Why do you think compiler issues a warning here? Just for you to silence it? Wrong!
            //       For you to fix!
        }
    }
}
