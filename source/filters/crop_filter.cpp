#include "crop_filter.h"
#include <algorithm>

CropFilter::CropFilter(int width, int height) : width_(width), height_(height) {
}

void CropFilter::Apply(Image& image) const {
    int new_width = std::min(width_, image.GetWidth());
    int new_height = std::min(height_, image.GetHeight());

    Image result(new_width, new_height);

    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            result.Get(x, y) = image.Get(x, y);
        }
    }
    image = result;
}
