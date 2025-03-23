//23 Mar
#ifndef QUEUE_H 
#define QUEUE_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct QueueNode {

	struct QueueNode *next;
	uint8_t data[];

} QueueNode;

typedef struct Queue {

	unsigned short int dataSize;
	struct QueueNode *head;
	struct QueueNode *tail;

} Queue;



void queue_print_uint8_t(void *ptr);
void queue_print_integer(void *ptr);
void queue_disp(Queue *queue, void print_element(void *element));
void queue_init(Queue *queue, unsigned short int dataSize);
bool queue_enqueue(Queue *queue, void *data);
QueueNode *queue_dequeue(Queue *queue);

#endif

