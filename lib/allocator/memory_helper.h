#ifndef MEMORY_HELPER_H 
#define MEMORY_HELPER_H
#include <stdint.h>
#include <stdlib.h>

#define ALIGNMENT 8 //8 byte alignment


typedef struct Node {
    struct Node *next;
    uint32_t blockSize;
} Node;
typedef struct MemoryRegion {
    void *memory;
    uint32_t nBytes;
    Node *freeList;
} MemoryRegion;





#endif
