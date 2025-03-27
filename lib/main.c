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

    GraphList g1;
    graph_list_init(&g1, 10, sizeof(int));



    return 0;
}




