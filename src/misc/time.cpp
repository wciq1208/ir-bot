#include "time.h"
#include <fmt/time.h>
#include <iomanip>
#include <sstream>
#include "exception.h"
#include "type.h"

namespace ir {
    std::string Time::time2str(time_t time, const std::string &&f) {
        std::string result;
        try {
            auto t = fmt::localtime(time);
            std::stringstream ss;
            ss << std::put_time(&t, f.data());
            result = (ss.str());
        } catch (...) {
            logging::error(u8"time convert error", Exception::getInfo());
        }
        return result;
    }
    std::string Time::time2str(const std::chrono::system_clock::time_point time, const std::string &&f) {
        return time2str(std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch()).count(),
                        std::move(f));
    }
} // namespace ir