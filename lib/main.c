#include <stdio.h>
#include "bitmap.h"
#include "hashmap.h"
#include "list.h"
#include "matrix.h"
#include "priority_queue.h"
#include "wav.h"
#include "bignum.h"


void mul(void *dest, void *m1, void *m2) {

    *((int*)dest) = *((int*)m1) * *((int*)m2);

    return;
}




int main(void) {

    Queue q1;
    Queue q2;
    queue_init(&q1, sizeof(int));
    queue_init(&q2, sizeof(int));

    for(size_t i = 0; i < 10; i++) {
        queue_priority_enqueue(&q1, &i, 9 - i);
    }
    printf("Inserted\n");
    queue_disp(&q1, queue_print_integer);



    for(size_t i = 0; i < 10; i++) {
        queue_priority_enqueue(&q2, &i, i);
    }
    printf("Inserted\n");
    queue_disp(&q2, queue_print_integer);

    int *val = (int*)(queue_dequeue(&q2)->data);
    printf("Value: %d\n", *val);

    val = (int*)(queue_dequeue(&q1)->data);
    printf("Value: %d\n", *val);

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




