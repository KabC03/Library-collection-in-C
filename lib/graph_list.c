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
    //Optimised for node deletion, using a vector here would mean deletions become really slow
    //Though consider... lots of pointer dereferencing going on here, HORRIBLE cache locality
    //Maybe in future consider hashing nodeID -> vector index of node
    graphList->dataSize = dataSize;
    if(list_init(&(graphList->adjacencyList), sizeof(List)) == false) {
        return false;
    }
    if(list_init(&(graphList->graphNodes), sizeof(GraphNode) + dataSize) == false) {
        list_destroy(&(graphList->adjacencyList));
        return false;
    }

    for(size_t i = 0; i < initialNumNodes; i++) {
        List *currentList = list_access_index(&(graphList->adjacencyList), i);

        if(list_init(currentList, sizeof(size_t)) == false) { //Allocation failure
            for(size_t j = 0; j < i; j++) {
                currentList = list_access_index(&(graphList->adjacencyList), j);
                list_destroy(currentList);
            }
            list_destroy(&(graphList->adjacencyList));
            return false;
        }
    }

    return true;
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

    GraphNode *newNode = MACRO_MALLOC(1, sizeof(GraphNode));
    if(newNode == NULL) {
        return NULL;
    }
    newNode->nodeID = nodeID;
    MACRO_MEMCPY(newNode->data, data, graphList->dataSize);


    return newNode;
}




