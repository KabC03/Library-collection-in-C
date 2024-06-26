#include "hashmap.h"

#define DJB2_CONSTANT 5381
#define hashmap_hash_djb2 hashmap_hash //Do this to select the current hash algorithm

/**
 * hashmap_hash_djb2
 * ===============================================
 * Brief: Perform a djb2 hash
 * 
 * Param: *data - Data to hash
 *        dataSize - Size of data to hash
 *        tableSize - Size of the table
 *        *hashOut - Hash output
 * 
 * Return: bool - T/F depending on if freeing was successful
 * 
 */
bool hashmap_hash_djb2(const uint8_t *const data, size_t dataSize, size_t tableSize, size_t *const hashOut) {

    size_t hash= DJB2_CONSTANT;
    if(data == NULL || dataSize == 0 || hashOut == NULL) {
        return false;
    } else {

        for(size_t i = 0; i < dataSize; i++) {
            
            hash = (hash << 5) + hash + data[i];

        }    
        hash %= tableSize;
        *hashOut = hash;
    }
    return true;
}



/*
TODO:

- Initialise hashmap
- Add to hashmap
- Remove from hashmap
- Get value
- Destroy hashmap
*/


/**
 * hashmap_print
 * ===============================================
 * Brief: Print a hashmap of ints - used for debugging
 * 
 * Param: *hashmap - Hashmap of interest 
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool hashmap_print(HashMap *const hashmap) {

    if(hashmap == NULL) {
        return false;
    } else {

        for(int i = 0; i < vector_get_length(&(hashmap->mapListNodes)) + 1; i++) {

            map_LL_print((MapList*)(vector_get_index(&(hashmap->mapListNodes), i)));

        }   
    }

    return true;
}




/**
 * hashmap_initiahlise 
 * ===============================================
 * Brief: Initialise a hash table 
 * 
 * Param: *hashmap - Hashmap of interest 
 *        keySize - Size of keys
 *        initialTableSize - Initial table size
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool hashmap_initialise(HashMap *const hashmap, size_t keySize, size_t valueSize, size_t initialTableSize) {

    if(hashmap == NULL || keySize == 0 || valueSize == 0 || initialTableSize == 0) {
        return false;
    } else {


        hashmap->keySize = keySize;
        hashmap->valueSize = valueSize;
        if(vector_initialise(&(hashmap->mapListNodes), sizeof(MapList)) == false) {
            return false;
        }
        
        if(vector_resize(&(hashmap->mapListNodes), initialTableSize) == false) {
            vector_destroy(&(hashmap->mapListNodes));
            return false;
        }




        MapList newMap;
        if(map_LL_initialise(&newMap) == false) {
            vector_destroy(&(hashmap->mapListNodes));
            return false;
        }

        for(size_t i = 0; i < initialTableSize; i++) {
            //vector_get_index can return null ptr but map_LL will notice it

            if(vector_insert_index(&(hashmap->mapListNodes), i, &newMap) == false) {
                for(int j = 0; j < i; j++) {
                    map_LL_destroy((MapList*)vector_get_index(&(hashmap->mapListNodes), i));
                }
                
                //vector_destroy(&(hashmap->mapListNodes)); //CAUSES ERROR - BUT SHOULD BE HERE TO AVOID LEAKS
                return false;
            }
        
        } 

    }

    return true;
}


/**
 * hashmap_insert
 * ===============================================
 * Brief: Insert into a hashtable 
 * 
 * Param: *hashmap - Hashmap of interest 
 *        *key - key of interest to insert
 *        *value - Corrosponding value to insert
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool hashmap_insert(HashMap *const hashmap, void *const key, void *const value) {

    if(hashmap == NULL || key == NULL || value == NULL) {
        return false;
    } else {

        //Hash the key
        size_t hash = 0;
        size_t tableSize = vector_get_size(&(hashmap->mapListNodes)) + 1; //get_size returns zero based index
        if(tableSize == 0) {
            return false;
        }
        if(hashmap_hash(key, hashmap->keySize, tableSize, &hash) == false) {
            return false;
        }

        if(map_LL_insert_front((MapList*)vector_get_index(&(hashmap->mapListNodes), hash), key, value, hashmap->keySize, hashmap->valueSize) == false) {
            return false;
        }

    }

    return true;
}



/**
 * hashmap_get_value
 * ===============================================
 * Brief: Get a value from a hashmap
 * 
 * Param: *hashmap - Hashmap of interest 
 *        *key - key of interest to insert
 *        *valueOut - Output of hash table 
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool hashmap_get_value(HashMap *const hashmap, void *const key, const void **valueOut) {

    if(hashmap == NULL || key == NULL || valueOut == NULL) {
        return false;
    } else {

        //Hash the key
        size_t hash = 0;
        size_t tableSize = vector_get_size(&(hashmap->mapListNodes)) + 1; //get_size returns zero based index
        
         
        if(tableSize == 0) {
            return false;
        }
        if(hashmap_hash(key, hashmap->keySize, tableSize, &hash) == false) {
            return false;
        }
        
        
        *valueOut = map_LL_get_value((MapList*)vector_get_index(&(hashmap->mapListNodes), hash), key, hashmap->keySize);
    }


 


    return true;
}







