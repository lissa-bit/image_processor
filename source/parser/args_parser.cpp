#include "args_parser.h"
#include <stdexcept>
#include "filters/filter_factory.h"

ArgsParser::ArgsParser(int argc, char** argv) {
    if (argc < 3) {
        throw std::invalid_argument("Need more arguments");
    }
    input_path_ = argv[1];
    output_path_ = argv[2];
    for (int i = 3; i < argc; ++i) {
        args_.push_back(argv[i]);
    }
}

const std::string& ArgsParser::GetInputPath() const {
    return input_path_;
}

const std::string& ArgsParser::GetOutputPath() const {
    return output_path_;
}

FilterPipeline ArgsParser::BuildPipeline() const {
    FilterPipeline pipeline;
    size_t i = 0;
    while (i < args_.size()) {
        std::string name = args_[i];
        if (name[0] != '-') {
            throw std::invalid_argument("Filter name starts with '-'");
        }
        ++i;
        std::vector<std::string> filter_args;
        while (i < args_.size() && args_[i][0] != '-') {
            filter_args.push_back(args_[i]);
            ++i;
        }
        std::unique_ptr<Filter> filter = FilterFactory::Create(name, filter_args);
        pipeline.AddFilter(std::move(filter));
    }
    return pipeline;
}
