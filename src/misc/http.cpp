#include "http.h"
#include "type.h"

namespace ir {
    namespace {
        size_t get_body(void *ptr, size_t size, size_t nmemb, void *stream) {
            auto *str = (std::string *)stream;
            str->append((char *)ptr, size * nmemb);
            return size * nmemb;
        }
    } // namespace
    Result<std::string> HTTP::get(const std::string &&url) { return get(url); }
    Result<std::string> HTTP::get(const std::string &url) {
        if (curl_ != nullptr) {
            curl_easy_cleanup(curl_);
        }
        curl_ = curl_easy_init();
        std::string response;
        curl_easy_setopt(curl_, CURLOPT_TIMEOUT, 5L);
        curl_easy_setopt(curl_, CURLOPT_CONNECTTIMEOUT, 10L);
        curl_easy_setopt(curl_, CURLOPT_URL, url.data());
        curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1);
        curl_easy_setopt(curl_, CURLOPT_NOSIGNAL, 1L); //关闭中断信号响应
        curl_easy_setopt(curl_, CURLOPT_VERBOSE, 1L); //启用时会汇报所有的信息
        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, get_body);
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, (void *)&response);
        long response_code = 0;
        auto res = curl_easy_perform(curl_);
        if (res != CURLE_OK) {
            return Result<std::string>(std::nullopt, curl_easy_strerror(res));
        }
        res = curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &response_code);
        if (res != CURLE_OK || response_code != 200) {
            return Result<std::string>(std::nullopt, curl_easy_strerror(res));
        }
        return response;
    }
    HTTP::~HTTP() {
        if (curl_ != nullptr) {
            curl_easy_cleanup(curl_);
        }
    }
} // namespace ir