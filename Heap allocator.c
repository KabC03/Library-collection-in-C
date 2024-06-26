#include "Heap allocator.h"


struct FreeMemoryNode {  //Stored next to the free node

    size_t blockSize;            //Size of the block
    struct FreeMemoryNode *next; //Next block

};


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


        //Ceil the page multiple
        size_t systemPageSize = sysconf(_SC_PAGESIZE);
        size_t pageSize = 0;
        if(size % systemPageSize == 0) {

            pageSize = size / systemPageSize;
        } else {
            pageSize = (size / systemPageSize) + 1;
        }


        //Request memory
        void *newMemory = mmap(NULL, pageSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if(newMemory == NULL) {
            return false;
        }
        heap->totalSize = pageSize;
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

    return NULL; //TEMPORARY
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













