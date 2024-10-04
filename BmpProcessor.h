#ifndef BMPPROCESSOR_H
#define BMPPROCESSOR_H

#include <stdio.h>
#include "PixelProcessor.h"
struct BMP_Header {
    char signature[2];
    int size;
    short reserved1;
    short reserved2;
    int offsetPixArray;
};
struct DIB_Header{
    int size;
    int width;
    int height;
    short planes;
    short bitsPerPixel;
    int compress;
    int imgSize;
    int horizontalResolution;
    int vertResolution;
    int numCol;
    int impNumCol;
};
void readBMPHeader(FILE* file, struct BMP_Header* header);

void writeBMPHeader(FILE* file, struct BMP_Header* header);

void readDIBHeader(FILE* file, struct DIB_Header* header);

void writeDIBHeader(FILE* file, struct DIB_Header* header);

void makeBMPHeader(struct BMP_Header* header, int width, int height);

void makeDIBHeader(struct DIB_Header* header, int width, int height);

void readPixelsBMP(FILE* file, struct Pixel** pArr, int width, int height);

void writePixelsBMP(FILE* file, struct Pixel** pArr, int width, int height);

#endif //BMPPROCESSOR_H
