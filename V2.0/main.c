#include "vector.h"


void vec_print(void *ptr) {

    if(ptr == NULL) {
        return;
    } else {
        printf("%d, ", *(int*)ptr);
    }
    return;
}


int main(void) {

    Vector v1;



    vector_disp(&v1, vec_print);

    return 0;
}


