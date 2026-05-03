#include "blur_filter.h"
#include <cmath>

BlurFilter::BlurFilter(float sigma) : sigma_(sigma) {
}

void BlurFilter::Apply(Image& image) const {
    int radius = static_cast<int>(sigma_ * 3);
    int width = image.GetWidth();
    int height = image.GetHeight();
    std::vector<float> kernel(2 * radius + 1);
    float weight_sum = 0;
    for (int i = -radius; i <= radius; i++) {
        kernel[i + radius] = std::exp(-static_cast<float>(i * i) / (2 * sigma_ * sigma_));
        weight_sum += kernel[i + radius];
    }
    for (auto& w : kernel) {
        w /= weight_sum;
    }
    Image tmp(width, height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float r = 0;
            float g = 0;
            float b = 0;
            for (int dx = -radius; dx <= radius; dx++) {
                const Color& c = image.Get(x + dx, y);
                float w = kernel[dx + radius];
                r += c.r * w;
                g += c.g * w;
                b += c.b * w;
            }
            tmp.Get(x, y) = Color(r, g, b);
        }
    }
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float r = 0;
            float g = 0;
            float b = 0;
            for (int dy = -radius; dy <= radius; dy++) {
                const Color& c = tmp.Get(x, y + dy);
                float w = kernel[dy + radius];
                r += c.r * w;
                g += c.g * w;
                b += c.b * w;
            }
            Color result(r, g, b);
            result.Clamp();
            image.Get(x, y) = result;
        }
    }
}
