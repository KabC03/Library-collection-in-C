#include "priority_queue.h"
#define MACRO_MALLOC(numel, size) malloc(numel * size)
#define MACRO_MEMCPY(dest, src, n) memcpy(dest, src, n)
#define MACRO_FREE(ptr) free(ptr)
#define MACRO_MEMCMP(arg1, arg2, n) memcmp(arg1, arg2, n)

/**
 * @brief :: Helper function for printing uint8_t (for use in queue_disp) 
 *
 * @param :: *ptr :: Item to be printed
 * 
 * @return :: void
 */
void queue_print_uint8_t(void *ptr) {

    if(ptr == NULL) {
        return;
    } else {
        printf("%u", *((unsigned int*)ptr));
    }
    return;
}



/**
 * @brief :: Helper function for printing integers (for use in queue_disp) 
 *
 * @param :: *ptr :: Item to be printed
 * 
 * @return :: void
 */
void queue_print_integer(void *ptr) {

    if(ptr == NULL) {
        return;
    } else {
        printf("%d", *((int*)ptr));
    }
    return;
}


/**
 * @brief :: Print a queue 
 *
 * @param :: *queue :: Queue to be printed 
 * @param :: print_element :: Element printing function 
 * 
 * @return :: void
 */
void queue_disp(Queue *queue, void print_element(void *element)) {

    printf("=====QUEUE STATUS=====\n");
    if(queue == NULL) {
        printf("NULL\n");
        return;
    }

    printf("\tData size: %d\n\tSize: %zu\n", queue->dataSize, queue->size);

    printf("[Priority, Data]:\n");
    QueueNode *current = queue->tail;
    for(size_t i = 0; i < queue->size; i++) { //Get to the last item in the list
		printf("[%zu, ", current->priority);
        print_element(current->data);
		printf("], ");
        current = current->next; 
    }
    printf("\n=======================\n");

    return;
}


/**
 * @brief :: Initialise a queue 
 *
 * @param :: *queue :: Queue to be initialised 
 * @param :: dataSize :: Size of element contained within queue
 * 
 * @return :: void
 */
void queue_init(Queue *queue, unsigned short int dataSize) {

    queue->size = 0;
	queue->dataSize = dataSize;	
	queue->head = NULL;
	queue->tail = NULL;
	return;
}


/**
 * @brief :: Get a queue size 
 *
 * @param :: *queue :: Queue to insert to 
 * 
 * @return :: size_t :: Queue size
 */
size_t queue_get_size(Queue *queue) {
    return queue->size;
}


/**
 * @brief :: Enqueue a node WITHOUT PRIORITY
 *
 * @param :: *queue :: Queue to insert to 
 * @param :: *data :: Item to be stored within the queue
 * 
 * @return :: bool :: Indication of success/failure 
 */
bool queue_enqueue(Queue *queue, void *data) {

	QueueNode *newNode = MACRO_MALLOC(1, sizeof(QueueNode) + queue->dataSize);
	newNode->priority = 0; //Default value
	newNode->next = NULL; 
	if(newNode == NULL) {
		return false;
	}
	if(queue->head != NULL) {
		queue->head->next = newNode; 
	} else { //Empty queue
		queue->tail = newNode;
    }
	queue->head = newNode;
	MACRO_MEMCPY(newNode->data, data, queue->dataSize);

    queue->size++;
	return true;
} 


/**
 * @brief :: Enqueue a node WITH PRIORITY
 *
 * @param :: *queue :: Queue to insert to 
 * @param :: *data :: Item to be stored within the queue
 * @param :: priority :: Priority 
 * 
 * @return :: bool :: Indication of success/failure 
 */
bool queue_priority_enqueue(Queue *queue, void *data, size_t priority) {

	QueueNode *newNode = MACRO_MALLOC(1, sizeof(QueueNode) + queue->dataSize);
	if(newNode == NULL) {
		return false;
	}

	newNode->priority = priority;
	QueueNode **current = &(queue->tail);
	while(1) {
		if(*current == NULL) { //End of list or empty list
			newNode->next = NULL;
			if(queue->tail == NULL) { //Empty list
				queue->head = newNode;
			}
			(*current) = newNode;
			break;

		} else if(newNode->priority > (*current)->priority) {
			newNode->next = (*current);
			(*current) = newNode;
			break;

		} else {
			current = &((*current)->next);
		}
	}
	queue->size++;
	MACRO_MEMCPY(newNode->data, data, queue->dataSize);
	return true;
} 



/**
 * @brief :: Peak a queue node 
 *
 * @param :: *queue :: Queue to peak from 
 * 
 * @return :: QueueNode :: Peaked node 
 */
QueueNode *queue_peak(Queue *queue) {
    
	return queue->tail;
} 


/**
 * @brief :: Dequeue node NOTE: CALLER MUST FREE NODE
 *
 * @param :: *queue :: Queue to dequeue from 
 * 
 * @return :: QueueNode :: Dequeued node 
 */
QueueNode *queue_dequeue(Queue *queue) {
    
    queue->size--;
	QueueNode *returnNode = queue->tail;
	queue->tail = queue->tail->next;
	if(queue->tail == NULL) { //Was last node in the list 
		queue->head = NULL;
	}

	return returnNode;
} 



/**
 * @brief :: Destroy memory associated with a queue 
 *
 * @param :: *queue :: Queue to destroy
 * 
 * @return :: void
 */
void queue_destroy(Queue *queue) {

    queue->size = 0;
	QueueNode *current = queue->tail;
	QueueNode *freeNode = queue->tail;
	queue->head = NULL;

	while(current != NULL) {
		current = current->next;
		freeNode = current;
		current = current->next;
		free(freeNode);
	}	

	return;
}




