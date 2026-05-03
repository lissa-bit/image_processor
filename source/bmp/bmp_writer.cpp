#include "bmp_writer.h"
#include <fstream>
#include <cstdint>

#pragma pack(push, 1)

struct BMPFileHeader {
    uint16_t bfType = 0x4D42;
    uint32_t bfSize;
    uint16_t bfReserved1 = 0;
    uint16_t bfReserved2 = 0;
    uint32_t bfOffBits = 54;
};

struct BMPInfoHeader {
    uint32_t biSize = 40;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes = 1;
    uint16_t biBitCount = 24;
    uint32_t biCompression = 0;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter = 0;
    int32_t biYPelsPerMeter = 0;
    uint32_t biClrUsed = 0;
    uint32_t biClrImportant = 0;
};

#pragma pack(pop)

void WriteBMP(const std::string& filename, const Image& image) {
    std::ofstream file(filename, std::ios::binary);
    int width = image.GetWidth();
    int height = image.GetHeight();
    int row_padded = (width * 3 + 3) & (~3);
    int data_size = row_padded * height;
    BMPFileHeader file_header;
    BMPInfoHeader info_header;
    const int padding_const = 54;
    file_header.bfSize = padding_const + data_size;
    info_header.biWidth = width;
    info_header.biHeight = height;
    info_header.biSizeImage = data_size;
    file.write(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    file.write(reinterpret_cast<char*>(&info_header), sizeof(info_header));
    std::vector<uint8_t> row(row_padded);
    const int rgbmax_const = 255;
    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            const Color& c = image.Get(x, y);
            row[x * 3 + 0] = static_cast<uint8_t>(c.b * rgbmax_const);
            row[x * 3 + 1] = static_cast<uint8_t>(c.g * rgbmax_const);
            row[x * 3 + 2] = static_cast<uint8_t>(c.r * rgbmax_const);
        }
        file.write(reinterpret_cast<char*>(row.data()), row_padded);
    }
}
