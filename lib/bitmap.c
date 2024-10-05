#include "bitmap.h"


/**
 * @brief :: Read a bitmap file directly into a structure 
 *
 * @param :: *ptr :: Item to be printed
 * @param :: *bitmap :: Bitmap image to be read into
 * 
 * @return :: bool :: Indication of if read was successful 
 */
bool bitmap_init(FILE *fptr, Bitmap *bitmap) {

    if(fread(&(bitmap->bitmapFileHeader), sizeof(BitmapFileHeader), 1, fptr) != 1) {
        return false;
    }
    if(fread(&(bitmap->bitmapInfoHeader), sizeof(BitmapInfoHeader), 1, fptr) != 1) {
        return false;
    }


    size_t dataSize = bitmap->bitmapFileHeader.bfSize - sizeof(BitmapFileHeader) - sizeof(BitmapInfoHeader);
    if(vector_init(&(bitmap->data), sizeof(uint8_t), dataSize) == false) {
        return false;
    }
    if(fseek(fptr, bitmap->bitmapFileHeader.bfOffBits, SEEK_SET) != 0) {
        vector_destroy(&(bitmap->data));
        return false;
    }
    if(fread(bitmap->data.data, dataSize, 1, fptr) != 1) {
        vector_destroy(&(bitmap->data));
        return false;
    }
    bitmap->data.top = dataSize; //Should really replace this with its own vector dedicated function


    return true;
}










































