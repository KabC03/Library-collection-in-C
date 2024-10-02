#include "list.h"


#define MACRO_MALLOC(numel, size) malloc(numel * size)
#define MACRO_MEMCPY(dest, src, n) memcpy(dest, src, n)


/**
 * @brief :: Helper function for printing uint8_t (for use in list_disp) 
 *
 * @param :: *ptr :: Item to be printed
 * 
 * @return :: void
 */
void list_print_uint8_8(void *ptr) {

    if(ptr == NULL) {
        return;
    } else {
        printf("%u ", *((unsigned int*)ptr));
    }
    return;
}



/**
 * @brief :: Helper function for printing integers (for use in list_disp) 
 *
 * @param :: *ptr :: Item to be printed
 * 
 * @return :: void
 */
void list_print_integer(void *ptr) {

    if(ptr == NULL) {
        return;
    } else {
        printf("%d ", *((int*)ptr));
    }
    return;
}

/**
 * @brief :: Display the status of a list and all of its elements
 *
 * @param :: *list :: List to be displayed
 * @param :: print_element :: Print function for individual element
 * 
 * @return :: void
 */
void list_disp(List *list , void print_element(void *element)) {

    printf("=====LIST STATUS=====\n");
    if(list == NULL) {
        printf("NULL\n");
        return;
    }

    printf("\tData size: %d\n\tSize: %zu\n", list->dataSize, list->size);

    printf("Data:\n");
    Node *current = list->head;
    for(size_t i = 0; i < list->size; i++) { //Get to the last item in the list
        print_element(current->data);
        current = current->next; 
    }
    printf("\n=======================\n");

    return;
}




/**
 * @brief :: Initialises a list 
 *
 * @param :: *list :: List of interest to be initialised 
 * @param :: dataSize :: Size of individual vector element
 * 
 * @return :: bool :: Indicates if list was initialised 
 */
bool list_init(List *list, size_t dataSize) {

    list->dataSize = dataSize;
    list->size = 0;
    list->head = NULL;

    return true;
}

/**
 * @brief :: Destroy a list and all associated memory 
 *
 * @param :: *list :: List to be destroyed 
 * 
 * @return :: void
 */
void list_destroy(List *list) {

    Node *current = list->head;
    Node *previous = current;
    for(size_t i = 0; i < list->size; i++) {
        current = current->next;
        free(previous);
        previous = current;
    }

    list->head = NULL;
    list->size = 0;

    return;
}




/**
 * @brief :: Appends an item to a list. The list is unchanged upon failure
 *
 * @param :: *list :: List to append an item too 
 * @param :: *data :: Data to append to list
 * 
 * @return :: bool :: Indication of if item was appended 
 */
bool list_append(List *list, void *data) {

    //Set up new node
    Node *newNode = MACRO_MALLOC(1, sizeof(Node) + list->dataSize);
    if(newNode == NULL) {
        return false;
    }
    newNode->next = NULL;
    MACRO_MEMCPY(newNode->data, data, list->dataSize);
    
    //Append node
    Node **current = &(list->head);
    for(size_t i = 0; i < list->size; i++) { //Get to the last item in the list
        current = &((*current)->next); 
    }
    *current = newNode;
    list->size++;

    return true;
}





/**
 * @brief :: Push an item to a list. The list is unchanged upon failure. The list is unchanged if the push is unsuccessful
 *
 * @param :: *list :: List to push an item too 
 * @param :: *data :: Data to push to list
 * 
 * @return :: bool :: Indication of if item was pushed 
 */
bool list_push(List *list, void *data) {

    //Set up new node
    Node *newNode = MACRO_MALLOC(1, sizeof(Node) + list->dataSize);
    if(newNode == NULL) {
        return false;
    }
    newNode->next = NULL;
    MACRO_MEMCPY(newNode->data, data, list->dataSize);
    
    //Append node
    newNode->next = list->head;
    list->head = newNode;
    list->size++;

    return true;
}



/**
 * @brief :: Pop an item from the front of a list
 *
 * @param :: *list :: List to pop an item from 
 * 
 * @return :: void* :: Item popped from the list 
 */
void *list_pop(List *list) {

    Node *temp = list->head;
    list->head = list->head->next;
    free(temp);

    return list->head->data;
}




/**
 * @brief :: Insert an item at an index in a list. The list is unchanged if the insertion is not successful
 *
 * @param :: *list :: List to insert an item too 
 * @param :: index :: Index to insert the data 
 * @param :: *data :: Data to insert to list
 * 
 * @return :: bool :: Indication of if item was inserted 
 */
bool list_insert_index(List *list, size_t index, void *data) {

    //Set up new node
    Node *newNode = MACRO_MALLOC(1, sizeof(Node) + list->dataSize);
    if(newNode == NULL) {
        return false;
    }
    newNode->next = NULL;
    MACRO_MEMCPY(newNode->data, data, list->dataSize);
    
    //Append node
    Node **current = &(list->head);
    for(size_t i = 0; i < index; i++) { //This is technically unsafe, no bounds checking done here
        current = &((*current)->next); 
    }
    newNode->next = *current;
    *current = newNode;
    list->size++;

    return true;
}





/**
 * @brief :: Get an item at an index from a list 
 *
 * @param :: *list :: List to index 
 * @param :: index :: Index to insert the data 
 * 
 * @return :: bool :: Indication of if item was inserted 
 */
void *list_access_index(List *list, size_t index) {

    Node *current = list->head;
    for(size_t i = 0; i < index; i++) { //This is technically unsafe, no bounds checking done here
        current = current->next; 
    }

    return current->data;
}






















