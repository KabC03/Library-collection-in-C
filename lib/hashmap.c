#include "hashmap.h"



#define MACRO_MALLOC(numel, size) malloc(numel * size)
#define MACRO_MEMCPY(dest, src, n) memcpy(dest, src, n)
#define MACRO_MEMCMP(arg1, arg2, n) memcmp(arg1, arg2, n)
#define MACRO_FREE(ptr) free(ptr)



/**
 * @brief :: DJB2 hash of an input stream of bytes 
 *
 * @param :: *input :: Input to be hashed 
 * @param :: *size :: Size of the input 
 * 
 * @return :: size_t :: Hash output 
 */
size_t hashmap_djb2(uint8_t *input, size_t size) {

    size_t hash = 5381;

    for(size_t i = 0; i < size; i++) {
        hash = (hash << 5) + hash + input[i];
    }

    return hash;
}





/**
 * @brief :: Initialise a hashmap 
 *
 * @param :: *Hashmap :: Hashmap to be initialised 
 * @param :: initialSize :: Initial size of the hashmap 
 * 
 * @return :: bool :: Indication of if hashmap initialisation was successful
 */
bool hashmap_init(Hashmap *hashmap, size_t initialSize) {

    if(vector_init(&(hashmap->buckets), sizeof(List), initialSize) == false) {
        return false;
    }
    for(size_t i = 0; i < initialSize; i++) {
        List *list = vector_access_index(&(hashmap->buckets), i);
        if(list_init(list, sizeof(EntryData)) == false) {
            vector_destroy(&(hashmap->buckets));
            return false;
        }
    }
    return true;
}




/**
 * @brief :: Destroy a hashmap and associated memory 
 *
 * @param :: *Hashmap :: Hashmap to be destroyed 
 * 
 * @return :: void 
 */
void hashmap_destroy(Hashmap *hashmap) {

    size_t buckets = hashmap->buckets.top;
    for(size_t i = 0; i < buckets; i++) {
        List *list = vector_access_index(&(hashmap->buckets), i);
        list_destroy(list);
    }

    vector_destroy(&(hashmap->buckets));

    return;
}































