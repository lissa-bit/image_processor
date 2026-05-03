#pragma once

#include "core/image.h"

class Filter {
public:
    virtual void Apply(Image& image) const = 0;
    virtual ~Filter() = default;
};
