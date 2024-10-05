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
typedef struct Hashmap {

    size_t (*hashmapFunction)(uint8_t *input, size_t size, size_t buckets); //Hash function
    Vector buckets;

} Hashmap;



size_t hashmap_djb2(uint8_t *input, size_t size, size_t buckets);
bool hashmap_init(Hashmap *hashmap, size_t initialSize, size_t (*hashmapFunction)(uint8_t *input, size_t size, size_t buckets));
void hashmap_destroy(Hashmap *hashmap);
bool hashmap_insert(Hashmap *hashmap, EntryData *entryData);
bool hashmap_remove(Hashmap *hashmap, EntryData *entryData);
Node *hashmap_search(Hashmap *hashmap, EntryData *entryData);



#endif 



      
      
      
      