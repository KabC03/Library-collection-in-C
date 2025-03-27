#include <stdio.h>
#include "bitmap.h"
#include "hashmap.h"
#include "list.h"
#include "matrix.h"
#include "queue.h"
#include "wav.h"
#include "bignum.h"


void mul(void *dest, void *m1, void *m2) {

    *((int*)dest) = *((int*)m1) * *((int*)m2);

    return;
}




int main(void) {

    Bignum b1;
    Bignum b2;
    Bignum b3;
    bignum_init(&b1);
    bignum_init(&b2);
    bignum_init(&b3);

    bignum_from_string(&b1, "-11111");
    bignum_from_string(&b2, "-11111");

    bignum_add(&b3, &b1, &b2);

    bignum_print(&b3);

    /*
    FILE *fptr = fopen("output/in.wav", "rb");
    if(!fptr) {
        printf("Cannot read file\n");
        return 1;
    }

    Wav wav2;
    Wav wav;
    wav_init(&wav, fptr);
    wav_init(&wav2, fptr);
   

    wav_append(&wav, &wav2);
    wav_reconstruct(&wav, "output/test.wav");
    fclose(fptr);
    */

    return 0;
}




