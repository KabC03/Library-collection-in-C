//6 October 2024
#ifndef DYNAMIC_HASHMAP_H 
#define DYNAMIC_HASHMAP_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "vector.h"

typedef struct Hashmap {

    size_t (*hashmapFunction)(uint8_t *input, size_t size, size_t buckets); //Hash function
    Vector buckets;

} Hashmap;




void hashmap_print_size_t(void *ptr);
void hashmap_print_integer(void *ptr);
void hashmap_print_uint8_t(void *ptr);
void hashmap_print_string(void *ptr);
void hashmap_disp(Hashmap *hashmap, void (print_key)(void *key), void (print_value)(void *value));
size_t hashmap_djb2(uint8_t *input, size_t inputSize, size_t buckets);
bool hashmap_init(Hashmap *hashmap, size_t buckets, size_t (*hashmap_hash)(uint8_t *input, size_t keySize, size_t buckets));
void hashmap_destroy(Hashmap *hashmap);
void *hashmap_insert(Hashmap *hashmap, void *key, size_t keySize, void *value, size_t valueSize);
bool hashmap_remove(Hashmap *hashmap, void *key, size_t keySize);
void *hashmap_set_key(Hashmap *hashmap, void *key, size_t keySize, void *value, size_t valueSize);
void *hashmap_find(Hashmap *hashmap, void *key, size_t keySize);
bool hashmap_rehash(Hashmap *hashmap, size_t buckets, size_t (*hashmap_hash)(uint8_t *input, size_t keySize, size_t buckets));


#endif 



      
      
      
      