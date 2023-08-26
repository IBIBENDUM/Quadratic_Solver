#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <complex.h>

#include "make_logs.h"
#include "colors.h"

int current_log_mode = TO_CONSOLE;
int current_log_level = LOG_DISABLED;
char log_file_name[] = "qe_solver.log";

static char* current_time_to_str();

static char* current_time_to_str()
{
    time_t current_time = time(0);
    struct tm* tm_info = localtime(&current_time);

    const int str_len = 9;
    char *time_str = (char *) malloc(str_len * sizeof(char));
    strftime(time_str, str_len, "%H:%M:%S", tm_info);
    return time_str;
}

void write_log(const char message[], int log_level, const char file[], const char func[], const int line)
{
    if (log_level == current_log_level)
    {
        FILE *file_ptr = NULL;

        if (current_log_mode == TO_CONSOLE)
            file_ptr = stdout;

        else if (current_log_mode == TO_FILE)
            file_ptr = fopen(log_file_name, "a");

        fprintf(file_ptr, "[%s] (FILE: %s, FUNC: %s, LINE: %d) %s\n", current_time_to_str(), file, func, line, message);

        if (current_log_mode == TO_FILE)
            fclose(file_ptr);

    }
}

void my_assert(const char expr[], const char file[], const char func[], const int line)
{
    write_log(expr, LOG_ERROR, file, func, line);
    printf("The program ended with an error");
    exit(EXIT_FAILURE);
}

void clear_log_file()
{
    fclose(fopen(log_file_name, "w"));
}

char* format_log(char *format, ...)
{
    va_list ptr;
    va_start(ptr, format);

    char *str = (char *) malloc(STR_LEN * sizeof(char));

    for (unsigned int i = 0, j =0; format[i]; i++, j++)
    {
        if (format[i] == '%')
        {
            i++;                // Skip '%'
            if (format[i] == 'l' && format[i+1] == 'f')
            {
                i++;            // Skip 'l'
                i++;            // Skip 'f'
                j += sprintf(str+j, "%.2lf", va_arg(ptr, double));
            }

            else if (format[i] == 'd')
            {
                i++;            // Skip 'd'
                j += sprintf(str+j, "%d", va_arg(ptr,int));
            }

        }

        if (format[i] == '\\')
        {
            i++;               // Skip '\'
            if (format[i] == 'n')
            {
                 str[j] = '\n';
            }
            else if (format[i] == '0')
            {
                str[j] = '\0';
            }
        }

        sprintf(str+j, "%c", format[i]);

      }

    strcat(str, "\0");
    va_end(ptr);

    return str;
}
