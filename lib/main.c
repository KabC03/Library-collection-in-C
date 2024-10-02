#include "list.h"

int main(void) {

    List l1;
    list_init(&l1, sizeof(int));
    
    for(int i = 0; i < 1000000; i++) {
        list_append(&l1, &i);
    }

    list_disp(&l1, list_print_integer);
    printf("%d\n", *(int*)(list_peak_back(&l1)->data));


    return 0;
}




