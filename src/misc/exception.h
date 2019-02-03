#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <string>
class Exception {
public:
    static std::string getInfo() {
        auto p = std::current_exception();
        try {
            if (p) {
                std::rethrow_exception(p);
            }
            return "";
        } catch (const std::exception &e) {
            return e.what();
        }
    }
};
#endif