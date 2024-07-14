#include "bitmap.h"
#define BITMAP_FILE_SIGNATURE 0x4D42
#define BITS_PER_BYTE 8
#define PAD_CONSTANT 4
/*
TODO: 
- Enstantiate and destroy a bitmap 
- Load a bmp into a flat vector 
- Greyscale an image
- Draw a line accross an image
- Create a blank image with a background colour
- Export an array and header data to a bitmap

- Currently only supports 24 bit depth - make it support at least 32 and 16 bit depth too
*/




/**
 * bitmap_enstantiate 
 * ===============================================
 * Brief: Enstantiate a bitmap image - must be manually closed before program ends
 * 
 * Param: *bitmapPath - Path to an empty bitmap struct
 *        *bitmapImageOutput - data of interest
 * 
 * Return: bool - T/F depending on if addition was successful
 * 
 */
RETURN_CODE bitmap_enstantiate(char *bitmapPath, BitmapImage *bitmapImageOutput) {

    if(bitmapPath == NULL || bitmapImageOutput == NULL) {
        return _NULL_PTR_PASS_;
    } else {

        FILE *bitmapFptr = fopen(bitmapPath, "rb");
        if(bitmapFptr == NULL) {
            return _FAILED_TO_OPEN_FILE_; 
        }


        //Leave this opened until manually closed
        bitmapImageOutput->bitmapImagePtr = bitmapFptr;

        //Read header
        if(fread(&(bitmapImageOutput->bitmapHeader), sizeof(BitmapHeader), 1, bitmapFptr) != 1) {
            return _GENERIC_FAILURE_;
        }
        //Read the metadata
        if(fread(&(bitmapImageOutput->bitmapMetadata), sizeof(BitmapMetadata), 1, bitmapFptr) != 1) {
            return _GENERIC_FAILURE_;
        }


        //Check file is a bitmap
        if(bitmapImageOutput->bitmapHeader.fileType != BITMAP_FILE_SIGNATURE) {
            return _GENERIC_FAILURE_;
        }


        //Read data into a vector - NOTE: CURRENTLY < 8 BIT PIXEL DEPTH NOT SUPPORTED

        size_t bytesPerPixel = (bitmapImageOutput->bitmapMetadata.bitsPerPixel)/BITS_PER_BYTE;
        size_t numberOfPixelsInRow = bitmapImageOutput->bitmapMetadata.imageWidth;
        size_t numberOfPixelsInCol = bitmapImageOutput->bitmapMetadata.imageHeight;

        size_t paddingPerRow = (PAD_CONSTANT - ((bitmapImageOutput->bitmapMetadata.imageWidth * bytesPerPixel) % PAD_CONSTANT)) * PAD_CONSTANT;
        size_t totalPadding = paddingPerRow * numberOfPixelsInCol;



        //Redo this entire section. vector MUST hold pixels
        size_t totalSizeToWriteToBuffer = ((bytesPerPixel * numberOfPixelsInRow) + totalPadding) * numberOfPixelsInCol;


        //Vector holds RAW BYTES
        if(vector_initialise(&(bitmapImageOutput->bitmapData), 1) == false) {
            return _GENERIC_FAILURE_;
        }




        void *tempBuffer = malloc(totalSizeToWriteToBuffer);
        if(tempBuffer == NULL) {
            return _MEMORY_ALLOCATION_FAILURE_;
        }
        if(fseek(bitmapFptr, bitmapImageOutput->bitmapHeader.dataOffset, SEEK_SET) != 0) {
            return _GENERIC_FAILURE_;
        }


        if(fread(tempBuffer, totalSizeToWriteToBuffer, 1, bitmapFptr) != 1) {
            return _GENERIC_FAILURE_;
        }
    


        //Write numberOfPixels from tempBuffer
        if(vector_quick_append(&(bitmapImageOutput->bitmapData), tempBuffer, 1) == false) {
            return _GENERIC_FAILURE_;
        }
        free(tempBuffer);
    }

    return _SUCCESS_;
}











/**
 * bitmap_greyscale 
 * ===============================================
 * Brief: Greyscales a bitmap image 
 * 
 * Param: *bitmapImage - Enstantiated bitmap of interest 
 * 
 * Return: bool - T/F depending on if addition was successful
 * 
 */
RETURN_CODE bitmap_greyscale(BitmapImage *bitmapImage) {

    if(bitmapImage == NULL) {
        return _NULL_PTR_PASS_;
    } else {

        //Will add more depths later
        switch (bitmapImage->bitmapMetadata.bitsPerPixel) {
        case 24:


            //Gray = 0.299 * R + 0.587 * G + 0.144 * B 
            uint8_t red = 0;
            uint8_t blue= 0;
            uint8_t green = 0;

            uint8_t grey = 0;

            uint32_t *pixel = 0;


            size_t numberOfPixels = vector_get_length(&(bitmapImage->bitmapData)) + 1;
            for(size_t i = 0; i < numberOfPixels; i++) {

                pixel = (uint32_t*)vector_get_index(&(bitmapImage->bitmapData), i);
                if(pixel == NULL) {
                    //Unexpected NULL ptr - will make better later
                    return _GENERIC_FAILURE_;
                }

                //WARNING: assuming BGR format
                red = (*pixel) & (0xFF); //255
                green = ((*pixel) & (0xFF00)) >> 8; //65280 then bitshift down 8 bits
                blue = ((*pixel) & (0xFF0000)) >> 16; //Same thing again


                //Set greyscale
                grey = (0.299 * red) + (0.587 * green) + (0.144 * blue);
                uint32_t newPixel = grey;
                newPixel <<= 8;
                newPixel += grey;
                newPixel <<= 8;
                newPixel += grey;



                //Set new greyscale pixel
                if(vector_set_index(&(bitmapImage->bitmapData), i, &newPixel) == false) {
                    return _GENERIC_FAILURE_;
                }

            }
            
            
            break;
        
        default:
            return _GENERIC_FAILURE_;
            break;
        }





    }

    return _SUCCESS_;
}





































