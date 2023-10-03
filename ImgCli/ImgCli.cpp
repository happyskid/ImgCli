#include <iostream>
#include <string>
#include <windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "colors.hpp"

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string density = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:, ^ `'.";
    int k,w,h,c,densityLen;
    unsigned char* img = stbi_load("./test.png", &w, &h, &c, 3);
    densityLen = density.size()-1;

    if (img == NULL)
    {
        std::cout << "Failed to load image";
        return 1;
    }

    std::cout << "Loaded: " << w << "x" << h << "px image with " << c << " channels" << std::endl << "Press any key";
    std::cin.get();

    for (int j = 0; j < h; j++) 
    {
        for (int i = 0; i < w; i++)
        {
            unsigned char* pixelOffset = img + (i + w * j) * (unsigned)c;
            rgb color_rgb = {
                (double)pixelOffset[0],
                (double)pixelOffset[1],
                (double)pixelOffset[2]
            };
            hsv color_hsv = rgb2hsv(color_rgb);
            double indx = (((color_rgb.r+color_rgb.g+color_rgb.b)/3)/255)*densityLen;
            char ascii = density[(int)indx];
            SetConsoleTextAttribute(hConsole, consoleColor(color_hsv));
            std::cout << ascii;
        }
        std::cout << std::endl;
    }

    std::cin.get();
    stbi_image_free(img);
    return 0;
}