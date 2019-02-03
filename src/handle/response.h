
#ifndef RESPONSE_H
#define RESPONSE_H
#include "../misc/type.h"

namespace ir {
    class Response {
    public:
        static void OnPrivateMessage(const cq::PrivateMessageEvent &e);
    };
} // namespace ir
#endif