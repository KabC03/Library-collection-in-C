#include "bitmap.h"

int main(void) {

    Bitmap bitmap;
    FILE *fptr = fopen("./data/test.bmp", "rb");
    if(fptr == NULL) {
        printf("File not located\n");
        return -1;
    }


    if(!bitmap_init(fptr, &bitmap)) {
        printf("Init failed\n");
        return -1;
    }

    vector_disp(&(bitmap.data), vector_print_uint8_t);


    return 0;
}




