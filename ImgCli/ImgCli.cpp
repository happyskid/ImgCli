#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include "ascii_image.hpp"

int main(int argc, char *argv[])
{
    // IO optimization.
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Check if file argument exists
    if (argc < 2)
    {
        std::cout << "Missing 1 argument (file path)\n";
        return 1;
    }

    std::string density = "a";

    // Check if density file argument exists 
    if (argc > 2)
    {
        std::ifstream densityFile(argv[2]);
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

    // Setup output handle and create image instance
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleMode(hConsole, ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    ascii_image image(argv[1], density);
    image.load();

    std::cout << "Loaded: " << image.w << "x" << image.h << "px image with " << image.c << " channels\n" << "Press any key\n";
    std::cin.get();
    std::cout << image.data;

    return 0;
}