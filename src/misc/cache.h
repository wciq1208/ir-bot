
#ifndef CACHE_H
#define CACHE_H
#include <mutex>
#include <string>
#include <unordered_map>
#include "ptr.h"

namespace ir {
    template <class T>
    class Cache {
    private:
        Ptr<T> data_;

    public:
        Cache(std::string &&name, uint32_t ttl){

        };
        ~cache();
    };

    template <class K, class T>
    class CacheHandler {
    private:
        static std::unordered_map<K, Ptr<T>> data_;
        static std::mutex m_;
        Ptr<T> ptr_;

    public:
        CacheHandler(const K &key) {
            std::lock_guard<std::mutex> l(m_);
            if (data_.count(key) > 0) {
                ptr = data[key];
            }
        }
    }

} // namespace ir
#endif
