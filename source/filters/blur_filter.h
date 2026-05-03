#pragma once
#include "filter.h"

class BlurFilter : public Filter {
public:
    explicit BlurFilter(float sigma);
    void Apply(Image& image) const override;

private:
    float sigma_;
};
