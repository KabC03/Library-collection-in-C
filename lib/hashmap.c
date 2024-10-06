#include "hashmap.h"



#define MACRO_MALLOC(numel, size) malloc(numel * size)
#define MACRO_MEMCPY(dest, src, n) memcpy(dest, src, n)
#define MACRO_MEMCMP(arg1, arg2, n) memcmp(arg1, arg2, n)
#define MACRO_FREE(ptr) free(ptr)



/**
 * @brief :: DJB2 hash of an input stream of bytes 
 *
 * @param :: *input :: Input to be hashed 
 * @param :: size :: Size of the input 
 * @param :: buckets :: Number of buckets in the map 
 * 
 * @return :: size_t :: Hash output 
 */
size_t hashmap_djb2(uint8_t *input, size_t size, size_t buckets) {

    size_t hash = 5381;

    for(size_t i = 0; i < size; i++) {
        hash = (hash << 5) + hash + input[i];
    }
    
    return hash % buckets;
}

