#include <stdio.h>
#include "bitmap.h"
#include "hashmap.h"
#include "list.h"


int main(void) {

    Hashmap h1;
    if(!hashmap_init(&h1, 100, hashmap_djb2)) {
        printf("Init failed\n");
    }


    HashmapItem h2;
    int data = 0;
    for(int i = 0; i < 100; i++) {
        data = i;
        h2.key = &data;
        h2.keySize = sizeof(int);
        h2.value = &data;
        h2.valueSize = sizeof(int);

        hashmap_insert(&h1, &h2);
    }

    data = -1;
    h2.key = &data;
    HashmapItem *item = hashmap_search(&h1, &h2);
    printf("Found: %d\n", *(int*)(item->value));


    hashmap_reconfigure(&h1, 5, hashmap_djb2);

    hashmap_destroy(&h1);

    return 0;
}




