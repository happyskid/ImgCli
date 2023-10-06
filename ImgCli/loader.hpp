#include <iostream>
#include <windows.h>
#include "colors.hpp"

void saveimg_ascii(unsigned char* img, int w, int h, unsigned int bytePerPixel, std::string density, HANDLE hConsole)
{
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
            double indx = (color_hsv.v / 255) * densityLen;
            char ascii = density[(int)indx];
            SetConsoleTextAttribute(hConsole, consoleColor(color_hsv));
            std::cout << ascii;
        }
        std::cout << "\n";
    }
}