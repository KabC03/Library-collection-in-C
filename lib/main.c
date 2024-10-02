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
    Node *node = list_delete_index(&l1,0);
    printf("%d\n", *(int*)(node->data));
    free(node);


    list_disp(&l1, list_print_integer);

    list_destroy(&l1);

    return 0;
}




