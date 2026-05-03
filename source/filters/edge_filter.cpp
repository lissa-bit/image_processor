#include "edge_filter.h"
#include <algorithm>

EdgeFilter::EdgeFilter(float threshold) : threshold_(threshold) {
}

void EdgeFilter::Apply(Image& image) const {

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

    Image copy = image;
    int kernel[3][3] = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

    for (int y = 0; y < image.GetHeight(); y++) {
        for (int x = 0; x < image.GetWidth(); x++) {
            float value = 0;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    float gray = copy.Get(x + dx, y + dy).r;
                    value += gray * static_cast<float>(kernel[dy + 1][dx + 1]);
                }
            }

            if (value > threshold_) {
                image.Get(x, y) = Color(1, 1, 1);
            } else {
                image.Get(x, y) = Color(0, 0, 0);
            }
        }
    }
}
