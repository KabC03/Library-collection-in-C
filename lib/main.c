#include "vector.h"


int main(void) {

    Vector v1;
    vector_initialise(&v1, sizeof(int));


    printf("Length: %zu\n", vector_get_length(&v1));

    int data = 1;
    vector_quick_append(&v1, &data, 1);

    printf("Length: %zu\n", vector_get_length(&v1));

    return 0;
}




