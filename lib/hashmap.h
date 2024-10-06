//6 October 2024
#ifndef DYNAMIC_HASHMAP_H 
#define DYNAMIC_HASHMAP_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "vector.h"
#include "list.h"

typedef struct HashmapItem { //This is embedded into a list in list.h

    size_t keySize;
    void *key;

    size_t valueSize;
    void *value;

} HashmapItem;
typedef struct Hashmap {

    size_t (*hashmapFunction)(uint8_t *input, size_t size, size_t buckets); //Hash function
    Vector buckets;

} Hashmap;



#endif 



      
      
      
      