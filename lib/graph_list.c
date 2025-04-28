#include "graph_list.h"
#define MACRO_MALLOC(numel, size) malloc(numel * size)
#define MACRO_REALLOC(ptr, numel, size) realloc(ptr, numel * size)
#define MACRO_FREE(ptr) free(ptr)
#define CONST_REALLOC_EXPANSION 2
#define MACRO_MEMCPY(dest, src, n) memcpy(dest, src, n)
//Lots of code duplication in the insert functions... I should fix that eventually when I optimise


/**
 * @brief :: Helper function for printing integers (for use in graph_list_disp) 
 *
 * @param :: *ptr :: Item to be printed
 * 
 * @return :: void
 */
void graph_list_print_integer(void *ptr) {

    if(ptr == NULL) {
        return;
    } else {
        printf("%d, ", *((int*)ptr));
    }
    return;
}


/**
 * @brief :: Print a graph
 *
 * @param :: *graphList :: Graph to print
 * @param :: print_element :: Function to print element
 * 
 * @return :: bool :: Indication of success or failure
 */
void graph_list_disp(GraphList *graphList, void (print_element)(void *element)) {

    printf("\tGraph nodes: %zu\n", graphList->numNodes);
    printf("\n\n\tGraph hashmap:\n");
    hashmap_disp(&(graphList->ID2Index), hashmap_print_size_t, hashmap_print_size_t);

    printf("\tGraph node data:\n");
    for(size_t i = 0; i < vector_get_size(&(graphList->graphNodes)); i++) {
        void *currentItem = vector_access_index(&(graphList->graphNodes), i);
        print_element(currentItem);
    }

    printf("\n\n\tGraph connections:\n");
    for(size_t i = 0; i < vector_get_size(&(graphList->adjacencyList)); i++) {
        printf("\t\ti = %zu\n",i);
        List *currentList = vector_access_index(&(graphList->adjacencyList), i);
        list_disp(currentList, list_print_size_t);
    }

    return;
}



/**
 * @brief :: Return number of nodes in graph
 *
 * @param :: *graphList :: Graph of interest
 * 
 * @return :: size_t :: Number of nodes
 */
size_t graph_list_get_num_nodes(GraphList *graphList) {

    return graphList->numNodes;
}




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
    graphList->numNodes = 0;
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
        //list_disp(currentList, list_print_size_t);
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
void *graph_list_insert(GraphList *graphList, Vector *incommingConnections, Vector *outgoingConnections, void *data, size_t nodeID) {

    //Insert nodes into adjacency list by decending order to minimise lookup time

    //Hash nodeID -> vectorTop
    size_t graphNodeVectorSize = vector_get_size(&(graphList->graphNodes));
    if(hashmap_insert(&(graphList->ID2Index), &nodeID, sizeof(nodeID), &graphNodeVectorSize, sizeof(graphNodeVectorSize)) == NULL) {
        goto cleanup_A;
    }

    //Append node data
    void *returnPtr = vector_append(&(graphList->graphNodes), data, 1);
    if(returnPtr == NULL) {
        goto cleanup_A;
    }


    /*
    //Append to adjacency list, this is innefficient, unessesary copy, should try to init() in place in vector
    //Fix this later
    List newList; //List contains ID of connected nodes
    if(list_init(&newList, sizeof(graphList->dataSize)) == false) {
        goto cleanup_B;
    }
    if(vector_append(&(graphList->adjacencyList), &newList, 1) == false) {
        goto cleanup_B;
    }
    */

    
    //Faster but maybe buggy
    if(vector_expand(&(graphList->adjacencyList), 1) == false) {
        goto cleanup_A;
    }
    List *newListPtr = vector_access_index(&(graphList->adjacencyList), vector_get_size(&(graphList->graphNodes)) - 1); //List contains ID of connected nodes
    if(list_init(newListPtr, sizeof(size_t)) == false) {
        goto cleanup_B;
    }
    



    //Add outgoing nodes to adjacency list
    List *currentListOutgoing = vector_access_index(&(graphList->adjacencyList), vector_get_size(&(graphList->graphNodes)) - 1);
    for(size_t i = 0; i < vector_get_size(outgoingConnections); i++) {
        void *currentData = vector_access_index(outgoingConnections, i);
        if(list_push(currentListOutgoing, currentData) == false) {
            goto cleanup_C;
        }
    }

    //Add incomming nodes to list
    size_t incommingNodeIterator = vector_get_size(incommingConnections);
    for(size_t i = 0; i < vector_get_size(incommingConnections); i++) {

        size_t currentIncommingConnection = *((size_t*)vector_access_index(incommingConnections, i));
        size_t appendToIndex = *((size_t*)hashmap_find(&(graphList->ID2Index), &currentIncommingConnection, sizeof(currentIncommingConnection)));
        List *currentList = vector_access_index(&(graphList->adjacencyList), appendToIndex);
        if(list_push(currentList, &nodeID) == false) {
            incommingNodeIterator = i;
            goto cleanup_D;
        }

    }


    graphList->numNodes++;
    return returnPtr;
cleanup_D:
    //Remove the trace of the new node
    for(size_t i = 0; i < incommingNodeIterator; i++) {

        size_t currentIncommingConnection = *((size_t*)vector_access_index(incommingConnections, i));
        size_t appendToIndex = *((size_t*)hashmap_find(&(graphList->ID2Index), &currentIncommingConnection, sizeof(currentIncommingConnection)));

        List *currentList = vector_access_index(&(graphList->adjacencyList), appendToIndex);

        list_find_and_delete(currentList, &nodeID); //Delete the node from the other adjacency lists
    }

cleanup_C:
    list_destroy(currentListOutgoing);
cleanup_B:
    vector_pop(&(graphList->adjacencyList));
cleanup_A:
    return NULL;

}





/**
 * @brief :: Delete an item from a graph
 *
 * @param :: *graphList :: Graph to initialise
 * @param :: nodeID :: Node to remove
 * 
 * @return :: bool :: Indication of item was found and removed
 */
bool graph_list_delete(GraphList *graphList, size_t nodeID) {

    size_t *nodeIndexPtr = ((size_t*)hashmap_find(&(graphList->ID2Index), &nodeID, sizeof(nodeID)));
    if(nodeIndexPtr == NULL) {
        return false;
    }

    for(size_t i = 0; i < vector_get_size(&(graphList->adjacencyList)); i++) {

        List *currentList = vector_access_index(&(graphList->adjacencyList), i);

        list_find_and_delete(currentList, &nodeID); //Delete the node from the other adjacency lists
    }

    //Swap and pop out last node

    size_t lastIndex = vector_get_size(&(graphList->adjacencyList)) - 1;
    vector_xor_swap(&(graphList->adjacencyList), *nodeIndexPtr, lastIndex);
    vector_pop(&(graphList->adjacencyList));

    //Adjust the hashmap
    printf("NOT IMPLEMENTED YET\n");
    exit(-1);
    /*
    To readjust hashmap indexing:
    - Lookup what nodeID was stored in the last index
    - Search the hashmap (which goes nodeID -> vector index) for vector index -> nodeID
    - Once the nodeID is found of the last element, use hash_set_key() to set the nodeID to its new position in the vector
    */



    //nodeIndexPtr points to the swapped element - must update the hashmap
    //TODO


    lastIndex = vector_get_size(&(graphList->graphNodes)) - 1;

    vector_xor_swap(&(graphList->graphNodes), *nodeIndexPtr, lastIndex);
    vector_pop(&(graphList->graphNodes));
    hashmap_remove(&(graphList->ID2Index), &nodeID, sizeof(nodeID));
    
    graphList->numNodes--;
    return true;
}


/**
 * @brief :: Set the value of a node in a list
 *
 * @param :: *graphList :: Graph to initialise
 * @param :: nodeID :: Node to set
 * @param :: *data :: Data to set
 * 
 * @return :: void* :: Set node (if present)
 */
void *graph_list_set(GraphList *graphList, size_t nodeID, void *data) {

    size_t *nodeIndexPtr = ((size_t*)hashmap_find(&(graphList->ID2Index), &nodeID, sizeof(nodeID)));
    if(nodeIndexPtr == NULL) {
        return NULL;
    }
    vector_set_index(&(graphList->graphNodes), data, *nodeIndexPtr);

    return vector_access_index(&(graphList->graphNodes), *nodeIndexPtr);
}




/**
 * @brief :: Find an item in a graph
 *
 * @param :: *graphList :: Graph to initialise
 * @param :: nodeID :: Node to find
 * 
 * @return :: void* :: Data (if present)
 */
void *graph_list_find(GraphList *graphList, size_t nodeID) {

    size_t *nodeIndexPtr = ((size_t*)hashmap_find(&(graphList->ID2Index), &nodeID, sizeof(nodeID)));
    if(nodeIndexPtr == NULL) {
        return NULL;
    }

    return vector_access_index(&(graphList->graphNodes), *nodeIndexPtr);
}



/**
 * @brief :: Find the first parent of a node and immediatly return, may miss other parents
 *
 * @param :: *graphList :: Graph to search
 * @param :: nodeID :: Node ID to search parent
 * 
 * @return :: List* :: Parent node adjacency list
 */
List *graph_list_find_first_parent_list(GraphList *graphList, size_t nodeID) {

    void *returnPtr = NULL;
    for(size_t i = 0; i < vector_get_size(&(graphList->adjacencyList)); i++) {

        List *currentList = vector_access_index(&(graphList->adjacencyList), i);

        returnPtr = list_find(currentList, &nodeID);
        if(returnPtr != NULL) {
            return currentList;
        }
    }

    return NULL;
}









