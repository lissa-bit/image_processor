#pragma once

#include "filter.h"

class EdgeFilter : public Filter {
public:
    explicit EdgeFilter(float threshold);
    void Apply(Image& image) const override;

private:
    float threshold_;
};
