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
        heap->numPages = pageSize;
   
        heap->memoryNode->blockSize = heap->numPages;
        heap->memoryNode->next = newMemory;

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


    void *newPtr = NULL;
    if(size == 0 || heap == NULL) {
        return NULL;
    } else {

        //Move through the LL until find a node with a large enough capacity. Break off whats needed then trim the node
        //If no blocks free just return NULL
    }

    return newPtr;
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

        //Decrement ptr by sizeof MemoryNode (to find the metadata node)
        //munmap the next bytes
        //check if next or previous blocks are free
        //if so combine them into their LLs
        //if not just insert the metadata node back into the LL
        

    }

    return true;    
}





/**
 * heap_destroy
 * ===============================================
 * Brief: Destroy a full heap
 * 
 * Param: *ptr - ptr to block of interest 
 * 
 * Return: bool - T/F depending on if initialisation was successful
 * 
 */
bool heap_destroy(Heap *const heap) {

    if(heap == NULL) {
        return false;
    } else {

        size_t systemPageSize = sysconf(_SC_PAGESIZE);
        if(munmap(heap->memoryNode, heap->numPages * systemPageSize) != 0) {
            return false;
        }
        
    }

    return true;    
}













 
