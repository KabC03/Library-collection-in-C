#include "tree.h"

/**
 * @brief :: Helper function for printing integers (for use in tree_disp) 
 *
 * @param :: *ptr :: Item to be printed
 * 
 * @return :: void
 */
void tree_print_integer(void *ptr) {

    if(ptr == NULL) {
        return;
    } else {
        printf("%d, ", *((int*)ptr));
    }
    return;
}


/**
 * @brief :: Print a tree
 *
 * @param :: *tree :: Tree to print
 * @param :: print_element :: Printing function for datatype
 * 
 * @return :: void :: Indication of success/failure
 */
void tree_disp(Tree *tree,  void (print_element)(void *element)) {

    graph_list_disp(&(tree->graphList), print_element);

    return;
}



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

    return true;
}



/**
 * @brief :: Insert a node
 *
 * @param :: *tree :: Tree to insert to
 * @param :: nodeID :: New node ID
 * @param :: insertID :: Node to insert under
 * @param :: *data :: Data to insert
 * 
 * @return :: bool :: Indication of success/failure
 */
bool tree_insert(Tree *tree, size_t nodeID, size_t insertID, void *data) {

    if(graph_list_get_num_nodes(&(tree->graphList)) == 0) {
        if(graph_insert_lone_node(&(tree->graphList), data, nodeID) == false) {
            return false;
        }
    } else {
        if(graph_list_insert_below(&(tree->graphList), insertID, data, nodeID) == false) {
            return false;
        }
    }

    return true;
}



/**
 * @brief :: Find a node in a tree
 *
 * @param :: *tree :: Tree to search
 * @param :: nodeID :: Node to delete
 * 
 * @return :: void* :: Data
 */
void *tree_find(Tree *tree, size_t nodeID) {

    return graph_list_find(&(tree->graphList), nodeID);
}








/**
 * @brief :: Delete a node
 *
 * @param :: *tree :: Tree to delete from
 * @param :: nodeID :: Node to delete
 * 
 * @return :: void
 */
void tree_delete(Tree *tree, size_t nodeID) {

    //Find parent node then link parent node to all decendent nodes of deleted node then delete current node

    size_t *nodeIndexPtr = ((size_t*)hashmap_find(&(tree->graphList.ID2Index), &nodeID, sizeof(nodeID)));

    List *mergeSrc = vector_access_index(&(tree->graphList.adjacencyList), *nodeIndexPtr);
    List *mergeDest = graph_list_find_first_parent_list(&(tree->graphList), nodeID);

    //Merge src into destination
    list_transfer(mergeDest, mergeSrc);

    return;
}











