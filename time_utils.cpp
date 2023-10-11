#include "time_utils.h"

#include <chrono>
#include <thread>

void Sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
