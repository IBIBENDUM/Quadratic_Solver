#ifndef MAKE_LOGS_H_
#define MAKE_LOGS_H_

#define LOG(X, Y)\
write_log(X, Y, __FILE__, __PRETTY_FUNCTION__, __LINE__)

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


extern int current_log_mode;
extern int current_log_level;
extern char log_file_name[];


void clear_log_file();

void write_log(const char message[], int log_level, const char file[], const char func[], const int line);


#endif
