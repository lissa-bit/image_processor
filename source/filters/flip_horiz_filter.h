#pragma once

#include "filter.h"

class FlopFilter : public Filter {
public:
    FlopFilter(int width, int height);
    void Apply(Image& image) const override;
};
