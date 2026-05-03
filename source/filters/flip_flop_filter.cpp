#include "flip_flop_filter.h"
#include <algorithm>

void CropFilter::Apply(Image& image) const {
    int width = image.GetWidth();
    int height = image.GetHeight();
    
    for (int y = 0; y < height / 2; y++) {
        for (int x = 0; x < width; x++) {
            int new_y = height + 1 - y;
            std::swap(image.Get(x, y), image.Get(x, new_y));
        }  
    }

    image = result;
}
