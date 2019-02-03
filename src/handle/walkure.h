#ifndef WALKURE_H
#define WALKURE_H
#include <chrono>
#include <nlohmann/json.hpp>
#include "../misc/type.h"

namespace ir {
    struct WalkureUser {
        std::string name;
        float hoshi;
        time_t last_modified;
    };
    class Walkure {
    public:
        Walkure(const std::vector<std::string>& args, const cq::PrivateMessageEvent& e);
        float getHoshi();
        std::string& getName();
        std::string getLastModified();

    private:
        uint32_t irid_;
        WalkureUser user_;
    };
} // namespace ir
#endif