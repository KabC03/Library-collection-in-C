#include "list.h"

int main(void) {

    List l1;
    if(!list_init(&l1, sizeof(int))) {
        printf("Init failed\n");
        return 1;
    }
    int data = 0;


    data = 0;
    if(!list_prepend(&l1, &data)) {
        printf("Failed to prepend\n");
        return 1;
    }
    data = 4;
    if(!list_prepend(&l1, &data)) {
        printf("Failed to prepend\n");
        return 1;
    }
    data = 3;
    if(!list_prepend(&l1, &data)) {
        printf("Failed to prepend\n");
        return 1;
    }



    data = 1;
    if(!list_insert_index(&l1, 0, &data)) {
        printf("Failed to insert\n");
        return 1;
    }

    printf("Item: %d\n", *(int*)list_access_index(&l1, 2));



    list_disp(&l1, list_print_integer);
    list_destroy(&l1);

    return 0;
}




