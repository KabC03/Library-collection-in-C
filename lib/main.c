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

    int data = 100;
    Vector in;
    Vector out;
    vector_init(&out, sizeof(size_t), 1);
    vector_init(&in, sizeof(size_t), 1);

    size_t dataArr[] = {100};


    if(graph_list_insert(&g1, &in, &out, &data, 100) == false) {
        printf("Insert failed\n");
    }
    data = 1;

    vector_fill(&in, dataArr);
    vector_fill(&out, dataArr);
    if(graph_list_insert(&g1, &in, &out, &data, 10) == false) {
        printf("Insert failed\n");
    }

    int *ptr = graph_list_find(&g1, 10);
    if(ptr == NULL) {
        printf("Not found\n");
    } else {
        printf("Found %d\n", *ptr);
    }
    graph_list_disp(&g1, graph_list_print_integer);

    return 0;
}




