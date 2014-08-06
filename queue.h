/*
	queue.h

	Programmer: Mohammad Juma, Antonio Orozco
	Date: 08/05/2014
	Revision: 1.0

	Purpose: Header file for the queue ADT implemented with a doubly linked list.
*/

/*********************************************************************************************************
 *                                        Preprocessor Directives
 ********************************************************************************************************/
#include "d_linkedList.h"

#define PUSH_ERROR -1
#define QUEUE_FULL_ERROR -2

#define NO_LIMIT -1

#define TRUE 1
#define FALSE 0

/*********************************************************************************************************
 *                                              ADTs
 ********************************************************************************************************/

typedef struct queue {
	List_p queue;		// implement the queue using a doubly linked list
	int limit;			// used to enforce a limited queue object
} Queue;

typedef Queue * Queue_p;

/*********************************************************************************************************
 *                                           Prototypes
 ********************************************************************************************************/
Queue_p createQueue(char * title, int limit);
// constructor for a queue object

void destroyQueue(Queue_p queue);				
// destructor for an instantiated queue

int isEmpty (Queue_p queue);					
// returns TRUE or FALSE

int isFull (Queue_p queue);						
// returns TRUE if queue->count == limit

char * pop (Queue_p queue);						
// returns a pointer to data in the heap if successful,
// NULL otherwise

int push (Queue_p queue, char * data);			
// returns TRUE if successful, error code if not
