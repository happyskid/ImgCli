#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "colors.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Missing 1 argument (file path)" << std::endl;
        return 1;
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string density = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:, ^ `'.";
    int k,w,h,c,densityLen;
    unsigned char* img = stbi_load(argv[1], &w, &h, &c, 3);
    SetConsoleTextAttribute(hConsole, 11);

    if (img == NULL)
    {
        std::cout << "Failed to load image";
        return 1;
    }

    if (argc > 2)
    {
        std::ifstream densityFile (argv[2]);
        if (densityFile.is_open())
        {
            densityFile >> density;
            densityFile.close();
        }
        else
        {
            std::cout << "Unable to open file" << std::endl;
        }
    }

    densityLen = density.size() - 1;

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