/**
* Implementation of a threaded program that will load an image and then apply a filter to it and save the changes
* made as a new image.
*
* Completion time: 11 hours
*
* @author Tristan Crawford, Suthar
* @version CLion 2023.2
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include "BmpProcessor.h"

#define BMP_HEADER_SIZE 14
#define BMP_DIB_HEADER_SIZE 40
#define MAXIMUM_IMAGE_SIZE 4096
#define THREAD_COUNT 4

int imgWidth;
int imgHeight;

void swissCheeseImg(struct Pixel** pArr) {

    colorShiftPixels(pArr, imgWidth, imgHeight, 0, 60, 60);

    for (int x = 0; x < imgHeight; x++) {
        for (int y = 0; y < imgWidth; y++) {
            if (pArr[x][y].pix == 1) {
                pArr[x][y].pixBlue = 0;
                pArr[x][y].pixGreen = 0;
                pArr[x][y].pixRed = 0;
            }
        }
    }
}
void imgHole(struct Pixel** pArr, int width, int height) {
    int avgRadius = 0;
    int holeLength = 0;
    if (width < height) {
        avgRadius = width * .08;
        holeLength = width;
    }
    else {
        avgRadius = height * .08;
        holeLength = height;
    }
    srand(time(NULL));

    int medHoleNum = avgRadius / 2;
    int mRadius = avgRadius;
    int smallHoleNum = (avgRadius - medHoleNum) / 2;
    int sRadius = avgRadius / 3;
    int lRadius = avgRadius * 2;

    printf("%d", mRadius);

    int** imgCenter = (int**)malloc(sizeof(int*) * avgRadius);
    for (int x = 0; x < avgRadius; x++) {
        imgCenter[x] = (int*)malloc(sizeof(int) * 2);
    }

    for (int x = 0; x < avgRadius; x++) {
        imgCenter[x][0] = rand() % width;
        imgCenter[x][1] = rand() % height;
    }

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            for (int z = 0; z < smallHoleNum; z++) {
                if (sqrt((x - imgCenter[z][1]) * (x - imgCenter[z][1]) + (y - imgCenter[z][0]) * (y - imgCenter[z][0])) < sRadius) {
                    pArr[x][y].pix = 1;
                    break;
                }
            }

            for (int z = smallHoleNum; z < smallHoleNum + medHoleNum; z++) {
                if (sqrt((x - imgCenter[z][1]) * (x - imgCenter[z][1]) + (y - imgCenter[z][0]) * (y - imgCenter[z][0])) < mRadius) {
                    pArr[x][y].pix = 1;
                    break;
                }
            }

            for (int z = smallHoleNum + medHoleNum; z < avgRadius; z++) {
                if (sqrt((x - imgCenter[z][1]) * (x - imgCenter[z][1]) + (y - imgCenter[z][0]) * (y - imgCenter[z][0])) < lRadius) {
                    pArr[x][y].pix = 1;
                    break;
                }
            }
        }
    }

    for (int x = 0; x < avgRadius; x++) {
        free(imgCenter[x]);
    }
    free(imgCenter);
}

void boxblur(void* arg) {
    struct Pixel** pArr = arg;
    int firstColor = 0;
    int lastColor = imgWidth;

    for (int x = 0; x < imgHeight; x++) {
        for (int y = firstColor; y < lastColor; y++) {

            int p1Red = 0;
            int p1Green = 0;
            int p1Blue = 0;
            int p2Red = 0;
            int p2Green = 0;
            int p2Blue = 0;
            int p3Red = 0;
            int p3Green = 0;
            int p3Blue = 0;
            int p4Red = 0;
            int p4Green = 0;
            int p4Blue = 0;
            int p5Red = 0;
            int p5Green = 0;
            int p5Blue = 0;
            int p6Red = 0;
            int p6Green = 0;
            int p6Blue = 0;
            int p7Red = 0;
            int p7Green = 0;
            int p7Blue = 0;
            int p8Red = 0;
            int p8Green = 0;
            int p8Blue = 0;
            int pixCount = 1;

            if (x - 1 >= 0 && y - 1 >= 0) {
                p1Red = pArr[x - 1][y - 1].pixRed;
                p1Green = pArr[x - 1][y - 1].pixGreen;
                p1Blue = pArr[x - 1][y - 1].pixBlue;
                pixCount++;
            }
            if (x - 1 >= 0 && y >= 0) {
                p2Red = pArr[x - 1][y].pixRed;
                p2Green = pArr[x - 1][y].pixGreen;
                p2Blue = pArr[x - 1][y].pixBlue;
                pixCount++;
            }
            if (x - 1 >= 0 && y + 1 < imgWidth) {
                p3Red = pArr[x - 1][y + 1].pixRed;
                p3Green = pArr[x - 1][y + 1].pixGreen;
                p3Blue = pArr[x - 1][y + 1].pixBlue;
                pixCount++;
            }
            if (x >= 0 && y - 1 >= 0) {
                p4Red = pArr[x][y - 1].pixRed;
                p4Green = pArr[x][y - 1].pixGreen;
                p4Blue = pArr[x][y - 1].pixBlue;
                pixCount++;
            }
            if (x >= 0 && y + 1 < imgWidth) {
                p5Red = pArr[x][y + 1].pixRed;
                p5Green = pArr[x][y + 1].pixGreen;
                p5Blue = pArr[x][y + 1].pixBlue;
                pixCount++;
            }
            if (x + 1 < imgHeight && y - 1 >= 0) {
                p6Red = pArr[x + 1][y - 1].pixRed;
                p6Green = pArr[x + 1][y - 1].pixGreen;
                p6Blue = pArr[x + 1][y - 1].pixBlue;
                pixCount++;
            }
            if (x + 1 < imgHeight && y >= 0) {
                p7Red = pArr[x + 1][y].pixRed;
                p7Green = pArr[x + 1][y].pixGreen;
                p7Blue = pArr[x + 1][y].pixBlue;
                pixCount++;
            }
            if (x + 1 < imgHeight && y + 1 < imgWidth) {
                p8Red = pArr[x + 1][y + 1].pixRed;
                p8Green = pArr[x + 1][y + 1].pixGreen;
                p8Blue = pArr[x + 1][y + 1].pixBlue;
                pixCount++;
            }
            pArr[x][y].pixRed = (p1Red + p2Red + p3Red + p4Red + p5Red + p6Red + p7Red + p8Red + pArr[x][y].pixRed ) / pixCount;
            pArr[x][y].pixGreen = (p1Green + p2Green + p3Green + p4Green + p5Green + p6Green + p7Green + p8Green + pArr[x][y].pixGreen) / pixCount;
            pArr[x][y].pixBlue = (p1Blue + p2Blue + p3Blue + p4Blue + p5Blue + p6Blue + p7Blue + p8Blue + pArr[x][y].pixBlue) / pixCount;
        }
    }
}

void main(int argc, char* argv[]) {

    int type = 0;
    char* inputFile = "";
    char* outputFile = "";

    for(int x = 0; x < argc; x++){
        if(strcmp(argv[x], "-x") == 0)
            inputFile = argv[x + 1];
        else if(strcmp(argv[x], "-o") == 0)
            outputFile = argv[x + 1];
        else if(strcmp(argv[x], "b") == 0)
            type = 1;
    }

    FILE* readfile = fopen(inputFile, "rb");

    struct BMP_Header* bmp_header;
    bmp_header = (struct BMP_Header*)malloc(sizeof(struct BMP_Header));
    struct DIB_Header* dib_header;
    dib_header = (struct DIB_Header*)malloc(sizeof(struct DIB_Header));

    readBMPHeader(readfile, bmp_header);
    readDIBHeader(readfile, dib_header);

    struct Pixel** pArr = (struct Pixel**)malloc(sizeof(struct Pixel*) * dib_header->height);
    for (int x = 0; x < dib_header->height; x++) {
        pArr[x] = (struct Pixel*)malloc(sizeof(struct Pixel) * dib_header->width);
    }

    readPixelsBMP(readfile, pArr, dib_header->width, dib_header->height);

    pthread_t threads[THREAD_COUNT];
    int threads_result[THREAD_COUNT];

    int divWidth = dib_header->width / THREAD_COUNT;
    int numRemain = dib_header->width % THREAD_COUNT;

    imgHeight = dib_header->height;
    imgWidth = divWidth + numRemain;

    if(type == 1){
        struct Pixel*** pArrDivide = (struct Pixel***)malloc(sizeof(struct Pixel**) * THREAD_COUNT);
        for (int x = 0; x < THREAD_COUNT; x++) {
            pArrDivide[x] = (struct Pixel**)malloc(sizeof(struct Pixel*) * dib_header->height);
            for (int y = 0; y < dib_header->height; y++) {
                pArrDivide[x][y] = (struct Pixel*)malloc(sizeof(struct Pixel) * (divWidth + numRemain + 1));
            }
        }

        for (int x = 0; x < THREAD_COUNT; x++) {
            if (x == 0) {
                for (int y = 0; y < dib_header->height; y++) {
                    for (int z = 0; z < divWidth + 1; z++) {
                        pArrDivide[x][y][z] = pArr[y][z];
                    }
                }
            }
            else if (x == THREAD_COUNT - 1) {
                for (int y = 0; y < dib_header->height; y++) {
                    for (int z = 0; z < divWidth + 1 + numRemain; z++) {
                        pArrDivide[x][y][z] = pArr[y][z + x * divWidth - 1];
                    }
                }
            }
            else {
                for (int y = 0; y < dib_header->height; y++) {
                    for (int z = 0; z < divWidth + 2; z++) {
                        pArrDivide[x][y][z] = pArr[y][z + x * divWidth - 1];
                    }
                }
            }
        }

        for (int x = 0; x < THREAD_COUNT; x++) {

            threads_result[x] = pthread_create(&threads[x], NULL, boxblur, pArrDivide[x]);

            if (threads_result[x] != 0) {

                printf("Thread build FAIL: thread %d\n.", x);
            }
            else {
                printf("Thread build SUCCESS: thread %d\n", x);
            }
        }
        void* returnVal;
        for (int x = 0; x < THREAD_COUNT; x++) {
            pthread_join(threads[x], &returnVal);
        }

        for (int x = 0; x < THREAD_COUNT; x++) {
            if (x == 0) {
                for (int y = 0; y < dib_header->height; y++) {
                    for (int z = 0; z < divWidth + 1; z++) {
                        pArr[y][z] = pArrDivide[x][y][z];
                    }
                }
            }
            else if (x == THREAD_COUNT - 1) {
                for (int y = 0; y < dib_header->height; y++) {
                    for (int z = 0; z < divWidth + numRemain; z++) {
                        pArr[y][z + x * divWidth] = pArrDivide[x][y][z + 1];
                    }
                }
            }
            else {
                for (int y = 0; y < dib_header->height; y++) {
                    for (int z = 0; z < divWidth; z++) {
                        pArr[y][z + x * divWidth] = pArrDivide[x][y][z + 1];
                    }
                }
            }
        }

    } else {

        imgHole(pArr, dib_header->width, dib_header->height);

        struct Pixel*** pArrDiv = (struct Pixel***)malloc(sizeof(struct Pixel**) * THREAD_COUNT);
        for (int x = 0; x < THREAD_COUNT; x++) {
            pArrDiv[x] = (struct Pixel**)malloc(sizeof(struct Pixel*) * dib_header->height);
            for (int y = 0; y < dib_header->height; y++) {
                pArrDiv[x][y] = (struct Pixel*)malloc(sizeof(struct Pixel) * (divWidth + numRemain));
            }
        }

        for (int x = 0; x < THREAD_COUNT; x++) {
            if (x == THREAD_COUNT - 1) {
                for (int y = 0; y < dib_header->height; y++) {
                    for (int z = 0; z < divWidth + numRemain; z++) {
                        pArrDiv[x][y][z] = pArr[y][z + x * divWidth];
                    }
                }
            }
            else {
                for (int y = 0; y < dib_header->height; y++) {
                    for (int z = 0; z < divWidth; z++) {
                        pArrDiv[x][y][z] = pArr[y][z + x * divWidth];
                    }
                }
            }
        }

        for (int x = 0; x < THREAD_COUNT; x++) {
            threads_result[x] = pthread_create(&threads[x], NULL, swissCheeseImg, pArrDiv[x]);
            if (threads_result[x] != 0) {
                printf("Thread building failed: thread %d\n.", x);

            } else {
                printf("Thread building was a success: thread %d\n", x);
            }
        }

        void* return_value;
        for (int x = 0; x < THREAD_COUNT; x++) {
            pthread_join(threads[x], &return_value);
        }

        for (int x = 0; x < THREAD_COUNT; x++) {
            if (x == THREAD_COUNT - 1) {
                for (int y = 0; y < dib_header->height; y++) {
                    for (int z = 0; z < divWidth + numRemain; z++) {
                        pArr[y][z + x * divWidth] = pArrDiv[x][y][z];
                    }
                }
            }
            else {
                for (int y = 0; y < dib_header->height; y++) {
                    for (int z = 0; z < divWidth; z++) {
                        pArr[y][z + x * divWidth] = pArrDiv[x][y][z];
                    }
                }
            }
        }
    }

    FILE* writefile = fopen(outputFile, "wb");
    writeBMPHeader(writefile, bmp_header);
    writeDIBHeader(writefile, dib_header);
    writePixelsBMP(writefile, pArr, dib_header->width, dib_header->height);
    fclose(writefile);
    for (int x = 0; x < dib_header->height; x++) {
        free(pArr[x]);
    }
    free(pArr);
    free(dib_header);
    free(bmp_header);

    printf("%s has completed.\n", outputFile);
}
