#include <iostream>
#include <string>
#include <windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int getColor(float rgb[3])
{
    int maxIndx = 3;
    int offset = 0;
    for (int i = 0; i < 3; i++)
    {
        if (rgb[i] > rgb[maxIndx])
        {
            maxIndx = i;
            if (rgb[i]>128)
            {
                offset = 8;
            } else 
            {
                offset = 0;
            }
        }
    }

    switch (maxIndx)
    {
        case 0:
            return 4 + offset;
            break;
        case 1:
            return 2 + offset;
            break;
        case 2:
            return 1 + offset;
            break;
        case 3:
            return 15;
            break;
    }
}
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
            float rgb[3] =
            {
                (float)pixelOffset[0],
                (float)pixelOffset[1],
                (float)pixelOffset[2]
            };
            float indx = (((rgb[0]+rgb[1]+rgb[2])/3)/255)*densityLen;
            char ascii = density[(int)indx];
            SetConsoleTextAttribute(hConsole, getColor(rgb));
            std::cout << ascii;
        }
        std::cout << std::endl;
    }

    std::cin.get();
    stbi_image_free(img);
    return 0;
}