#ifndef INIT_H
#define INIT_H
#include "curl/curl.h"
namespace ir {
    void init() { curl_global_init(CURL_GLOBAL_ALL); }
} // namespace ir
#endif