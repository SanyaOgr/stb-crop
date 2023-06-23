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
#include <string>

template<class T>
struct Rect
{
    T x1;
    T y1;
    T x2;
    T y2;
};

void printUsageStr()
{
    std::cout << "Usage: -s [source image path] -d [destination image path] -q [quality] -- [x1] [y1] [x2] [y2]\n";
}

int main(int argc, char** argv)
{
    std::cout << "--- hello stb-crop ---" << std::endl;

    if(argc == 1)
    {
        printUsageStr();
        return 0;
    }

    std::string srcPath{};
    std::string dstPath{};
    Rect<float> rectInPercents{};
    //Rect<unsigned int> rectInPixels{};
    unsigned int quality = 0;

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

    rectInPercents.x1 = atof(argv[optind]);
    rectInPercents.y1 = atof(argv[optind + 1]);
    rectInPercents.x2 = atof(argv[optind + 2]);
    rectInPercents.y2 = atof(argv[optind + 3]);

    std::cout << "Pount 1: " << rectInPercents.x1 << " " << rectInPercents.y1 << "\n";
    std::cout << "Pount 2: " << rectInPercents.x2 << " " << rectInPercents.y2 << "\n";
    std::cout << "Quality: " << quality << "\n";
    std::cout << "Source: " << srcPath << "\n";
    std::cout << "Destination: " << dstPath << "\n";
    
    return 0;
}