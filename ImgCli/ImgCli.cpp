#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_resize.h"
#include "colors.hpp"

int main(int argc, char *argv[])
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    if (argc < 2)
    {
        std::cout << "Missing 1 argument (file path)\n";
        return 1;
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string density = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:, ^ `'.";
    int k,w,h,c,densityLen;
    unsigned int bytePerPixel = 4;
    unsigned char* img = stbi_load(argv[1], &w, &h, &c, bytePerPixel);
    SetConsoleTextAttribute(hConsole, 11);

    if (img == NULL)
    {
        std::cout << "Failed to load image\n";
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
            std::cout << "Unable to open file\n";
        }
    }

    densityLen = density.size() - 1;

    std::cout << "Loaded: " << w << "x" << h << "px image with " << c << " channels\n" << "Press any key\n";
    std::cin.get();

    for (int j = 0; j < h; j++) 
    {
        for (int i = 0; i < w; i++)
        {
            unsigned char* pixelOffset = img + (i + w * j) * bytePerPixel;
            if (c > 3 && pixelOffset[3] < 20)
            {
                SetConsoleTextAttribute(hConsole, 0);
                std::cout << " ";
                continue;
            }
            rgb color_rgb = {
                (double)pixelOffset[0],
                (double)pixelOffset[1],
                (double)pixelOffset[2]
            };
            hsv color_hsv = rgb2hsv(color_rgb);
            double indx = (color_hsv.v/255)*densityLen;
            char ascii = density[(int)indx];
            SetConsoleTextAttribute(hConsole, consoleColor(color_hsv));
            std::cout << ascii;
        }
        std::cout << "\n";
    }

    std::cin.get();
    stbi_image_free(img);
    return 0;
}