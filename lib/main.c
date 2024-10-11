#include <stdio.h>
#include "bitmap.h"
#include "hashmap.h"
#include "list.h"
#include "matrix.h"


void mul(void *dest, void *m1, void *m2) {

    *((int*)dest) = *((int*)m1) * *((int*)m2);

    return;
}


int main(void) {

    int data[] = {1,2,3,4};

    Matrix m1;
    Matrix m2;

    matrix_init(&m1, sizeof(int), 2, 2);
    matrix_init(&m2, sizeof(int), 2, 2);

    matrix_fill(&m1, data);
    matrix_fill(&m2, data);

    matrix_multiply(&m2, &m1, &m2, mul);

    matrix_disp(&m2, vector_print_integer);

    return 0;
}




