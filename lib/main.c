#include "wav.h"

int main(void) {

    Wav one;
    Wav two;

    FILE *src = fopen("./data/tone.wav", "rb");
    FILE *dest = fopen("./data/cavemono.wav", "rb");
    if(!src || !dest) {
        printf("Cannot open\n");
        return 1;
    }

    if(!wav_init(&one, src)) {
        printf("Cannot init src\n");
        return 1;
    }


    if(!wav_init(&two, dest)) {
        printf("Cannot init dest\n");
        return 1;
    }

    
    if(!wav_append(&two, &one)) {
        printf("Cannot append\n");
        return 1;
    }
     

    if(!wav_reconstruct(&two, "./output/reconstructed.wav")) {
        printf("Reconstruct failed\n");
        return 1;
    }


    return 0;
}




