#ifndef TREE_H
#define TREE_H
#include "graph_list.h"

//Insert (under a node), delete (by ID), print entire tree, access (return pointer to node)

//Head node has ID of 0
typedef struct Tree {
    GraphList graphList;
} Tree;

void tree_print(Tree *tree,  void (print_element)(void *element));
bool tree_init(Tree *tree, size_t dataSize, size_t initialNodes);
bool tree_insert(Tree *tree, size_t nodeID, void *data);
void *tree_find(Tree *tree, size_t nodeID);
bool tree_delete(Tree *tree, size_t nodeID);



#endif

