//A basic bitmap library in C

#ifndef BITMAP_H 
#define BITMAP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "vector.h"


#pragma pack(push, 1)

typedef struct BMPHeader {

    uint16_t fileType;
    uint32_t fileSize;
    uint16_t res1;
    uint16_t res2;
    uint32_t dataOffset;

} BMPHeader;


typedef struct BMPMetadata {

    uint32_t headerSize;
    int32_t imageWidth;
    int32_t imageHeight;
    uint16_t numberOfPlanes;
    uint16_t bitsPerPixel;
    uint32_t compressionType;
    uint32_t imageFileSize;
    int32_t xRes;
    int32_t yRes;
    uint32_t numberOfColours;
    uint32_t importantColours;

} BMPMetadata;


#pragma pack(pop)



#endif // BITMAP_H





