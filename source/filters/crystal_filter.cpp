#include "crystal_filter.h"

CrystallizeFilter::CrystallizeFilter(int radius) : radius_(radius) {
}

void CrystallizeFilter::Apply(Image& image) const {
    Image copy = image;
    int width = image.GetWidth();
    int height = image.GetHeight();
    for (int y = 0; y < height; y += radius_) {
        for (int x = 0; x < width; x += radius_) {
            int cx = x + radius_ / 2;
            int cy = y + radius_ / 2;
            const Color& center_color = copy.Get(cx, cy);
            for (int dy = 0; dy < radius_; dy++) {
                for (int dx = 0; dx < radius_; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx < width && ny < height) {
                        image.Get(nx, ny) = center_color;
                    }
                }
            }
        }
    }
}
