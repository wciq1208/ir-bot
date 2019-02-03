#ifndef ROUTER_H
#define ROUTER_H
#include "../misc/type.h"
namespace ir {
    class Router {
    public:
        void work(const cq::PrivateMessageEvent &e);
    };
} // namespace ir

#endif