/*
	queue.c

	Programmer: Mohammad Juma, Antonio Orozco
	Date: 08/05/2014
	Revision: 1.0

	Purpose: queue.c is the implementation of a queue ADT using an underlying List container class. This class
	is a wrapper that inherits the List functionality but restricts it to those operations that are
	valid for a queue object.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *	Queue ADT
 *
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/************************************************************************************************************
 * createQueue
 *
 * Synopsis: Stack_p createQueue(char * title, int limit)
 *
 * Description: This function allocates memory in the heap for a queue that will be implement
 * by a doubly linked list.
 *
 * Returns: A pointer to the queue in the heap.
 *
 ************************************************************************************************************/
Queue_p createQueue(char * title, int limit) {
	Queue_p my_queue = (Queue_p) malloc (sizeof(Queue));
	my_queue->queue = createList(title);
	my_queue->limit = limit;
	return my_queue;
}
/************************************************************************************************************
 * destroyQueue
 *
 * Synopsis: void destroyQueue(Stack_p queue)
 *
 * Description: This function destroys the list in the heap, then it destroyes the queue in the heap.
 *
 * Returns: Nothing (void).
 *
 ************************************************************************************************************/
void destroyQueue(Queue_p queue) {
	if (queue != NULL && queue->queue != NULL) {
		destroyList(queue->queue);
		queue->limit = 0;
		free(queue);
	} else
		printf("Queue is NULL\n");
}		
/************************************************************************************************************
 * isEmpty
 *
 * Synopsis: int isEmpty (Queue_p queue)
 *
 * Description: This function checks to see if the queue is empty by simply returning the # of items
 * in the queue.
 *
 * Returns: # of items in the queue, if 0, then queue is empty.
 *
 ************************************************************************************************************/
int isEmpty (Queue_p queue) {
	if (queue == NULL || queue->queue == NULL)
		return FALSE;
	else
		return sizeList(queue->queue);
}					
/************************************************************************************************************
 * isFull
 *
 * Synopsis: int isFull (Queue_p queue)
 *
 * Description: This function checks to see if the queue is full by comparing the # of items
 * in the queue with the queue limit.
 *
 * Returns: TRUE if full(1), FALSE is not(0).
 *
 ************************************************************************************************************/
int isFull (Queue_p queue) {
	if (queue == NULL || queue->queue == NULL)
		return FALSE;

	if (sizeList(queue->queue) == queue->limit)
		return TRUE;
	else 
		return FALSE;
}
/************************************************************************************************************
 * dequeue
 *
 * Synopsis: char * dequeue (Queue_p queue)
 *
 * Description: This function pops the last item added to the queue. In other words, it removes from end
 * of the list. It helps to think about it as if your stacking plates on top of each other. So a pop
 * is simply removing the very bottom plate added(the last item added to the queue).
 *
 * Returns: A pointer to the data in the heap if successful, NULL otherwise.
 *
 ************************************************************************************************************/
char * dequeue (Queue_p queue) {
	if (queue == NULL || queue->queue == NULL)
		return NULL;
	else 
		return removeDataFromTail(queue->queue);
}			
/************************************************************************************************************
 * enqueue
 *
 * Synopsis: int enqueue (Queue_p queue, char * data)
 *
 * Description: This function pushes the items to the end of the queue. In other words, it's adding
 * to end of the list. Think about as if your stacking plates on underneath of each other.
 *
 * Returns: TRUE if successful, error code if not.
 *
 ************************************************************************************************************/	
int enqueue (Queue_p queue, char * data) {
	if (queue == NULL || queue->queue == NULL || data == NULL)
		return PUSH_ERROR;
	else
		return appendData(queue->queue, data);
}		


/*int main() {
	Queue_p my_queue = createQueue("My First Queue", 5);
	printf("\nName of queue: %s, and the queue limit = %d\n", 
			my_queue->queue->listName,
			my_queue->limit);
	printf("Queue items: %d\n", isEmpty(my_queue));
	printf("Push: %d\n", push(my_queue, "Antonio"));
	printf("Queue items: %d\n", isEmpty(my_queue));
	printf("Push: %d\n", push(my_queue, "Orozco"));
	printf("Push: %d\n", push(my_queue, "Jayden"));
	printf("Queue items: %d\n", isEmpty(my_queue));

	printf("Pop: %s\n", pop(my_queue));
	printf("Queue items: %d\n", isEmpty(my_queue));
	printf("Pop: %s\n", pop(my_queue));
	printf("Queue items: %d\n", isEmpty(my_queue));
	printf("Pop: %s\n", pop(my_queue));
	printf("Queue items: %d\n", isEmpty(my_queue));

	printf("Push: %d\n", push(my_queue, "String1"));
	printf("Push: %d\n", push(my_queue, "String2"));
	printf("Push: %d\n", push(my_queue, "String3"));
	printf("Push: %d\n", push(my_queue, "String4"));
	printf("Push: %d\n", push(my_queue, "String5"));

	printf("Is the queue full? %d\n", isFull(my_queue));
	printf("Pop: %s\n", pop(my_queue));
	printf("Is the queue full? %d\n", isFull(my_queue));

	printf("Queue items before destroyQueue: %d\n", isEmpty(my_queue));
	destroyQueue(my_queue);
	printf("Queue items after destroyQueue: %d\n", isEmpty(my_queue));

	return 0;
}*/
