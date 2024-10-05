#include "list.h"


#define MACRO_MALLOC(numel, size) malloc(numel * size)
#define MACRO_MEMCPY(dest, src, n) memcpy(dest, src, n)
#define MACRO_FREE(ptr) free(ptr)
#define MACRO_MEMCMP(arg1, arg2, n) memcmp(arg1, arg2, n)

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
        MACRO_FREE(previous);
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
 * @brief :: Dequeues an item from a list
 *           NOTE: Returned node must be freed manually
 *           NOTE: Dequeueing from an empty list is undefined
 *
 * @param :: *list :: List to append an item too 
 * 
 * @return :: Node* :: Dequeued node 
 */
Node *list_dequeue(List *list) {

    Node *temp = NULL;
    Node **current = &(list->head);
    for(size_t i = 0; i < list->size - 1; i++) {
        current = &((*current)->next);
    }
    temp = *current;
    *current = NULL;
    list->size--;

    return temp;
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
 * @brief :: Enqueue an item to a list. The list is unchanged upon failure. The list is unchanged if the enqueue is unsuccessful
 *
 * @param :: *list :: List to enqueue an item too 
 * @param :: *data :: Data to enqueue to list
 * 
 * @return :: bool :: Indication of if item was enqueue 
 */
bool list_enqueue(List *list, void *data) { 
    //Alternative name for list_push
    return list_push(list, data);
}


/**
 * @brief :: Pop an item from the front of a list
 *           NOTE: Returned item MUST be freed manually
 *           NOTE: Popping from an empty list is undefined
 *
 * @param :: *list :: List to pop an item from 
 * 
 * @return :: Node* :: Item popped from the list 
 */
Node *list_pop(List *list) {

    Node *temp = list->head;
    list->head = list->head->next;
    //free(temp);
    list->size--;

    return temp; 
}



/**
 * @brief :: Peak the front of a list. The list is unchanged 
 *           NOTE: Peaking from an empty list is undefined
 *
 * @param :: *list :: List to peak an item from 
 * 
 * @return :: Node* :: Item peaked from the list 
 */
Node *list_peak_front(List *list) {
    return list->head; 
}




/**
 * @brief :: Peak the back of a list. The list is unchanged 
 *           NOTE: Peaking from an empty list is undefined
 *
 * @param :: *list :: List to peak an item from 
 * 
 * @return :: Node* :: Item peaked from the list 
 */
Node *list_peak_back(List *list) {
    Node *current = list->head;
    for(size_t i = 0; i < list->size - 1; i++) {
        current = current->next;
    }
    return current;
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
 * @brief :: Deletes an item at an index from a list 
 *           NOTE: Returned node must be freed manually
 *           NOTE: Deleting from an empty list is undefined
 *
 * @param :: *list :: List to append an item too 
 * @param :: index :: Index to remove
 * 
 * @return :: Node* :: Deleted node 
 */
Node *list_delete_index(List *list, size_t index) {

    Node *temp = NULL;
    Node **current = &(list->head);
    for(size_t i = 0; i < index; i++) {
        current = &((*current)->next);
    }
    temp = *current;
    *current = (*current)->next;
    list->size--;

    return temp;
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


/**
 * @brief :: Find an item in a list 
 *
 * @param :: *list :: List to search item in 
 * @param :: *data :: Data to find in list
 * 
 * @return :: Node* :: Node containing the item, is NULL if the item is not found
 */
Node *list_find(List *list, void *data) {

    Node **current = &(list->head);
    for(size_t i = 0; i < list->size; i++) {

        if(MACRO_MEMCMP((*current)->data, data, list->dataSize) == 0) {
            return *current;
        }
        current = &((*current)->next); 
    }

    return NULL;
}



/**
 * @brief :: Find and delete an item in a list 
 *
 * @param :: *list :: List to search item in 
 * @param :: *data :: Data to find in list
 * 
 * @return :: bool :: Indication of if item was deleted from the list 
 */
bool list_find_and_delete(List *list, void *data) {

    Node *temp = NULL;
    Node **current = &(list->head);
    for(size_t i = 0; i < list->size; i++) {

        if(MACRO_MEMCMP((*current)->data, data, list->dataSize) == 0) {
            //Element found
            list->size--;
            temp = *current;
            *current = (*current)->next;
            MACRO_FREE(temp);
            return true;
        }
        current = &((*current)->next); 
    }


    return false;
}















