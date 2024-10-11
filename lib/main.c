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

    float data1[] = {1,2,3,4,5,6,7,8,9};

    Matrix m1;
    Matrix m2;
    matrix_init(&m1, sizeof(float), 3, 2);
    matrix_init(&m2, sizeof(float), 2,3);
    matrix_fill(&m1, data1);

    matrix_disp(&m1, matrix_print_float);
    matrix_transpose(&m2, &m1);

    printf("\n\n\n");

    matrix_disp(&m2, matrix_print_float);

    return 0;
}




