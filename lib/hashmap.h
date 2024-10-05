//6 October 2024
#ifndef DYNAMIC_HASHMAP_H 
#define DYNAMIC_HASHMAP_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "vector.h"

typedef struct Entry {

    void *key;
    size_t keySize;

    void *value;
    size_t valueSize;

    struct Entry *next;

} Entry;
typedef struct DynamicHashmap {

    Vector entry;

} DynamicHashmap;



size_t hashmap_djb2(uint8_t *input, size_t size);



#endif 



      
      
      
      