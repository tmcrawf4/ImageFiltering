/**
*
*
* Completion time: 11 hours
*
* @author Tristan Crawford, Suthar
* @version CLion 2023.2
*/

#include <stdio.h>
#include "PixelProcessor.h"
#include "BmpProcessor.h"

void readBMPHeader(FILE* file, struct BMP_Header* header){

    fread(&header->signature, sizeof(char)*2, 1, file);
    fread(&header->size, sizeof(int), 1, file);
    fread(&header->reserved1, sizeof(short), 1, file);
    fread(&header->reserved2, sizeof(short), 1, file);
    fread(&header->offsetPixArray, sizeof(int), 1, file);
}
void writeBMPHeader(FILE* file, struct BMP_Header* header){

    fwrite(&header->signature, sizeof(char)*2, 1, file);
    fwrite(&header->size, sizeof(int), 1, file);
    fwrite(&header->reserved1, sizeof(short), 1, file);
    fwrite(&header->reserved2, sizeof(short), 1, file);
    fwrite(&header->offsetPixArray, sizeof(int), 1, file);
}

void readDIBHeader(FILE* file, struct DIB_Header* header){

    fread(&header->size, sizeof(int), 1, file);
    fread(&header->width, sizeof(int), 1, file);
    fread(&header->height, sizeof(int), 1, file);
    fread(&header->planes, sizeof(short), 1, file);
    fread(&header->bitsPerPixel, sizeof(short), 1, file);
    fread(&header->compress, sizeof(int), 1, file);
    fread(&header->imgSize, sizeof(int), 1, file);
    fread(&header->horizontalResolution, sizeof(int), 1, file);
    fread(&header->vertResolution, sizeof(int), 1, file);
    fread(&header->numCol, sizeof(int), 1, file);
    fread(&header->impNumCol, sizeof(int), 1, file);
}

void writeDIBHeader(FILE* file, struct DIB_Header* header){

    fwrite(&header->size, sizeof(int), 1, file);
    fwrite(&header->width, sizeof(int), 1, file);
    fwrite(&header->height, sizeof(int), 1, file);
    fwrite(&header->planes, sizeof(short), 1, file);
    fwrite(&header->bitsPerPixel, sizeof(short), 1, file);
    fwrite(&header->compress, sizeof(int), 1, file);
    fwrite(&header->imgSize, sizeof(int), 1, file);
    fwrite(&header->horizontalResolution, sizeof(int), 1, file);
    fwrite(&header->vertResolution, sizeof(int), 1, file);
    fwrite(&header->numCol, sizeof(int), 1, file);
    fwrite(&header->impNumCol, sizeof(int), 1, file);
}

void makeBMPHeader(struct BMP_Header* header, int width, int height){

    header->signature[0] = 'B';
    header->signature[1] = 'M';
    header->reserved1 = 0;
    header->reserved2 = 0;
    header->offsetPixArray = sizeof(struct BMP_Header) + sizeof(struct DIB_Header) - 2;
    header->size = header->offsetPixArray + width * height * 24 / 8;
}

void makeDIBHeader(struct DIB_Header* header, int width, int height){

    header->size = sizeof(struct DIB_Header);
    header->height = height;
    header->width = width;
    header->planes = 1;
    header->bitsPerPixel= 24;
    header->compress = 0;
    header->imgSize = width * height * 24 / 8;
    header->horizontalResolution = 3780;
    header->vertResolution = 3780;
    header->numCol = 0;
    header->impNumCol = 0;
}
void readPixelsBMP(FILE* file, struct Pixel** pArr, int width, int height){

    for(int x = 0; x < height; x++){

        for(int y = 0; y < width; y++){

            fread(&pArr[x][y].pixRed, sizeof(char), 1, file);
            fread(&pArr[x][y].pixBlue, sizeof(char), 1, file);
            fread(&pArr[x][y].pixGreen, sizeof(char), 1, file);
        }
    }
}

void writePixelsBMP(FILE* file, struct Pixel** pArr, int width, int height){

    for(int x = 0; x < height; x++){

        for(int y = 0; y < width; y++){

            fwrite(&pArr[x][y].pixRed, sizeof(char), 1, file);
            fwrite(&pArr[x][y].pixBlue, sizeof(char), 1, file);
            fwrite(&pArr[x][y].pixGreen, sizeof(char), 1, file);
        }
    }
}
