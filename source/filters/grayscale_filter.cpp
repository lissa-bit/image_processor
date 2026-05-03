#include "grayscale_filter.h"

void GrayscaleFilter::Apply(Image& image) const {
    for (int y = 0; y < image.GetHeight(); y++) {
        for (int x = 0; x < image.GetWidth(); x++) {
            Color& c = image.Get(x, y);
            const float r_const = 0.299f;
            const float g_const = 0.587f;
            const float b_const = 0.114f;
            float gray = r_const * c.r + g_const * c.g + b_const * c.b;
            c = Color(gray, gray, gray);
        }
    }
}
