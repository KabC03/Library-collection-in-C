//Custom malloc and free function

#ifndef HEAP_ALLOCATOR_H 
#define HEAP_ALLOCATOR_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>


typedef struct FreeMemoryNode FreeMemoryNode;

typedef struct Heap { //Do this to allow for multiple heaps

    size_t numPages;
    struct FreeMemoryNode *memoryNode; //A memory node contained within the heap

} Heap;



bool heap_initialise(Heap *const heap, size_t size);
void *heap_allocate(size_t size, const Heap *const heap);
bool heap_free(void *ptr);
bool heap_destroy(Heap *const heap);

#endif // HEAP_ALLOCATOR_H


