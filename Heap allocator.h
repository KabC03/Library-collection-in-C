//Custom malloc and free function

#ifndef HEAP_ALLOCATOR_H 
#define HEAP_ALLOCATOR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>



typedef struct FreeMemoryNode {  //Stored next to the free node

    size_t blockSize;            //Size of the block
    struct FreeMemoryNode *next; //Next block

} FreeMemoryNode;
typedef struct Heap { //Do this to allow for multiple heaps

    size_t totalSize;
    struct FreeMemoryNode *memoryNode; //A memory node contained within the heap

} Heap;


bool heap_initialise(Heap *const heap, size_t size);
void *heap_allocate(size_t size, const Heap *const heap);
bool heap_free(void *ptr);

#endif // HEAP_ALLOCATOR_H


