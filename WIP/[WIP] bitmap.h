//6 October
//This library only works with bitmaps > 8 bit colour depth
#ifndef BITMAP_H 
#define BITMAP_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "vector.h"
#include "matrix.h"


/*
TODO:
    - Image from a matrix
    - Draw a line on an image
    - Generate a solid colour image
    - Convolve an image with a matrix
*/



#pragma pack(push, 1)

typedef struct BitmapFileHeader { //Thanks chatGPT
    uint16_t bfType;      // File type; must be "BM"
    uint32_t bfSize;      // Size of the file in bytes
    uint16_t bfReserved1; // Reserved; must be 0
    uint16_t bfReserved2; // Reserved; must be 0
    uint32_t bfOffBits;   // Offset to start of pixel data
} BitmapFileHeader;

typedef struct BitmapInfoHeader {
    uint32_t biSize;          // Size of this header (40 bytes)
    int32_t  biWidth;         // Width of the bitmap in pixels
    int32_t  biHeight;        // Height of the bitmap in pixels
    uint16_t biPlanes;        // Number of color planes (must be 1)
    uint16_t biBitCount;      // Number of bits per pixel
    uint32_t biCompression;    // Compression type
    uint32_t biSizeImage;     // Size of the pixel data
    int32_t  biXPelsPerMeter;  // Horizontal resolution (pixels per meter)
    int32_t  biYPelsPerMeter;  // Vertical resolution (pixels per meter)
    uint32_t biClrUsed;       // Number of colors in the color palette
    uint32_t biClrImportant;   // Important colors; generally ignored
} BitmapInfoHeader;

typedef struct Bitmap {

    BitmapFileHeader bitmapFileHeader;
    BitmapInfoHeader bitmapInfoHeader;
    Vector data;

} Bitmap;


#pragma pack(pop)



bool bitmap_init(FILE *fptr, Bitmap *bitmap);
bool bitmap_reconstruct(Bitmap *bitmap, char *name);
void bitmap_24_convolve(Bitmap *bitmap, Matrix *kernel);
void bitmap_destroy(Bitmap *bitmap);

#endif 





