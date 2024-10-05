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
    for(int i = 0; i < 100; i++) {
        h2.key = &i;
        h2.keySize = sizeof(int);
        h2.value = &i;
        h2.valueSize = sizeof(int);

        hashmap_insert(&h1, &h2);
    }




    hashmap_reconfigure(&h1, 5, hashmap_djb2);

    hashmap_destroy(&h1);

    return 0;
}




