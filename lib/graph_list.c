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
        if(list_init(currentList, sizeof(size_t)) == false) {
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
 * @param :: *incommingConnections :: Incomming connections to new node
 * @param :: *outgoingConnections :: Outgoing connections to new node
 *           NOTE: Yes it would be more efficient to pass as a sorted list but this makes library use more complicated, want to avoid complexity
 *                 Maybe do this in another function that accepts a list and prevents copying
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

    //Hash nodeID -> vectorTop
    size_t graphNodeVectorSize = vector_get_size(&(graphList->graphNodes));
    if(hashmap_insert(&(graphList->ID2Index), &nodeID, sizeof(nodeID), &graphNodeVectorSize, sizeof(graphNodeVectorSize)) == NULL) {
        goto cleanup_A;
    }

    //Append node data
    if(vector_append(&(graphList->graphNodes), data, 1) == false) {
        goto cleanup_A;
    }

    //Append to adjacency list, this is innefficient, unessesary copy, should try to init() in place in vector
    //Fix this later
    List newList; //List contains ID of connected nodes
    if(list_init(&newList, sizeof(graphList->dataSize)) == false) {
        goto cleanup_A;
    }
    if(vector_append(&(graphList->adjacencyList), &newList, 1) == false) {
        goto cleanup_A;
    }


    //Add outgoing nodes to adjacency list
    List *currentListOutgoing = vector_access_index(&(graphList->adjacencyList), vector_get_size(&(graphList->graphNodes)));
    for(size_t i = 0; i < vector_get_size(outgoingConnections); i++) {
        void *currentData = vector_access_index(outgoingConnections, i);
        if(list_append(currentListOutgoing, currentData) == false) {
            goto cleanup_B;
        }
    }

    //Add incomming nodes to list
    size_t incommingNodeIterator = vector_get_size(incommincConnections);
    for(size_t i = 0; i < vector_get_size(incommincConnections); i++) {

        size_t currentIncommingConnection = *((size_t*)vector_access_index(incommincConnections, i));
        size_t appendToIndex = *((size_t*)hashmap_find(&(graphList->ID2Index), &currentIncommingConnection, sizeof(size_t)));

        List *currentList = vector_access_index(&(graphList->adjacencyList), appendToIndex);

        if(list_append(currentList, &nodeID) == false) {
            incommingNodeIterator = i;
            goto cleanup_C;
        }
    }



    return newNode;
cleanup_C:
    //Remove the trace of the new node
    for(size_t i = 0; i < incommingNodeIterator; i++) {

        size_t currentIncommingConnection = *((size_t*)vector_access_index(incommincConnections, i));
        size_t appendToIndex = *((size_t*)hashmap_find(&(graphList->ID2Index), &currentIncommingConnection, sizeof(size_t)));

        List *currentList = vector_access_index(&(graphList->adjacencyList), appendToIndex);

        list_find_and_delete(currentList, &nodeID); //Delete the node from the other adjacency lists
    }

cleanup_B:
    list_destroy(currentListOutgoing);
cleanup_A:
    free(newNode);
    return false;
}




