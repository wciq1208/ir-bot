#ifndef PTR_H
#define PTR_H
#include <atomic>
#include <shared_ptr>
template <class T>
class Ptr {
private:
    std::atomic<std::shared_ptr<T>> data_;

public:
    Ptr() = default;
    Ptr(Ptr<T> &) = default;
    Ptr(Ptr<T> &&) = default;
    template <class... Args>
    Ptr(Args... args) {
        data_.store(std::make_shared<T>(args...));
    };
    void set(T &&data) { data_.store(std::move(data)); }
    void set(const T &data) { data_.store(data); }
    T *get() { return data_.load().get(); }
};
#endif