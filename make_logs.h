#ifndef MAKE_LOGS_H_
#define MAKE_LOGS_H_

#define LOG(X, Y)\
    write_log(X, Y, __FILE__, __PRETTY_FUNCTION__, __LINE__)

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
    LOG_DISABLED,
    LOG_MESSAGE,
    LOG_ERROR
};

const int STR_LEN = 128;

extern int current_log_mode;
extern int current_log_level;
extern char log_file_name[];

void my_assert(const char expr[], const char file[], const char func[], const int line);

void clear_log_file();

void write_log(const char message[], int log_level, const char file[], const char func[], const int line);

char* format_log(char *format, ...);

#endif
