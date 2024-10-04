/**
*
*
* Completion time: 11 hours
*
* @author Tristan Crawford, Suthar
* @version CLion 2023.2
*/

#include "PixelProcessor.h"

void colorShiftPixels(struct Pixel** pArr, int width, int height, int rShift, int gShift, int bShift){
    for(int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            if (pArr[x][y].pixRed + rShift > 255) {
                pArr[x][y].pixRed = 255;
            }
            else if (pArr[x][y].pixRed + rShift < 0) {
                pArr[x][y].pixRed = 0;
            }
            else {
                pArr[x][y].pixRed += rShift;
            }
            if (pArr[x][y].pixGreen + gShift > 255) {
                pArr[x][y].pixGreen = 255;
            }
            else if (pArr[x][y].pixGreen + gShift < 0) {
                pArr[x][y].pixGreen = 0;
            }
            else {
                pArr[x][y].pixGreen += gShift;
            }
            if (pArr[x][y].pixBlue + bShift > 255) {
                pArr[x][y].pixBlue = 255;
            }
            else if (pArr[x][y].pixBlue + bShift < 0) {
                pArr[x][y].pixBlue = 0;
            }
            else {
                pArr[x][y].pixBlue += bShift;
            }
        }
    }
}
