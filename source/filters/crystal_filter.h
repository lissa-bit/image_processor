#pragma once

#include "filter.h"

class CrystallizeFilter : public Filter {
public:
    explicit CrystallizeFilter(int radius);
    void Apply(Image& image) const override;

private:
    int radius_;
};
