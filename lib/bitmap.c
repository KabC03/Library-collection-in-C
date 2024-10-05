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



/**
 * @brief :: Reconstruct a bitmap image from data 
 *
 * @param :: *bitmap :: Bitmap image to be reconstructed 
 * @param :: *char :: File name of output bitmap 
 * 
 * @return :: bool :: Indication of if read was successful 
 */
bool bitmap_reconstruct(Bitmap *bitmap, char *name) {

    FILE *output = fopen(name, "wb");
    if(output == NULL) {
        return false;
    }

    if(fwrite(&(bitmap->bitmapFileHeader), sizeof(BitmapFileHeader), 1, output) != 1) {
        goto close;
    }    
    if(fwrite(&(bitmap->bitmapInfoHeader), sizeof(BitmapInfoHeader), 1, output) != 1) {
        goto close;
    }

    if(fwrite(bitmap->data.data, sizeof(uint8_t), bitmap->data.top, output) != bitmap->data.top) {
        goto close;
    }

    if(fclose(output) != 0) {
        return false;
    }

    return true;

close:
    fclose(output);
    return false;
}




/**
 * @brief :: Destroy a bitmap structure 
 *
 * @param :: *bitmap :: Bitmap structure to be destroyed 
 * 
 * @return :: void
 */
void bitmap_destroy(Bitmap *bitmap) {

    vector_destroy(&bitmap->data);

    return;
}





























