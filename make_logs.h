#ifndef MAKE_LOGS_H_
#define MAKE_LOGS_H_

#include <stdlib.h>


// ===================================== BEFORE =====================================
// #define LOG(LVL, FORMAT, ...)                                        \
//     do                                                                \
//     {                                                                  \
//         write_log(LVL, __FILE__, __PRETTY_FUNCTION__, __LINE__, FORMAT, ##__VA_ARGS__); \
//     }                                                                       \
//     while(0)

// ================================= AND THEN AFTER =================================
// #define LOG(LVL, FORMAT, ...)                                                           \
//     do                                                                                  \
//     {                                                                                   \
//         write_log(LVL, __FILE__, __PRETTY_FUNCTION__, __LINE__, FORMAT, ##__VA_ARGS__); \
//     }                                                                                   \
//     while(0)

// TODO: ^^^ DECIDE WHAT DO YOU THINK IS BETTER FOR MY MENTAL HEALTH AND YOUR TOO ^^^
// ==================================================================================



/// Log message
///
/// Call format_log then send output to write_log
/// ### Example
/// ~~~~~~~~~~~~~~~~~~~.cpp
/// LOG(LOG_LVL_MESSAGE, "D = %g", d);
/// ~~~~~~~~~~~~~~~~~~~
/// @param FORMAT Format that is passed to the format_log()
/// @param LVL Level that is passed to the write_log()
/// @see format_log(), write_log()
#define LOG(LVL, FORMAT, ...)                                                           \
    do                                                                                  \
    {                                                                                   \
        write_log(LVL, __FILE__, __PRETTY_FUNCTION__, __LINE__, FORMAT, ##__VA_ARGS__); \
    }                                                                                   \
    while(0)

#define RETURN_WITH_STRERROR(VAR)\
{                               \
        printf(COLOR_RED "%s\n" COLOR_RESET, strerror(errno)); \
        return VAR;\
}

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

const size_t LOG_STR_LEN = 128;
const double MAX_VAL = 1E5;

enum ANIM_MODE
{
    ANIM_DISABLED,
    ANIM_ENABLED
}; // TODO: not enough... space... c.c..can't... breeea..th!
const size_t ANIM_DELAY = 5;
extern size_t current_anim_mode; // BAH: Come up with something better

extern int current_log_mode;
extern int current_log_level;


// TODO: I think you just ruined this library's speed with
//       your decision to reopen log file every time.

//       Also you made it a lot narrower than it needs to be:
//       you can't write to files without names (buffers, 
//       stdout, stderr, so on, but you could if you were
//       to use file descriptors)

extern const char *log_file_name;


/// Clear file where log will write
bool clear_log_file();

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
void write_log(const int log_level, const char file[], const char func[], const int line, const char *format, ...);



// TODO: annotate __attribute__((noreturn))


#endif
