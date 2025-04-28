



#include <stdio.h>
#include "bitmap.h"
#include "hashmap.h"
#include "list.h"
#include "matrix.h"
#include "priority_queue.h"
#include "wav.h"
#include "bignum.h"
#include "graph_list.h"
#include "tree.h"


void mul(void *dest, void *m1, void *m2) {

    *((int*)dest) = *((int*)m1) * *((int*)m2);

    return;
}




int main(void) {



    Tree t1;
    tree_init(&t1, sizeof(int), 10);

    for(int i = 1; i < 10; i++) {
        size_t temp = i;
        tree_insert(&t1, i, temp, &i);
    }


    tree_disp(&t1, tree_print_integer);
    tree_delete(&t1, 1);

    return 0;
}

