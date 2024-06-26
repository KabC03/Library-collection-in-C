#include "Heap allocator.h"




/**
 * heap_initialise 
 * ===============================================
 * Brief: Initialise a heap 
 * 
 * Param:  *heap - Heap of interest
 *         size - Size of the pool 
 * 
 * Return: T/F depending on if initialisation was successful 
 * 
 */
bool heap_initialise(Heap *const heap, size_t size) {

    if(heap == NULL || size == 0) {
        return false;
    } else {


    }

    return true;
}



/**
 * heap_allocate
 * ===============================================
 * Brief: Request a block of memory 
 * 
 * Param: size - Size of the block
 *        *heap - Heap of interest 
 * 
 * Return: void* - Pointer to the new block 
 * 
 */
void *heap_allocate(size_t size, const Heap *const heap) {

    if(size == 0 || heap == NULL) {
        return NULL;
    } else {


    }


}



/**
 * heap_free 
 * ===============================================
 * Brief: Free a block of memory
 * 
 * Param: *ptr - ptr to block of interest 
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool heap_free(void *ptr) {

    if(ptr == NULL) {
        return false;
    } else {

    }

    return true;    
}













