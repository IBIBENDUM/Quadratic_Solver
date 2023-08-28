#include <stdio.h>
#include <Windows.h>
#include <stdarg.h>
#include <ctype.h>

#include "make_logs.h"

void print_by_symbols(const char *string);
int printf_animated(const char *format, ...);

char* format_log(const char *format, ...)
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
                i++;            // Skip 'f'
                double lf_val = va_arg(ptr, double);

                if (std::isfinite(lf_val))
                {
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
                j += sprintf(str+j, "%s", va_arg(ptr,const char*));
                //j--; // Remove \0 ???
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

    strcat(str, "\0");
    va_end(ptr);

    return str;
}

int main()
{
    print_by_symbols(format_log("Agfddg"));
}
void print_by_symbols(const char *string)
{
    for (int i = 0; string[i]; i++)
    {
        putchar(toupper(string[i]));
        Sleep(50);
        if (islower(string[i]))
            printf("\b%c", string[i]);
        Sleep(50);
    }
}
