#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <complex.h>
#include <math.h>
#include <Windows.h>
#include <errno.h>
#include <assert.h>

#include "print_with_anim.h"
#include "make_logs.h"
#include "colors.h"

int current_log_mode = TO_CONSOLE;
int current_log_level = LOG_LVL_DISABLED;
char const *log_file_name = "qe_solver.log";

static char* current_time_to_str();

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

        if (current_log_mode == TO_CONSOLE)
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

bool clear_log_file()
{
    FILE *file_ptr = fopen(log_file_name, "w");
    if (!file_ptr)
        RETURN_WITH_STRERROR(true);

    if (fclose(file_ptr))
        RETURN_WITH_STRERROR(true);

    return false;
}
