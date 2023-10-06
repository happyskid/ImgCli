#pragma once

#include <iostream>
#include <string>
#include <windows.h>

class ascii_image {
	public:
		int w, h, c;
		std::string data;
		ascii_image(const char* filePath, std::string density);
		void load();
		void remove();

	private:
		unsigned char* img;
		int densityLen;
		unsigned int bytePerPixel = 4;
		std::string density;
};