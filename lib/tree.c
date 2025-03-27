#include "tree.h"

/**
 * @brief :: Initialise a tree
 *
 * @param :: *tree :: Tree to initialise
 * @param :: initialNodes :: Space reserved for this many nodes
 * @param :: dataSize :: Size of data
 * 
 * @return :: bool :: Indication of success/failure
 */
bool tree_init(Tree *tree, size_t dataSize, size_t initialNodes) {

    if(graph_list_init(&(tree->graphList), initialNodes, dataSize) == false) {
        return false;
    }

    return false;
}



/**
 * @brief :: Insert a node
 *
 * @param :: *tree :: Tree to insert to
 * @param :: nodeID :: Node to insert under
 * @param :: *data :: Data to insert
 * 
 * @return :: bool :: Indication of success/failure
 */
bool tree_insert(Tree *tree, size_t nodeID, void *data) {

    if(graph_list_get_num_nodes(&(tree->graphList)) == 0) {
        if(graph_insert_lone_node(&(tree->graphList), nodeID) == false) {
            return false;
        }
    } else {
        if(graph_list_insert_below(&(tree->graphList), 0, data, nodeID) == false) {
            return false;
        }
    }

    return false;
}


/**
 * @brief :: Delete a node
 *
 * @param :: *tree :: Tree to insert to
 * @param :: nodeID :: Node to delete
 * 
 * @return :: bool :: Indication of success/failure
 */
bool tree_insert(Tree *tree, size_t nodeID, void *data) {

    //NOTE: SHOULD FIX THE TREE IF A MIDDLE NODE IS DELETED


    return false;
}











