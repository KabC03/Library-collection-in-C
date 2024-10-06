//3 Oct
#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {

    struct Node *next;
    uint8_t data[]; //Flexible length array

} Node;
typedef struct List {

    size_t size; //Size of the list (number of elements)
    unsigned short int dataSize; //Data size of item stored in list
    struct Node *head;

} List;


void list_print_uint8_t(void *ptr);
void list_print_integer(void *ptr);
bool list_init(List *list, size_t dataSize);
void list_destroy(List *list);
void list_disp(List *list , void print_element(void *element));
Node *list_append(List *list, void *data);
Node *list_dequeue(List *list);
Node *list_push(List *list, void *data);
Node *list_enqueue(List *list, void *data); //Alternative name for list_push
Node *list_pop(List *list);
Node *list_peak_front(List *list);
Node *list_peak_back(List *list);
Node *list_insert_index(List *list, size_t index, void *data);
Node *list_delete_index(List *list, size_t index);
Node *list_access_index(List *list, size_t index);
Node *list_find(List *list, void *data);
bool list_find_and_delete(List *list, void *data);

#endif 



      
      
      
      