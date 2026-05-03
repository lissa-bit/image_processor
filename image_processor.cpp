#include <iostream>
#include "source/parser/args_parser.h"
#include "source/core/image.h"
#include "source/bmp/bmp_reader.h"
#include "source/bmp/bmp_writer.h"

int main(int argc, char** argv) {
    try {
        ArgsParser parser(argc, argv);
        Image image = ReadBMP(parser.GetInputPath());
        FilterPipeline pipeline = parser.BuildPipeline();
        pipeline.Apply(image);
        WriteBMP(parser.GetOutputPath(), image);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
