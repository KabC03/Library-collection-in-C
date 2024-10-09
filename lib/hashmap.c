#include "hashmap.h"



#define MACRO_MALLOC(numel, size) malloc(numel * size)
#define MACRO_MEMCPY(dest, src, n) memcpy(dest, src, n)
#define MACRO_MEMCMP(arg1, arg2, n) memcmp(arg1, arg2, n)
#define MACRO_FREE(ptr) free(ptr)

typedef struct InternalNode {

    struct InternalNode *next;
    size_t keySize;
    size_t valueSize;

    uint8_t data[]; //Flexible length array containing KEY|DATA

} InternalNode;
typedef struct InternalList {

    struct InternalNode *head;

} InternalList;


//Initialise a list
void internal_list_init(InternalList *internalList) {

    internalList->head = NULL;
    return;
}
//Insert at front, list is unchanged otherwise
void *internal_list_append(InternalList *internalList, void *key, size_t keySize, void *value, size_t valueSize) {

    InternalNode *newNode = MACRO_MALLOC(1, sizeof(InternalNode) + keySize + valueSize); 
    if(newNode == NULL) {
        return NULL;
    }
    MACRO_MEMCPY(&(newNode->data), key, keySize);
    MACRO_MEMCPY((uint8_t*)(&(newNode->data)) + keySize, value, valueSize);

    newNode->keySize = keySize;
    newNode->valueSize = valueSize;

    newNode->next = internalList->head;
    internalList->head = newNode;

    return newNode;
}
//Destroy a list
void internal_list_destroy(InternalList *InternalList) {

    InternalNode *current = InternalList->head;
    InternalNode *temp = InternalList->head;
    while(current != NULL) {
        current = current->next; 
        MACRO_FREE(temp);
        temp = current;
    }

    return;
}





/**
 * @brief :: DJB2 hash of an input stream of bytes 
 *
 * @param :: *input :: Input to be hashed 
 * @param :: inputSize :: Size of the input 
 * @param :: buckets :: Number of buckets in the map 
 * 
 * @return :: size_t :: Hash output 
 */
size_t hashmap_djb2(uint8_t *input, size_t inputSize, size_t buckets) {

    size_t hash = 5381;

    for(size_t i = 0; i < inputSize; i++) {
        hash = (hash << 5) + hash + input[i];
    }
    
    return hash % buckets;
}



/**
 * @brief :: Instantiate a hashmap 
 *
 * @param :: *hashmap :: Hashmap of interest 
 * @param :: buckets :: Number of initial buckets 
 * @param :: *hashmap_hash :: Hash function to be used for the map 
 * 
 * @return :: bool :: Indication of if initialisation was successful
 */
bool hashmap_init(Hashmap *hashmap, size_t buckets, 
size_t (*hashmap_hash)(uint8_t *input, size_t keySize, size_t buckets)) {

    hashmap->hashmapFunction = hashmap_hash;
    if(vector_init(&(hashmap->buckets), sizeof(InternalList), buckets) == false) {
        return false;
    }


    InternalList internalList;
    internal_list_init(&internalList);


    for(size_t i = 0; i < buckets; i++) {
        if(vector_append(&(hashmap->buckets), &internalList, 1) == NULL) {
            for(size_t j = 0; j < i; j++) { //Free all previous data

                InternalList *current = vector_access_index(&(hashmap->buckets), j);
                internal_list_destroy(current);
            }
            vector_destroy(&(hashmap->buckets));
            return false;
        }


    } 

    return true;
}




/**
 * @brief :: Destroy a hashmap and associated memory
 *
 * @param :: *hashmap :: Hashmap of interest 
 * 
 * @return :: void 
 */
void hashmap_destroy(Hashmap *hashmap) {

    size_t buckets = hashmap->buckets.capacity;

    for(size_t i = 0; i < buckets; i++) {
        InternalList *current = vector_access_index(&(hashmap->buckets), i);

        internal_list_destroy(current);
    } 
    vector_destroy(&(hashmap->buckets));

    return;
}





/**
 * @brief :: Insert an item to a hashmap. Upon failure the map is unchanged
 *
 * @param :: *hashmap :: Hashmap of interest 
 * @param :: *key :: Hashmap of interest 
 * @param :: keySize :: Hashmap of interest 
 * @param :: *value :: Hashmap of interest 
 * @param :: valueSize :: Hashmap of interest 
 * 
 * @return :: void* :: Pointer to new element in map 
 */
void *hashmap_insert(Hashmap *hashmap, void *key, size_t keySize, void *value, size_t valueSize) {

    size_t bucketIndex = hashmap->hashmapFunction(key, keySize, hashmap->buckets.capacity);
    InternalList *internalList = vector_access_index(&(hashmap->buckets), bucketIndex);

    InternalNode *new = internal_list_append(internalList, key, keySize, value, valueSize);
    if(new == NULL) {
        return false;
    } 

    return ((uint8_t*)(new->data) + keySize);
}










