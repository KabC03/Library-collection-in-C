#include <stdio.h>
#include "bitmap.h"
#include "hashmap.h"
#include "list.h"


int main(void) {

    Hashmap h1;
    if(!hashmap_init(&h1, 10, hashmap_djb2)) {
        printf("Init failed\n");
        return 1;
    }

    for(size_t i = 0; i < 50; i++) {
        if(!hashmap_insert(&h1, &i, sizeof(size_t), &i, sizeof(size_t))) {
            printf("Failed to add %zu\n", i);
            return 1;
        }
    }


    size_t data = 20;
    hashmap_remove(&h1, &data, sizeof(size_t));
    if(!hashmap_find(&h1, &data, sizeof(size_t))) {
        printf("Failed to find %zu\n", data);
    }


    hashmap_destroy(&h1);


    return 0;
}




