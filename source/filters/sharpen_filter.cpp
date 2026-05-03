#include "sharpen_filter.h"
#include "utilities/clamp.h"

void SharpenFilter::Apply(Image& image) const {
    Image copy = image;
    const int center_kernel = 5;
    int kernel[3][3] = {{0, -1, 0}, {-1, center_kernel, -1}, {0, -1, 0}};
    for (int y = 0; y < image.GetHeight(); y++) {
        for (int x = 0; x < image.GetWidth(); x++) {
            float r = 0;
            float g = 0;
            float b = 0;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    const Color& c = copy.Get(x + dx, y + dy);
                    int k = kernel[dy + 1][dx + 1];
                    r += c.r * static_cast<float>(k);
                    g += c.g * static_cast<float>(k);
                    b += c.b * static_cast<float>(k);
                }
            }
            Color result(r, g, b);
            result.Clamp();
            image.Get(x, y) = result;
        }
    }
}
