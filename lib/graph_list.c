#include "graph_list.h"
#define MACRO_MALLOC(numel, size) malloc(numel * size)
#define MACRO_REALLOC(ptr, numel, size) realloc(ptr, numel * size)
#define MACRO_FREE(ptr) free(ptr)
#define CONST_REALLOC_EXPANSION 2
#define MACRO_MEMCPY(dest, src, n) memcpy(dest, src, n)


/**
 * @brief :: Initialise a graph
 *
 * @param :: *graphList :: Graph to initialise
 * @param :: initialNumNodes :: Initial number of nodes
 * @param :: dataSize :: Data size of graph element
 * 
 * @return :: bool :: Indication of success or failure
 */
bool graph_list_init(GraphList *graphList, size_t initialNumNodes, size_t dataSize) {

    graphList->dataSize = dataSize;
    if(hashmap_init(&(graphList->ID2Index), initialNumNodes, hashmap_djb2) == false) {
        return false;
    }
    if(vector_init(&(graphList->graphNodes), dataSize, initialNumNodes) == false) {
        goto cleanup_A;
    }
    if(vector_init(&(graphList->adjacencyList), sizeof(List), initialNumNodes) == false) {
        goto cleanup_B;
    }

    for(size_t i = 0; i < initialNumNodes; i++) {

        List *currentList = vector_access_index(&(graphList->adjacencyList), i);
        if(list_init(currentList, dataSize) == false) {
            for(size_t j = 0; j < i; j++) {
                currentList = vector_access_index(&(graphList->adjacencyList), j);
                list_destroy(currentList);
            }
            goto cleanup_C;
        }
    }

    return true;
cleanup_C:
    vector_destroy(&(graphList->adjacencyList));
cleanup_B:
    vector_destroy(&(graphList->graphNodes));
cleanup_A:
    hashmap_destroy(&(graphList->ID2Index));
    return false;
}



/**
 * @brief :: Insert an item to a graph
 *
 * @param :: *graphList :: Graph to initialise
 * @param :: *incommingConnections :: Incomming connections to new node, SORTED IDs highest to lowest
 * @param :: *outgoingConnections :: Outgoing connections to new node, SORTED IDs highest to lowest
 * @param :: *data :: Data to insert to the graph
 * @param :: nodeID :: New node ID
 * 
 * @return :: void* :: Pointer to the new node in the graph
 */
void *graph_list_insert(GraphList *graphList, Vector *incommincConnections, Vector *outgoingConnections, void *data, size_t nodeID) {

    uint8_t *newNode = MACRO_MALLOC(1, graphList->dataSize);
    if(newNode == NULL) {
        return NULL;
    }
    //Insert nodes into adjacency list by decending order to minimise lookup time


    return newNode;
}




