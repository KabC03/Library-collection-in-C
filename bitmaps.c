#include "bitmap.h"

/*
TODO: 
- Enstantiate and destroy a bitmap 
- Load a bmp into a flat vector 
- Greyscale an image
- Draw a line accross an image
- Create a blank image with a background colour
- Export an array and header data to a bitmap
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


        //Read data into a vector - NOTE: CURRENTLY < 8 BIT PIXEL DEPTH NOT SUPPORTED

        size_t bytesPerPixel = (bitmapImageOutput->bitmapMetadata.bitsPerPixel)/sizeof(uint8_t);
        size_t numberOfPixels = (bitmapImageOutput->bitmapMetadata.imageHeight) * (bitmapImageOutput->bitmapMetadata.imageWidth);
        if(vector_initialise(&(bitmapImageOutput->bitmapData), bytesPerPixel) == false) {
            return _GENERIC_FAILURE_;
        }


        //Must use a temp buffer when reading from a file ptr
        void *tempBuffer = malloc(bytesPerPixel * numberOfPixels);
        if(tempBuffer == NULL) {
            return _MEMORY_ALLOCATION_FAILURE_;
        }
        fseek(bitmapImageOutput->bitmapImagePtr, bitmapImageOutput->bitmapHeader.dataOffset, SEEK_SET);
        fread(tempBuffer, bytesPerPixel, numberOfPixels, bitmapImageOutput->bitmapImagePtr);
    


        //Write numberOfPixels from tempBuffer
        if(vector_quick_append(&(bitmapImageOutput->bitmapData), tempBuffer, numberOfPixels) == false) {
            return _GENERIC_FAILURE_;
        }

    
        free(tempBuffer);
    }


    return _SUCCESS_;
}












