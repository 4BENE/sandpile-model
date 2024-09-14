#include "visualization.h"
#include <fstream>
#include <iostream>
#include <cstdint>
uint8_t count_colors = 3;
const uint8_t file_header_size = 14;
const uint8_t information_header_size = 40;

uint8_t Image::GetColor(int x, int y) const {
    return colors[y*width + x];
}

void Image::SetColor(const uint8_t& color, int x , int y) {
    colors[y*width + x] = color;
}

void Image::Export(const char* path) const{
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);

    unsigned char bmpPad[3] ={0,0,0};
    const int padding_amount = ((4 - (width * count_colors) % 4) % 4);
    const uint64_t file_size = file_header_size + information_header_size + width * height * count_colors + padding_amount * height;

    unsigned char file_header[file_header_size];

    file_header[0] = 'B';
    file_header[1] = 'M';
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;
    file_header[4] = file_size >> 16;
    file_header[5] = file_size >> 24;
    file_header[6] = 0;
    file_header[7] = 0;
    file_header[8] = 0;
    file_header[9] = 0;
    file_header[10] = file_header_size + information_header_size;
    file_header[11] = 0;
    file_header[12] = 0;
    file_header[13] = 0;

    unsigned char information_header[information_header_size];

    information_header[0] = information_header_size;
    information_header[1] = 0;
    information_header[2] = 0;
    information_header[3] = 0;
    information_header[4] = width;
    information_header[5] = width>>8;
    information_header[6] = width>>16;
    information_header[7] = width>>24;
    information_header[8] = height;
    information_header[9] = height>>8;
    information_header[10] = height>>16;
    information_header[11] = height>>24;
    information_header[12] = 1;
    information_header[13] = 0;
    information_header[14] = 24;
    information_header[15] = 0;
    information_header[16] = 0;
    information_header[17] = 0;
    information_header[18] = 0;
    information_header[19] = 0;
    information_header[20] = 0;
    information_header[21] = 0;
    information_header[22] = 0;
    information_header[23] = 0;
    information_header[24] = 0;
    information_header[25] = 0;
    information_header[26] = 0;
    information_header[27] = 0;
    information_header[28] = 0;
    information_header[29] = 0;
    information_header[30] = 0;
    information_header[31] = 0;
    information_header[32] = 5;
    information_header[33] = 0;
    information_header[34] = 0;
    information_header[35] = 0;
    information_header[36] = 5;
    information_header[37] = 0;
    information_header[38] = 0;
    information_header[39] = 0;

    file.write(reinterpret_cast<char*>(file_header),file_header_size);
    file.write(reinterpret_cast<char*>(information_header),information_header_size);

    for(int y = 0 ; y < height ; y++){
        for(int x = 0; x <width; x++) {
            unsigned char red = static_cast<unsigned char>(GetColor(x, y).red );
            unsigned char green = static_cast<unsigned char>(GetColor(x, y).green );
            unsigned char blue = static_cast<unsigned char>(GetColor(x, y).blue );

            unsigned char color[] = {blue , green , red};

            file.write(reinterpret_cast<char*>(color), count_colors);
        }
        file.write(reinterpret_cast<char*>(bmpPad),padding_amount);
    }
   file.close();
}
