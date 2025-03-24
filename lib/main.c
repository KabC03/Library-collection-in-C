#include <stdio.h>
#include "bitmap.h"
#include "hashmap.h"
#include "list.h"
#include "matrix.h"
#include "queue.h"

void mul(void *dest, void *m1, void *m2) {

    *((int*)dest) = *((int*)m1) * *((int*)m2);

    return;
}




int main(void) {

    Queue queue;
    queue_init(&queue, sizeof(int));
    for(int i = 0; i < 10; i++) {
        int j = i;
        if(!queue_enqueue(&queue, &j)) {
            printf("ERROR\n");
            return 1;
        }
    }
    queue_disp(&queue, queue_print_integer);


    return 0;
}




