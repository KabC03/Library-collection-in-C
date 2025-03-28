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
    size_t numNodes;

} GraphList;

//delete, print, find
void graph_list_print_integer(void *ptr);
void graph_list_disp(GraphList *graphList, void (print_element)(void *element));
size_t graph_list_get_num_nodes(GraphList *graphList);
void *graph_insert_lone_node(GraphList *graphList, void *data, size_t nodeID);
bool graph_list_init(GraphList *graphList, size_t initialNumNodes, size_t dataSize);
void *graph_list_insert_below(GraphList *graphList, size_t incommingConnectionID ,void *data, size_t nodeID);
void *graph_list_insert(GraphList *graphList, Vector *incommingConnections, Vector *outgoingConnections, void *data, size_t nodeID);
bool graph_list_delete(GraphList *graphList, size_t nodeID);
void *graph_list_set(GraphList *graphList, size_t nodeID, void *data);
void *graph_list_find(GraphList *graphList, size_t nodeID);
List *graph_list_find_first_parent_list(GraphList *graphList, size_t nodeID);


#endif


