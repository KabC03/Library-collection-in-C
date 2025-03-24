#include "queue.h"
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
        printf("%u ", *((unsigned int*)ptr));
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
        printf("%d ", *((int*)ptr));
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

    printf("\tData size: %d\nSize: %zu\n", queue->dataSize, queue->size);

    printf("Data:\n");
    QueueNode *current = queue->head;
    while(current != NULL) { //Get to the last item in the list
        print_element(current->data);
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
 * @brief :: Enqueue a node 
 *
 * @param :: *queue :: Queue to insert to 
 * @param :: *data :: Item to be stored within the queue
 * 
 * @return :: bool :: Indication of success/failure 
 */
bool queue_enqueue(Queue *queue, void *data) {

    queue->size++;
	QueueNode *newNode = MACRO_MALLOC(1, sizeof(QueueNode) + queue->dataSize);
	if(newNode == NULL) {
		return false;
	}
	if(queue->head != NULL) {
		queue->head->next = newNode; 
	}
	newNode->next = NULL; 
	queue->head = newNode;
	MACRO_MEMCPY(newNode->data, data, queue->dataSize);

	if(queue->tail == NULL) { //Empty list
		queue->tail = newNode;
	}

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
	if(queue->head == queue->tail) { //Was last node in the list 
		queue->head = NULL;
	}
	queue->tail = queue->tail->next;

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




