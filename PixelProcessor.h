#ifndef PixelProcessor_H
#define PixelProcessor_H 1
struct Pixel{
    unsigned char pixRed;
    unsigned char pixGreen;
    unsigned char pixBlue;
    unsigned char pix;
};

void colorShiftPixels(struct Pixel** pArr, int width, int height, int rShift, int gShift, int bShift);

#endif //PixelProcessor_H
