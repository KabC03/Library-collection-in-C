#include "vector.h"


void vec_print(void *ptr) {

    if(ptr == NULL) {
        return;
    } else {
        printf("%d, ", *((int*)ptr));
    }
    return;
}


int main(void) {

    Vector v1;

    vector_init(&v1, sizeof(int), 1);



    int data = 1;
    vector_append(&v1, &data, 1);
    int arr[] = {1,2,3,4,5};
    vector_append(&v1, arr, 5);


    vector_disp(&v1, vec_print);

    return 0;
}


