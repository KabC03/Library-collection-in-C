#ifndef TREE_H
#define TREE_H
#include "graph_list.h"

//Insert (under a node), delete (by ID), print entire tree, access (return pointer to node)

//Head node has ID of 0
typedef struct Tree {
    GraphList graphList;
} Tree;


bool tree_init(Tree *tree, size_t dataSize, size_t initialNodes);

#endif

