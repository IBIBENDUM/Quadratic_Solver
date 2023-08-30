#ifndef PRINT_WITH_ANIM_H_
#define PRINT_WITH_ANIM_H_

//
//struct print_settings
//{
//  const char *color;
//  bool anim_mode;
//};

enum ANIM_MODE
{
    ANIM_DISABLED,
    ANIM_ENABLED
};
const size_t ANIM_DELAY = 5;
const size_t MSG_STR_LEN = 128;
extern size_t current_anim_mode; // BAH: Come up with something better


/// Print string with appearance animation
/// @param string String which will be displayed
/// @param delay Delay value (multiples by two)
void print_with_anim(const char color[], const char *format, ...);

#endif
