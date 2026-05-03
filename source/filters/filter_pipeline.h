#pragma once

#include <vector>
#include <memory>
#include "filter.h"

class FilterPipeline {
public:
    void AddFilter(std::unique_ptr<Filter> filter);
    void Apply(Image& image) const;

private:
    std::vector<std::unique_ptr<Filter>> filters_;
};
