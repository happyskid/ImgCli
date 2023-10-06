#include "ascii_image.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ascii_image::ascii_image(const char* filePath, std::string density)
{
    ascii_image::density = density;
    densityLen = density.size() - 1;
    img = stbi_load(filePath, &w, &h, &c, bytePerPixel);

    if (img == NULL)
    {
        std::cout << "Image failed to load\n";
        exit(1);
    }
}

void ascii_image::load()
{
    for (int j = 0; j < h; j++)
    {
        for (int i = 0; i < w; i++)
        {
            unsigned char* pixelOffset = img + (i + w * j) * bytePerPixel;
            if (c > 3 && pixelOffset[3] < 20)
            {
                data += " ";
                continue;
            }
            float indx = ((pixelOffset[0] + pixelOffset[1] + pixelOffset[2]) / 3) / 255 * densityLen;
            char ascii = density[(int)indx];
            data += "\x1b[38;2;" + std::to_string(pixelOffset[0]) + ";" + std::to_string(pixelOffset[1]) + ";" + std::to_string(pixelOffset[2]) + "m" + ascii + "\x1b[0m";
        }
        data += "\n";
    }
}

void ascii_image::remove()
{
    stbi_image_free(img);
}