#include "memory.h"
#include "memory_helper.h"
#include <stdint.h>
#include <stdlib.h>


MemoryRegion memory_init(void *memory, uint32_t nBytes) {
    MemoryRegion region = {
        .memory = memory,
        .nBytes = nBytes,
        .freeList = NULL,
    };
    return region;
}


void *memory_malloc(MemoryRegion *region, uint32_t bytes) {
    Node **freeRegion = &(region->freeList);

    while(*freeRegion) {
        freeRegion = (*freeRegion)->next;
    }
    //Write pointer to next block to *freeRegion

    void *nodeEnd = internal_get_node_end(*freeRegion);
    void *alignedAddress = (void*)internal_get_node_end((uintptr_t)(*freeRegion));

    (*freeRegion) = alignedAddress;

    Node *newBlock = *freeRegion;
    newBlock->blockSize = bytes;
    newBlock->next = NULL;

    uint32_t *newBlockEnd = internal_get_node_end(newBlock);
    *newBlockEnd = bytes; //Footer

    void *userData = internal_align_address_forward(newBlock + sizeof(uint32_t));

    return userData;
}


void memory_free(void *ptr) {

    //Find header -> Find block size -> Find footer and merge next block
    //Find header -> Find previous footer -> Merge previous block

    return;
}



