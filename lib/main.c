#include "list.h"

int main(void) {

    List l1;
    if(!list_init(&l1, sizeof(int))) {
        printf("Init failed\n");
        return 1;
    }

    for(int i = 0; i < 1; i++) {
        list_append(&l1, &i);
    }

    list_disp(&l1, list_print_integer);
    printf("Dequeue: %d\n", *(int*)list_dequeue(&l1)->data);
    list_disp(&l1, list_print_integer);

    list_destroy(&l1);

    return 0;
}




