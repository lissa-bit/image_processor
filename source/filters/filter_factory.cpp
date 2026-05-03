#include "filter_factory.h"
#include <stdexcept>
#include "grayscale_filter.h"
#include "negative_filter.h"
#include "sharpen_filter.h"
#include "crop_filter.h"
#include "edge_filter.h"
#include "blur_filter.h"
#include "crystal_filter.h"

std::unique_ptr<Filter> FilterFactory::Create(const std::string& name, const std::vector<std::string>& args) {
    if (name == "-gs") {
        if (!args.empty()) {
            throw std::invalid_argument("Grayscale filter takes no arguments");
        }
        return std::make_unique<GrayscaleFilter>();
    }

    if (name == "-neg") {
        if (!args.empty()) {
            throw std::invalid_argument("Negative filter takes no arguments");
        }
        return std::make_unique<NegativeFilter>();
    }

    if (name == "-sharp") {
        if (!args.empty()) {
            throw std::invalid_argument("Sharpen filter takes no arguments");
        }
        return std::make_unique<SharpenFilter>();
    }

    if (name == "-crop") {
        if (args.size() != 2) {
            throw std::invalid_argument("Crop takes 2 arguments");
        }
        int width = std::stoi(args[0]);
        int height = std::stoi(args[1]);
        return std::make_unique<CropFilter>(width, height);
    }

    if (name == "-edge") {
        if (args.size() != 1) {
            throw std::invalid_argument("Edge takes 1 argument");
        }
        float threshold = std::stof(args[0]);
        return std::make_unique<EdgeFilter>(threshold);
    }

    if (name == "-blur") {
        if (args.size() != 1) {
            throw std::invalid_argument("Blur takes 1 argument");
        }
        float sigma = std::stof(args[0]);
        return std::make_unique<BlurFilter>(sigma);
    }

    if (name == "-crystallize") {
        if (args.size() != 1) {
            throw std::invalid_argument("Crystal takes 1 argument");
        }
        int radius = std::stoi(args[0]);
        return std::make_unique<CrystallizeFilter>(radius);
    }

    if (name == "-flip_vert") {
        if (!args.empty()) {
            throw std::invalid_argument("Flip takes no arguments");
        }
        return std::make_unique<VertFlipFilter>();
    }
     if (name == "-flip_hor") {
        if (!args.empty()) {
            throw std::invalid_argument("Flip takes no arguments");
        }
        return std::make_unique<HorFlipFilter>();
    }

    throw std::invalid_argument("Unknown filter: " + name);
}
