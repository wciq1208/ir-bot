#ifndef TIME_H
#define TIME_H

#include <chrono>
#include <string>

namespace ir {
    class Time {
    public:
        static std::string time2str(time_t time, const std::string &&f);
        static std::string time2str(const std::chrono::system_clock::time_point time, const std::string &&f);
    };
} // namespace ir
#endif