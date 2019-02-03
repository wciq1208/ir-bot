#ifndef OPTIONS_H
#define OPTIONS_H
#include <boost/program_options.hpp>
#include "exception.h"
#include "result.h"
#include "type.h"
namespace ir {
    class Options {
    public:
        static Result<boost::program_options::variables_map> parse(
            const std::vector<std::string> &args, const boost::program_options::options_description &opts) {
            boost::program_options::variables_map vm;
            std::vector<char *> charsetVec;
            for (auto str : args) {
                charsetVec.emplace_back(str.data());
            }
            try {
                boost::program_options::store(
                    boost::program_options::parse_command_line(args.size(), &charsetVec.front(), opts), vm);
            } catch (...) {
                return {std::nullopt, Exception::getInfo()};
            }
            return vm;
        }
    };
} // namespace ir
#endif