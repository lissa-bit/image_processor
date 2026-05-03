#pragma once

#include <memory>
#include <string>
#include <vector>
#include "filter.h"

class FilterFactory {
public:
    static std::unique_ptr<Filter> Create(const std::string& name, const std::vector<std::string>& args);
};
