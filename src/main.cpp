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

int main()
{
    std::cout << "--- hello stb-crop ---" << std::endl;
    return 0;
}