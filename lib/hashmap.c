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

    return hash;
}





/**
 * @brief :: Initialise a hashmap 
 *
 * @param :: *Hashmap :: Hashmap to be initialised 
 * @param :: initialSize :: Initial size of the hashmap 
 * @param :: *hashmapFunction :: Hash function to be used for this hashmap
 * 
 * @return :: bool :: Indication of if hashmap initialisation was successful
 */
bool hashmap_init(Hashmap *hashmap, size_t initialSize, size_t (*hashmapFunction)(uint8_t *input, size_t size, size_t buckets)) {

    if(vector_init(&(hashmap->buckets), sizeof(List), initialSize) == false) {
        return false;
    }
    for(size_t i = 0; i < initialSize; i++) {
        List *list = vector_access_index(&(hashmap->buckets), i);
        if(list_init(list, sizeof(HashmapItem)) == false) {
            vector_destroy(&(hashmap->buckets));
            return false;
        }
    }
    hashmap->hashmapFunction = hashmapFunction;

    return true;
}




/**
 * @brief :: Destroy a hashmap and associated memory 
 *
 * @param :: *hashmap :: Hashmap to be destroyed 
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



/**
 * @brief :: Insert an item into a hashmap 
 *
 * @param :: *hashmap :: Hashmap to be inserted into 
 * @param :: *entryData :: Entry data to insert to hashmap 
 * 
 * @return :: bool :: Indication of if insertion was successful 
 */
bool hashmap_insert(Hashmap *hashmap, HashmapItem *entryData) {

    size_t index = hashmap->hashmapFunction(entryData->key, entryData->keySize, hashmap->buckets.top); 

    List *list = vector_access_index(&(hashmap->buckets), index);
    if(list_push(list, entryData) == false) { //Push to front so resizing is easier
        return false;
    }

    return true;
}





/**
 * @brief :: Delete an item from a hashmap 
 *
 * @param :: *hashmap :: Hashmap of interest 
 * @param :: *entryData :: Entry data to delete from hashmap
 * 
 * @return :: bool :: Indication of if deletion was successful 
 */
bool hashmap_remove(Hashmap *hashmap, HashmapItem *entryData) {

    size_t index = hashmap->hashmapFunction(entryData->key, entryData->keySize, hashmap->buckets.top); 

    List *list = vector_access_index(&(hashmap->buckets), index);
    if(list_find_and_delete(list, entryData) == false) {
        return false;
    }

    return true;
}




/**
 * @brief :: Search a hashmap for an item 
 *
 * @param :: *hashmap :: Hashmap of interest 
 * @param :: *entryData :: Entry data to search hashmap for 
 * 
 * @return :: node* :: Node in hashmap (NULL is returned if the item is not found) 
 */
Node *hashmap_search(Hashmap *hashmap, HashmapItem *entryData) {

    size_t index = hashmap->hashmapFunction(entryData->key, entryData->keySize, hashmap->buckets.top); 

    List *list = vector_access_index(&(hashmap->buckets), index);


    Node *node = list_find(list, entryData);
    if(node == NULL) {
        return NULL;
    }

    return node;
}



/**
 * @brief :: Resize a hashmap. It is modified upon failure
 *
 * @param :: *hashmap :: Hashmap of interest 
 * @param :: size :: New size of the hashmap
 * @param :: *hashmapFunction :: Hash function to be used for this hashmap 
 * 
 * @return :: bool :: Indication of if the hashmap was resized 
 */
bool hashmap_resize(Hashmap *hashmap, size_t size, size_t (*hashmapFunction)(uint8_t *input, size_t size, size_t buckets)) {

    size_t oldSize = hashmap->buckets.top;
    hashmap->hashmapFunction = hashmapFunction;

    //If new size is bigger must expand vector to new size
    if(size > hashmap->buckets.top) {
        if(vector_resize(&(hashmap->buckets), size) == false) {
            return false;
        }
    } 

    for(size_t i = 0; i < oldSize; i++) {
        List *list = vector_access_index(&(hashmap->buckets), i);
        
        
        Node **current = &(list->head);
        Node *temp = list->head;
        while(*current != NULL) {
            HashmapItem *entryData = (HashmapItem*)((*current)->data);

            //Insertion algoritm
            size_t index = hashmap->hashmapFunction(entryData->key, entryData->keySize, size); 
            List *listInsert = vector_access_index(&(hashmap->buckets), index);
            if(list_push(listInsert, entryData) == false) { //Push to front so resizing is easier
                return false;
            }


            //Delete old node

            temp = *current;
            *current = (*current)->next;
            list->size--;
            MACRO_FREE(temp);
        }
    }



    if(size < hashmap->buckets.top) { //If the hashmap has shrunk shrink the vector
        if(vector_resize(&(hashmap->buckets), size) == false) {
            return false;
        }
    }  

    return true;
}














