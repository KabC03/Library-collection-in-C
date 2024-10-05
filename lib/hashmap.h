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

typedef struct EntryData { //This is embedded into a list in list.h

    size_t keySize;
    void *key;

    size_t valueSize;
    void *value;

} EntryData;
typedef struct DynamicHashmap {

    Vector bucket;

} DynamicHashmap;



size_t hashmap_djb2(uint8_t *input, size_t size);



#endif 



      
      
      
      