#include <stdio.h>
#include "bitmap.h"
#include "hashmap.h"
#include "list.h"


int main(void) {

    List l1;
    list_init(&l1, sizeof(int));

    for(int i = 0; i <= 10000; i++) {
        list_append(&l1, &i);
    }

    int search = 10000;
    if(!list_find_and_delete(&l1, &search)) {
        printf("Not deleted\n");
    }
    Node *data = list_find(&l1, &search);

    if(data == NULL) {
        printf("Not found\n");
    } else {
        printf("Found: %d\n", *(int*)(data->data));
    }


    return 0;
}




