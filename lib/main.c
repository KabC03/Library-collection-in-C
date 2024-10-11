#include <stdio.h>
#include "bitmap.h"
#include "hashmap.h"
#include "list.h"
#include "matrix.h"


void mul(void *dest, void *m1, void *m2) {

    *((int*)dest) = *((int*)m1) * *((int*)m2);

    return;
}

void prt(void *element) {

    printf("%.0f ", *(float*)(element));
    return;
}



int main(void) {

    float data1[] = {1,2,3,4,5,6};

    Matrix m1;

    matrix_init(&m1, sizeof(float), 3, 2);

    matrix_fill(&m1, data1);

    matrix_disp(&m1, prt);
    matrix_transpose(&m1);

    printf("\n\n\n");

    matrix_disp(&m1, prt);

    return 0;
}




