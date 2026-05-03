#pragma once

#include <string>
#include <vector>
#include "filters/filter_pipeline.h"

class ArgsParser {
public:
    ArgsParser(int argc, char** argv);
    const std::string& GetInputPath() const;
    const std::string& GetOutputPath() const;
    FilterPipeline BuildPipeline() const;

private:
    std::string input_path_;
    std::string output_path_;

    std::vector<std::string> args_;
};
