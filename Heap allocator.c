#include "Heap allocator.h"


struct MemoryNode{  //Stored next to the free node

    size_t blockSize;            //Size of the block with padding and metadata

    bool isUsed;                 //If the block is used

    struct MemoryNode *next;     //Next block
    struct MemoryNode *prev;     //Previous block (NULL if node is being used, loops to itself or previous node if free)

};
//Doubly linked list
//When allocating node set forward pointer to skip allocated node
//Allocated node back ptr points to previous node, forward ptr points to next node still
//When freeing, can check if adjacent blocks are marked free, if so then combine and insert


/*
Allocating:

1. prevNode->next = allocatedNode->next
2. (Leave allocatedNode->prev pointing to prevNode)
3. Done?
4. If adjacent block is allocated


*/


//Undo alignment to find metadata
size_t calculate_dealignment_offset(void *address, size_t alignment) {

    size_t offset = 0;
    if(address == NULL) {
        return -1;
    } else {
        offset = (uintptr_t)address % alignment;
    }

    return  offset;
}

//Calculate the allignment corretion of data
size_t calculate_alignment_correction(void *address, size_t alignment) {

    size_t correction = 0;
    if(address == NULL) {
        return -1;
    } else {


        size_t misAllignment = 0; 
        //Metadata alignment

        misAllignment = (((uintptr_t)address) % alignment);
        if(misAllignment == 0) {
            correction = 0;
        } else {
            correction = alignment - misAllignment;
        }
    }


    return correction;
}





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
        void *newMemory = mmap(NULL, pageSize * systemPageSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if(newMemory == NULL) {
            return false;
        }


        MemoryNode newNode;
        newNode.isUsed = false;
        newNode.blockSize = (pageSize * systemPageSize);
        //Number of free bytes in block (including metadata)
        newNode.prev = newMemory;
        newNode.next = NULL;
        memcpy(newMemory, &newNode, sizeof(MemoryNode));
        
        heap->memoryNode = newMemory;
        heap->numBytes =  (pageSize * systemPageSize); //Number of bytes (including metadata)
        //Automatically aligned to bottom of page so dont need to manually do it
    }

    return true;
}



/**
 * heap_allocate
 * ===============================================
 * Brief: Request a block of memory 
 * 
 * Param: *heap - Heap of interest 
 *        size - Size of the block
 *        elementSize - Size of individual element in block (for allignment)
 * 
 * Return: void* - Pointer to the new block 
 * 
 */
void *heap_allocate(Heap *const heap, size_t size, size_t elementSize) {


    if(size == 0 || heap == NULL) {
        return NULL;
    } else {

        //Move through the LL until find a node with a large enough capacity. Break off whats needed then trim the node
        //If no blocks free just return NULL


        if(size > heap->numBytes) {
            return NULL;
        } else {

            MemoryNode *currentNode = heap->memoryNode;
            MemoryNode *prevNode = NULL;
            while(currentNode != NULL) { 

                size_t dataAlignmentCorrection = calculate_alignment_correction((uint8_t*)currentNode + sizeof(MemoryNode), elementSize); 
                size_t metadataAlignmentCorrection = calculate_alignment_correction((uint8_t*)currentNode + sizeof(MemoryNode) + size + dataAlignmentCorrection, alignof(MemoryNode));

                if(currentNode->blockSize >= size + sizeof(MemoryNode) + dataAlignmentCorrection + metadataAlignmentCorrection) { 
                    //Allocate memory (Also have to store metadata)

                    //Size of the current block including metadata and padding
                    size_t currentBlockSize = size + sizeof(MemoryNode) + dataAlignmentCorrection + metadataAlignmentCorrection;

                    size_t leftover = currentNode->blockSize - currentBlockSize;
                    //Size of the leftover block (after splitting)


                    //Split the block - therefore set up the next node in the block
                    MemoryNode newNode;
                    newNode.isUsed = false;
                    newNode.next = currentNode->next;
                    newNode.blockSize = leftover;
                    newNode.prev = currentNode;

                    //Put data into the current node
                    currentNode->isUsed = true;
                    currentNode->blockSize = currentBlockSize;
                    //Previous node does not need to be updated
                    //Set next node to the address of the copied block
                    //Need to MANUALLY align memory
                    //If allignment = size until size == long, then just allign for a void* (8 bytes)


                    MemoryNode *newNodeAddress = (MemoryNode*)((uint8_t*)currentNode + currentBlockSize);
                    //Skip the allocated node


                    //Allocate first node
                    if(prevNode == NULL) {
                        heap->memoryNode = currentNode->next;
                    } else {
                        prevNode->next = currentNode->next;
                    }

                    //Copy the new node in
                    memcpy(newNodeAddress, &newNode, sizeof(MemoryNode));
                    printf("Returning: %p || alignment = %zu\n",(void*)((uint8_t*)currentNode + sizeof(MemoryNode) + dataAlignmentCorrection), elementSize); //Should %elementSize == 0
                    printf("Next metadata struct is at: %p || alignment = %zu\n",newNodeAddress, alignof(MemoryNode)); //Should %alignof(MemoryNode) == 0
                    printf("Current metadata struct is at: %p\n",currentNode);


                    currentNode->next = prevNode;                    
                    currentNode->prev = NULL;

                    return (void*)((uint8_t*)currentNode + sizeof(MemoryNode) + dataAlignmentCorrection);
                    //Skip the metadata and return pointer
                }

                prevNode = currentNode;
                currentNode = currentNode->next;
            }

        }
    }
    return NULL;
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
bool heap_free(Heap *heap, void *ptr) {

    if(heap == NULL || ptr == NULL) {
        return false;
    } else {


        //If ptr == end of prevBlock then combine prev and current block
        //If ptrEnd == start of NextBlock then combine to current block


        //Find metadata struct (must be aligned to boundry and behind ptr)
        //(address - offset)%(alignment) = 0 -> (offset) = (address)%(alignment)
        size_t offset = calculate_dealignment_offset(ptr, alignof(MemoryNode));
        MemoryNode *currentNode = (MemoryNode*)((uintptr_t)(ptr) - offset - sizeof(MemoryNode));

        printf("Freeing ptr, blockSize = %zu || address of metadata = %p\n",currentNode->blockSize,currentNode);
        //Check if adjacent blocks are free (if so then combine them)


        MemoryNode *freeNode = currentNode;
        //Pointers behind currentNode automatically follow it (so it automatically remains ordered)
        

        while(1) {
            //If freenode == NULL then set heap head to point to new node
            //If freenode->prev != NULL then insert after

            if(freeNode == NULL) {
                break;
            } else if(freeNode->prev != NULL) {
                break;
            }

            freeNode = freeNode->next;
        }


        if(freeNode == NULL) {
            //Only node

            currentNode->next = heap->memoryNode;
            heap->memoryNode = currentNode;
            currentNode->prev = currentNode; //Loop pointer to itself to say its free and at the start


        } else {
            //Not the only node
            currentNode->next = freeNode->next;
            freeNode->next = currentNode;

            //Loop to indicate node is free
            currentNode->prev = currentNode;
        }


        //Combine adjacent nodes


        //Check previous node
        if(freeNode != NULL) {

            if((uintptr_t)freeNode + freeNode->blockSize + 1 == (uintptr_t)currentNode) {
                freeNode += currentNode->blockSize;
                freeNode->next = currentNode->next;
            }
        }


        //Combine next node
        if(currentNode->next != NULL) {

            if((uintptr_t)currentNode + currentNode->blockSize == (uintptr_t)currentNode->next) {
                currentNode->blockSize += currentNode->next->blockSize;
                currentNode->next = currentNode->next->next;
            }
        }




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
        if(heap->memoryNode == NULL) {
            return false;
        }


        if(munmap(heap->memoryNode, heap->numBytes) != 0) {
            return false;
        }
        
    }

    return true;    
}













 

 
