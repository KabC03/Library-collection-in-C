#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H
#include <assert.h>
#include "vector.h"
#include "list.h"

//Graph as an adjacency list

typedef struct GraphNode {

    size_t nodeID; //Store an identifier for the node
    uint8_t data[];

} GraphNode;

typedef struct GraphList { 
    //Optimised for node deletion, using a vector here would mean deletions become really slow
    //Though consider... lots of pointer dereferencing going on here, HORRIBLE cache locality
    //Maybe in future consider hashing nodeID -> vector index of node

    List adjacencyList; //List of linked lists
    //Was considering directly mapping insertion order -> list index but this makes deletion really hard
    //Since every node must have its index adjusted once the list resizes
    List graphNodes; //List of graph nodes
    size_t dataSize;

} GraphList;

//Init, insert, delete, print, find
bool graph_list_init(GraphList *graphList, size_t initialNumNodes, size_t dataSize);
void *graph_list_insert(GraphList *graphList, Vector *incommincConnections, Vector *outgoingConnections, void *data, size_t nodeID);



#endif


