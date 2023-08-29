#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <complex.h>
#include <math.h>
#include <Windows.h>
#include <errno.h>

#include "make_logs.h"
#include "colors.h"

size_t current_anim_mode = ANIM_ENABLED;

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

void write_log(const char message[], const int log_level, const char file[], const char func[], const int line)
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
                exit_with_strerror();
        }

        fprintf(file_ptr, "[%s] (FILE: %s, FUNC: %s, LINE: %d)\n%s\n", current_time_to_str(), file, func, line, message);

        if (current_log_mode == TO_FILE)
        {
            if (fclose(file_ptr))
                exit_with_strerror();
        }
        else
            printf(COLOR_RESET);
    }
}

void my_assert(const char expr[], const char file[], const char func[], const int line) // TODO: rename
{
    write_log(expr, LOG_LVL_ERROR, file, func, line);
    printf(COLOR_RED "The program ended with an error\n" COLOR_RESET);
    exit(EXIT_FAILURE);
}

void exit_with_strerror()
{
    printf(COLOR_RED "%s" COLOR_RESET, strerror(errno));
    exit(EXIT_FAILURE);
}

void clear_log_file()
{
    FILE *file_ptr = fopen(log_file_name, "w");
    if (!file_ptr)
        exit_with_strerror();
    if (fclose(file_ptr))
        exit_with_strerror();
}

char* format_log(const char *format, ...)
{
    va_list ptr;
    va_start(ptr, format);

    // TODO: just use vprintf(), including vsnprintf

    char *str = (char *) malloc(LOG_STR_LEN * sizeof(char));
    if (!str)
        exit_with_strerror();

    unsigned int j = 0;

    for (unsigned int i = 0; format[i]; i++, j++)
    {

        if (format[i] == '%') // TODO: switch...case
        {
            i++;                // Skip '%'

            if (format[i] == 'l' && format[i+1] == 'g')
            {
                i++;            // Skip 'f'
                double lf_val = va_arg(ptr, double);

                if (std::isfinite(lf_val))
                {
                    j += sprintf(str+j, "%.3g", lf_val);
                }

                else
                    j += sprintf(str+j, "Infinite");
            }

            else if (format[i] == 'd')
            {
                j += sprintf(str+j, "%d", va_arg(ptr, int));
            }

            else if (format[i] == 's')
            {
                j += sprintf(str+j, "%s", va_arg(ptr, const char*));
            }

            j--;

            continue;
        }

        else if (format[i] == '\\')
        {
            i++;                // Skip '\'
            if (format[i] == 'n')
            {
                 str[j] = '\n';
            }
            else if (format[i] == '0')
            {
                str[j] = '\0';
            }

            continue;
        }

        str[j] = format[i];
    }

    str[j] = '\0';
    va_end(ptr);

    return str;
}

void print_by_symbols(const char *string)
{
    switch (current_anim_mode)
    {
        case ANIM_DISABLED: {
            printf("%s", string);
            break;
        }

        case ANIM_ENABLED: {
            for (size_t i = 0; string[i]; i++)
            {
                printf("%c", toupper(string[i]));
                Sleep(ANIM_DELAY);
                if (islower(string[i]))
                    printf("\b%c", string[i]);
                Sleep(ANIM_DELAY);
            }
            break;
        }

        default: {
            break;
        }
    }
}
