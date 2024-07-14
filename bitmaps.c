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


        //Read data into a vector
        if(vector_initialise(&(bitmapImageOutput->bitmapData), sizeof(uint8_t) * bitmapImageOutput->bitmapMetadata.bitsPerPixel) == false) {
            return _GENERIC_FAILURE_;
        }


        FILE *addressToWriteTo = bitmapImageOutput->bitmapImagePtr;
        for(size_t i = 0; i < bitmapImageOutput->bitmapMetadata.imageWidth * bitmapImageOutput->bitmapMetadata.imageHeight; i++) {


            //WARNING: THIS PART IS WRONG - REDO IT
            fseek(bitmapImageOutput->bitmapImagePtr, bitmapImageOutput->bitmapHeader.dataOffset + 
            (i*(bitmapImageOutput->bitmapMetadata.bitsPerPixel)), SEEK_SET);



            //Write pixel by pixel 
            if(vector_quick_append(&(bitmapImageOutput->bitmapData), addressToWriteTO, 1) == false) {
                vector_destroy(&(bitmapImageOutput->bitmapData));
                return _GENERIC_FAILURE_;
            }
        }



    }


    return _SUCCESS_;
}



















