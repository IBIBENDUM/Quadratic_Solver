#ifndef MAKE_LOGS_H_
#define MAKE_LOGS_H_

#include <stdlib.h>


/// Log message
///
/// Call format_log then send output to write_log
/// ### Example
/// ~~~~~~~~~~~~~~~~~~~.cpp
/// LOG(LOG_LVL_MESSAGE, "D = %lf", d);
/// ~~~~~~~~~~~~~~~~~~~
/// @param FORMAT Format that is passed to the format_log()
/// @param LVL Level that is passed to the write_log()
/// @see format_log(), write_log()
#define LOG(LVL, FORMAT, ...)\
do{ \
    char *log_ptr;             \
    log_ptr = format_log(FORMAT, ##__VA_ARGS__);\
    write_log(log_ptr, LVL, __FILE__, __PRETTY_FUNCTION__, __LINE__);\
    free(log_ptr);}\
while(0)

/// Print message with animation
///
/// Call format_log then send output to print_by_symbols()
/// ### Example
/// ~~~~~~~~~~~~~~~~~~~.cpp
/// PRINT_WITH_ANIM(DELAY_SLOW, "This program solves quadratic equations!\nVersion: 1.2\n");
/// ~~~~~~~~~~~~~~~~~~~
/// @param FORMAT Format that is passed to the print_by_symbols()
/// @see format_log(), print_by_symbols()
#define PRINT_WITH_ANIM(DELAY, FORMAT, ...)\
do{ \
    char *log_ptr;             \
    log_ptr = format_log(FORMAT, ##__VA_ARGS__);\
    print_by_symbols(log_ptr, DELAY);\
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
const int DELAY_FAST = 1;

extern int current_log_mode;
extern int current_log_level;
extern char log_file_name[];


/// Assert function with write_log() call
/// ### Output example
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
/// [11:57:03] (FILE: qe_solver_interactive.cpp, FUNC: int get_expected_args_amount(const char*), LINE: 33)
/// !format
/// The program ended with an error
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// @param expr Assert expression
/// @param file, func, line File, func, line where my_assert() called from
/// @see write_log()
void my_assert(const char expr[], const char file[], const char func[], const int line);

/// Clear file where log will write
void clear_log_file();

/// Write log to selected output
///
/// Usually calling from LOG() macro
/// ### Output example
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
/// [12:02:52] (FILE: qe_solver.cpp, FUNC: double calculate_discriminant(double, double, double), LINE: 28)
/// D = -8.00
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// @param message Output message
/// @param log_level Level or higher at which the message will be displayed
/// @param file, func, line File, func, line where write_log() called from
void write_log(const char message[], const int log_level, const char file[], const char func[], const int line);

/// Printf alternative but output is string
///
/// Usually calling from LOG() or PRINT_WITH_ANIM() macros
char* format_log(const char *format, ...);

/// Print string with appearance animation
/// @param string String which will be displayed
/// @param delay Delay value (multiples by two)
void print_by_symbols(const char *string, const int delay);

#endif
