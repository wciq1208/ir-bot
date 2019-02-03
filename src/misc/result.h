#ifndef RESULT_H
#define RESULT_H
#include <optional>
namespace ir {
    template <class T>
    class Result {
    private:
        std::optional<T> data_;
        std::string info_;

    public:
        Result(T &&data) : data_(data){};
        Result(std::nullopt_t, const std::string &&info) : info_(info){};
        bool ok() { return data_.has_value(); }
        const T &value() { return data_.value(); }
        const std::string &info() { return info_; }
    };
} // namespace ir
#endif