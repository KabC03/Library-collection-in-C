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

typedef struct Hashmap {

    size_t (*hashmapFunction)(uint8_t *input, size_t size, size_t buckets); //Hash function
    Vector buckets;

} Hashmap;




size_t hashmap_djb2(uint8_t *input, size_t inputSize, size_t buckets);
bool hashmap_init(Hashmap *hashmap, size_t buckets, size_t (*hashmap_hash)(uint8_t *input, size_t keySize, size_t buckets));
void hashmap_destroy(Hashmap *hashmap);
void *hashmap_insert(Hashmap *hashmap, void *key, size_t keySize, void *value, size_t valueSize);
void hashmap_remove(Hashmap *hashmap, void *key, size_t keySize);
void *hashmap_find(Hashmap *hashmap, void *key, size_t keySize);

#endif 



      
      
      
      