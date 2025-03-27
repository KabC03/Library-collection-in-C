#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H
#include <assert.h>
#include "vector.h"
#include "list.h"
#include "hashmap.h"

//Graph as an adjacency list

typedef struct GraphList { 
    //For deletions - do swap and pop
    Hashmap ID2Index; //Hash node ID -> index into vectors
    Vector graphNodes; //Vector of graph nodes
    Vector adjacencyList; //Vector of linked lists (adjacency lists)

    size_t dataSize;

} GraphList;

//Init, insert, delete, print, find
bool graph_list_init(GraphList *graphList, size_t initialNumNodes, size_t dataSize);
void *graph_list_insert(GraphList *graphList, Vector *incommincConnections, Vector *outgoingConnections, void *data, size_t nodeID);



#endif


