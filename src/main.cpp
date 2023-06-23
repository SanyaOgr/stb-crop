#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers" 
#pragma GCC diagnostic ignored "-Wunused-parameter"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_JPEG
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#pragma GCC diagnostic pop

#include <iostream>
#include <unistd.h>
#include <cstring>

template<class T>
struct Rect
{
    T left;
    T top;
    T width;
    T height;
};

void printUsageStr()
{
    std::cout << "Usage: -s [source image path] -d [destination image path] -q [quality] -- [x1] [y1] [x2] [y2]\n";
}

Rect<size_t> mapToPixels(Rect<float> percents, size_t width, size_t height)
{
    Rect<size_t> ret{};
    ret.left = percents.left * width / 100.f;
    ret.top = percents.top * height / 100.f;
    ret.width = percents.width * width / 100.f;
    ret.height = percents.height * height / 100.f;
    return ret;
}

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        printUsageStr();
        return 0;
    }

    const char* srcPath{};
    const char* dstPath{};
    Rect<float> rectInPercents{};
    Rect<size_t> rectInPixels{};
    int quality = 0;

    int opt = 0;
    while((opt = getopt(argc, argv, "q:s:d:")) != -1)
    {
        switch(opt)
        {
            case 'q':
                quality = atoi(optarg);
                break;
            
            case 's':
                srcPath = optarg;
                break;
            
            case 'd':
                dstPath = optarg;
                break;

            default:
                printUsageStr();
                return 1;
        }
    }

    if(optind < 8 || optind + 4 > argc)
    {
        printUsageStr();
        return 1;
    }

    rectInPercents.left = atof(argv[optind]);
    rectInPercents.top = atof(argv[optind + 1]);
    rectInPercents.width = atof(argv[optind + 2]) - rectInPercents.left;
    rectInPercents.height = atof(argv[optind + 3]) - rectInPercents.top;

    int srcWidth = 0;
    int srcHeight = 0;
    int channels = 0;
    stbi_uc* srcImg = stbi_load(srcPath, &srcWidth, &srcHeight, &channels, 0);
    if(srcImg == nullptr)
    {
        std::cout << "Not read image: " << srcPath << "\n";
        return 2;
    }

    rectInPixels = mapToPixels(rectInPercents, srcWidth, srcHeight);
    
    stbi_uc* dstImg = new stbi_uc[rectInPixels.width * rectInPixels.height * channels];
    
    for(size_t y = 0; y < rectInPixels.height; ++y)
    {
        size_t absY = rectInPixels.top + y;
        size_t absX = rectInPixels.left;
        size_t srcOffset = (absY * srcWidth + absX) * channels;
        size_t dstOffset = y * rectInPixels.width * channels;
        std::memcpy(dstImg + dstOffset, srcImg + srcOffset, rectInPixels.width * channels);
    }

    if(!stbi_write_jpg(dstPath, rectInPixels.width, rectInPixels.height, channels, dstImg, quality))
    {
        std::cout << "Not write image: " << dstPath << "\n";
        return 2;
    }

    stbi_image_free(srcImg);
    delete[] dstImg;
    return 0;
}