#ifndef MAKE_LOGS_H_
#define MAKE_LOGS_H_

#include <stdlib.h>

#define LOG(LVL, FORMAT, ...)\
do{ \
    char *log_ptr;             \
    log_ptr = format_log(FORMAT, ##__VA_ARGS__);\
    write_log(log_ptr, LVL, __FILE__, __PRETTY_FUNCTION__, __LINE__);\
    free(log_ptr);}\
while(0)

#define MY_ASSERT(X)\
do {\
    if (!(X))\
        my_assert(#X, __FILE__, __PRETTY_FUNCTION__, __LINE__);}\
while(0)

enum LOG_MODE
{
    TO_CONSOLE,
    TO_FILE
};

enum LOG_LEVEL
{
    LOG_LVL_DISABLED,
    LOG_LVL_MESSAGE,
    LOG_LVL_ERROR
};

const int STR_LEN = 128;
const float MAX_VAL = 1E5;

extern int current_log_mode;
extern int current_log_level;
extern char log_file_name[];

void my_assert(const char expr[], const char file[], const char func[], const int line);

void clear_log_file();

void write_log(const char message[], const int log_level, const char file[], const char func[], const int line);

char* format_log(const char *format, ...);

#endif
