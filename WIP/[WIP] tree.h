#ifndef TREE_H
#define TREE_H
#include "vector.h"

//Insert (under a node), delete (by ID), print entire tree, access (return pointer to node)

//Head node has ID of 0

typedef struct TreeNode {
    size_t ID;
    Vector decendents;
    uint8_t data[];
} TreeNode;

typedef struct Tree {
    TreeNode *node;
    size_t numNodes;
    size_t dataSize;
} Tree;

void tree_print_integer(void *ptr);
void tree_disp(Tree *tree,  void (print_element)(void *element));
size_t tree_num_nodes(Tree *tree);
bool tree_init(Tree *tree, size_t dataSize, size_t initialNodes);
bool tree_insert(Tree *tree, size_t nodeID, size_t insertID, void *data);
void *tree_find(Tree *tree, size_t nodeID);
void tree_delete(Tree *tree, size_t nodeID);



#endif

