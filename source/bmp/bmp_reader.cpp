#include "bmp_reader.h"
#include <fstream>
#include <stdexcept>
#include <cstdint>

#pragma pack(push, 1)

struct BMPFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BMPInfoHeader {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

#pragma pack(pop)

Image ReadBMP(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file");
    }
    BMPFileHeader file_header;
    BMPInfoHeader info_header;
    file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));
    const int not_bmp_const = 0x4D42;
    const int bit_c_const = 24;
    if (file_header.bfType != not_bmp_const) {
        throw std::runtime_error("Not a BMP file");
    }
    if (info_header.biBitCount != bit_c_const) {
        throw std::runtime_error("Unsupported format");
    }
    if (info_header.biCompression != 0) {
        throw std::runtime_error("Compressed BMP");
    }
    int width = info_header.biWidth;
    int height = info_header.biHeight;

    Image image(width, height);

    int row_padded = (width * 3 + 3) & (~3);
    std::vector<uint8_t> row(row_padded);

    for (int y = height - 1; y >= 0; --y) {
        file.read(reinterpret_cast<char*>(row.data()), row_padded);
        for (int x = 0; x < width; ++x) {
            uint8_t b = row[x * 3 + 0];
            uint8_t g = row[x * 3 + 1];
            uint8_t r = row[x * 3 + 2];
            const float rgb_max = 255.0f;
            image.Get(x, y) = Color(static_cast<float>(r) / rgb_max, static_cast<float>(g) / rgb_max,
                                    static_cast<float>(b) / rgb_max);
        }
    }
    return image;
}
