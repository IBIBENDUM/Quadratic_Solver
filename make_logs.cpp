#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <complex.h>
#include <math.h>
#include <Windows.h>

#include "make_logs.h"
#include "colors.h"

int current_log_mode = TO_CONSOLE;
int current_log_level = LOG_LVL_DISABLED;
char *log_file_name = "qe_solver.log";

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
    if (log_level == current_log_level)
    {
        FILE *file_ptr = NULL;

        if (current_log_mode == TO_CONSOLE)
        {
            file_ptr = stdout;
            if (current_log_level == LOG_LVL_MESSAGE)
                printf(COLOR_YELLOW);
            else
                printf(COLOR_RED);
        }
        else  // TO_FILE
        {
            file_ptr = fopen(log_file_name, "a");

            // TODO: not exists
        }

        fprintf(file_ptr, "[%s] (FILE: %s, FUNC: %s, LINE: %d)\n%s\n", current_time_to_str(), file, func, line, message);

        if (current_log_mode == TO_FILE)
            fclose(file_ptr);
        else
            printf(COLOR_RESET);
    }
}

void my_assert(const char expr[], const char file[], const char func[], const int line)
{
    write_log(expr, LOG_LVL_ERROR, file, func, line);
    printf(COLOR_RED "The program ended with an error\n" COLOR_RESET);
    exit(EXIT_FAILURE);
}

void clear_log_file()
{
    // TODO: check errno
    fclose(fopen(log_file_name, "w")); // TODO: what if file will not open
}

char* format_log(const char *format, ...)
{
    va_list ptr;
    va_start(ptr, format);

    char *str = (char *) malloc(STR_LEN * sizeof(char));
    // TODO: str == NULL ?

    unsigned int j = 0;

    for (unsigned int i = 0; format[i]; i++, j++)
    {

        if (format[i] == '%')
        {
            i++;                // Skip '%'

            if (format[i] == 'l' && format[i+1] == 'f')
            {
                i++;            // Skip 'f'
                double lf_val = va_arg(ptr, double);

                if (std::isfinite(lf_val))
                {
                    // TODO: ???
                    if (fabs(lf_val) < MAX_VAL)
                        j += sprintf(str+j, "%.2lf", lf_val);
                    else
                        j += sprintf(str+j, "%.2e", lf_val);
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

void print_by_symbols(const char *string, const int delay)
{
    for (int i = 0; string[i]; i++)
    {
//        printf("%c", toupper(string[i]));
        printf("%c", string[i]);
//        Sleep(delay);
//        if (islower(string[i]))
//            printf("\b%c", string[i]);
//        Sleep(delay);
    }
}
