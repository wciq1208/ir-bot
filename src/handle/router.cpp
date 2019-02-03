#include "router.h"
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include "walkure.h"

namespace ir {
    void Router::work(const cq::PrivateMessageEvent &e) {
        auto msg = std::to_string(e.message);
        boost::algorithm::trim(msg);
        std::vector<std::string> result;
        boost::algorithm::split(result, msg, boost::algorithm::is_any_of(u8" 　"), boost::algorithm::token_compress_on);
        if (result.empty()) {
            return;
        }
        auto uri = result.front();
        if (uri == "/walkure") {
            Walkure(result, e);
        }
    }
} // namespace ir