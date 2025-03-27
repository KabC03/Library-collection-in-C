


#include <stdio.h>
#include "bitmap.h"
#include "hashmap.h"
#include "list.h"
#include "matrix.h"
#include "priority_queue.h"
#include "wav.h"
#include "bignum.h"
#include "graph_list.h"


void mul(void *dest, void *m1, void *m2) {

    *((int*)dest) = *((int*)m1) * *((int*)m2);

    return;
}




int main(void) {

    List l1;
    List l2;

    list_init(&l1, sizeof(int));
    list_init(&l2, sizeof(int));

    for(int i = 0; i < 10; i++) {
        list_append(&l1, &i);
        list_append(&l2, &i);
    }

    list_transfer(&l1, &l2);

    list_disp(&l1, list_print_integer);
    list_disp(&l2, list_print_integer);

    return 0;
}




