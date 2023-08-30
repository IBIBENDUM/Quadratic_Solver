#include <stdio.h>
#include <Windows.h>
#include <ctype.h>

#include "colors.h"
#include "print_with_anim.h"


size_t current_anim_mode = 0; // BAH: Come up with something better

void print_with_anim(const char color[], const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char message[MSG_STR_LEN] = {};
    vsnprintf(message, MSG_STR_LEN, format, args);
    va_end(args);

    switch (current_anim_mode)
    {
        case ANIM_DISABLED: {
            printf("%s%s%s", color, message, COLOR_RESET);
            break;
        }

        case ANIM_ENABLED: {
            printf("%s", color);
            for (size_t i = 0; message[i]; i++)
            {
                printf("%c", toupper(message[i]));
//                --std=c++17
//                std::this_thread::sleep_for(std::chrono::nanoseconds(ANIM_DELAY));
                Sleep(ANIM_DELAY);
                if (islower(message[i]))
                    printf("\b%c", message[i]);
//                std::this_thread::sleep_for(std::chrono::nanoseconds(ANIM_DELAY));
            }
            printf(COLOR_RESET);
            break;
        }

        default: {
            break;
        }
    }
}
