#include <stdio.h>
#include "bitmap.h"
#include "hashmap.h"
#include "list.h"


int main(void) {

    Hashmap h1;
    if(!hashmap_init(&h1, 100)) {
        printf("Init failed\n");
    }


    hashmap_destroy(&h1);

    return 0;
}




