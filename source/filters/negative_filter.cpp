#include "negative_filter.h"

void NegativeFilter::Apply(Image& image) const {
    for (int y = 0; y < image.GetHeight(); y++) {
        for (int x = 0; x < image.GetWidth(); x++) {
            Color& c = image.Get(x, y);
            c.r = 1.0f - c.r;
            c.g = 1.0f - c.g;
            c.b = 1.0f - c.b;
        }
    }
}
