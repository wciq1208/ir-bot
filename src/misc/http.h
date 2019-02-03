#ifndef HTTP_H
#define HTTP_H
#include <curl/curl.h>
#include <optional>
#include "result.h"

namespace ir {
    class HTTP {
    private:
        CURL *curl_;

    public:
        HTTP() : curl_(nullptr) {}
        Result<std::string> get(const std::string &url);
        Result<std::string> get(const std::string &&url);
        ~HTTP();
    };
} // namespace ir
#endif