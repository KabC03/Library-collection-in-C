



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

    Matrix m1;
    matrix_init(&m1, sizeof(float), 3, 3);
    float data[] = {1,2,3,4,5,6,7,8,9};
    matrix_fill(&m1, data);
    matrix_disp(&m1, matrix_print_float);
    exit(0);

    Tree t1;
    tree_init(&t1, sizeof(int), 10);

    for(int i = 0; i < 10; i++) {
        size_t temp = i;
        tree_insert(&t1, i, temp, &i);
    }


    tree_disp(&t1, tree_print_integer);

    return 0;
}

