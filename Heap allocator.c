#include "Heap allocator.h"


struct MemoryNode{  //Stored next to the free node

    size_t blockSize;            //Size of the block
    bool isUsed;                 //If the block is used
    struct MemoryNode *next;      //Next block
    struct MemoryNode *previous; //Previous block

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
        newNode.blockSize = (pageSize * systemPageSize) - sizeof(MemoryNode);
        //Number of free bytes in block (including metadata)

        newNode.next = NULL;
        newNode.previous = NULL;
        memcpy(newMemory, &newNode, sizeof(MemoryNode));
        
        heap->memoryNode = newMemory;
        heap->numBytes =  (pageSize * systemPageSize); //Number of bytes (including metadata)
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
void *heap_allocate(Heap *const heap, size_t size) {


    if(size == 0 || heap == NULL) {
        return NULL;
    } else {

        //Move through the LL until find a node with a large enough capacity. Break off whats needed then trim the node
        //If no blocks free just return NULL


        if(size > heap->numBytes) {
            return NULL;
        } else {

            MemoryNode *currentNode = heap->memoryNode;


            while(currentNode != NULL) {

                if(currentNode->blockSize >= size + sizeof(MemoryNode)) { //Allocate memory (Also have to store metadata)

                    size_t leftover = currentNode->blockSize - size - sizeof(MemoryNode);
                    //Size of the leftover block (after splitting)


                    //Split the block - therefore set up the next node in the block
                    MemoryNode newNode;
                    newNode.isUsed = false;
                    newNode.next = currentNode->next;
                    newNode.previous = currentNode;
                    newNode.blockSize = leftover;


                    //Put data into the current node
                    currentNode->isUsed = true;
                    currentNode->blockSize = size;
                    //Previous node does not need to be updated
                    //Set next node to the address of the copied block
                    currentNode->next = (MemoryNode*)((uint8_t*)currentNode + sizeof(MemoryNode) + currentNode->blockSize);

                    //Skip the allocated node

                    if(currentNode->previous != NULL) {
                        currentNode->previous->next = currentNode->next;
                    
                    
                    } else {
                        heap->memoryNode = currentNode->next;
                    }


                    //Copy the new node in
                    memcpy(currentNode->next, &newNode, sizeof(newNode));
                    return (void*)((uint8_t*)currentNode + sizeof(newNode)); //Skip the metadata and return pointer
                }

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
bool heap_free(void *ptr) {

    if(ptr == NULL) {
        return false;
    } else {

        //Comments outdataed
        //Decrement ptr by sizeof MemoryNode (to find the metadata node)
        //munmap the next bytes
        //Fragmentation can be resolved during allocation??

        //Deletion
        //While left and right are empty add them to the current block
        //Then just add to the LL

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













 
