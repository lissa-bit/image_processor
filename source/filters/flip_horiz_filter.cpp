#include "flip_horiz_filter.h"
#include <algorithm>

void CropFilter::Apply(Image& image) const {
    int width = image.GetWidth();
    int height = image.GetHeight();
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width / 2; x++) {
            int new_x = width + 1 - x;
            std::swap(image.Get(x, y), image.Get(new_x, y));
        }  
    }
    image = result;
}
