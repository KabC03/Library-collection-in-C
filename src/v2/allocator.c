#include "./allocator.h"

#define MAX_ALIGNMENT 32 //4 bytes
#define ADDRESS_TYPE uint32_t

//Address bounds
ADDRESS_TYPE heapStart = 0;
ADDRESS_TYPE heapEnd = 0;
Block *head = NULL;



/** allocator_init
 * 
 * @brief Initialise the allocator with a starting and ending address
 * 
 * @param start :: Start of heap address
 * @param end :: End of heap address
 * 
 * @return void :: None
 */
void allocator_init(ADDRESS_TYPE start, ADDRESS_TYPE end) {
    heapStart = start;
    heapEnd = end;
    return;
}


/** allocator_alloc
 *  
 * @brief Allocate memory and return a pointer, fails if items * size overflows
 * 
 * @param items :: Number of items to allocate
 * @param size :: Size of each item to allocate
 * 
 * @return void* :: Pointer to memory block, NULL if allocation failed or items * size overflows
 */
void *allocator_alloc(ADDRESS_TYPE items, ADDRESS_TYPE size) {

    ADDRESS_TYPE addr = sizeof(Block);
    ADDRESS_TYPE alignedAddr = addr + ((MAX_ALIGNMENT - (addr % MAX_ALIGNMENT)) % MAX_ALIGNMENT);

    Block block;
    if(head == NULL) {
        memcpy(heapStart, &block, alignedAddr);
    } else {
        ADDRESS_TYPE start = &(block.next) + sizeof(Block);
        ADDRESS_TYPE alignedAddrStart = start + ((MAX_ALIGNMENT - (start % MAX_ALIGNMENT)) % MAX_ALIGNMENT);

        while(alignedAddrStart - block.end)
    }

    return alignedAddr;
}


/** allocator_free
 * 
 */
void allocator_free(void *ptr) {

    return;
}







