#include "walkure.h"
#include <fmt/format.h>
#include <fmt/time.h>
#include "../misc/http.h"
#include "../misc/options.h"
#include "../misc/result.h"
#include "../misc/time.h"
#include "../misc/type.h"

namespace ir {
    void from_json(const nlohmann::json& j, WalkureUser& user) {
        user.name = j.at("name").get<std::string>();
        user.hoshi = j.at("hoshi").get<float>();
        user.last_modified = j.at("last_modified").get<time_t>();
    }
    namespace {
        Result<boost::program_options::variables_map> parseArgs(const std::vector<std::string>& args) {
            boost::program_options::options_description opts;
            for (auto i : args) {
                logging::debug(u8"test", i);
            }
            opts.add_options()("irid", boost::program_options::value<uint8_t>(), "ir id")(
                "action", boost::program_options::value<std::string>()->default_value("hoshi"), "action");
            return Options::parse(args, opts);
        }
        Result<WalkureUser> request(uint32_t irid) {
            auto http = HTTP();
            auto url = fmt::format("http://walkure.net/hakkyou/recommended_json.cgi?id={}", irid);
            auto res = http.get(url);
            if (res.ok()) {
                try {
                    auto j = nlohmann::json::parse(res.value());
                    return j.get<WalkureUser>();
                } catch (...) {
                }
                logging::info(u8"API", fmt::format(u8"请求walkure数据：{}", res.value()));
            } else {
                logging::info(u8"API", fmt::format(u8"请求walkure({})失败：{}", url, res.info()));
            }
            return Result<WalkureUser>(std::nullopt, std::move(res.info()));
        }
    } // namespace
    Walkure::Walkure(const std::vector<std::string>& args, const cq::PrivateMessageEvent& e) {
        Result<boost::program_options::variables_map> vm(parseArgs(args));
        if (!vm.ok()) {
            logging::error(u8"walkure", fmt::format(u8"parse args error:{}", vm.info()));
            return;
        }
        if (!vm.value().count("irid")) {
            logging::error(u8"walkure", u8"not found irid");
            return;
        }
        irid_ = vm.value()["irid"].as<uint8_t>();
        auto res = request(irid_);
        if (!res.ok()) {
            logging::error(u8"walkure", fmt::format(u8"parse args error:{}", vm.info()));
            return;
        }
        user_ = std::move(res.value());
        auto action = vm.value()["action"].as<std::string>();
        if (action == "hoshi") {
            api::send_msg(e.target,
                          fmt::format(u8"{}的实力值是：{}，最后更新时间为：{}",
                                      getName(),
                                      getHoshi(),
                                      getLastModified())); // 使用 e.target 指定发送目标
        }
    }
    float Walkure::getHoshi() { return user_.hoshi; }
    std::string& Walkure::getName() { return user_.name; }
    std::string Walkure::getLastModified() { return Time::time2str(user_.last_modified, u8"%F %T"); }
} // namespace ir