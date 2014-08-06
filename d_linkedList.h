/*
	d_linkedList.h

	Programmer: Mohammad Juma, Antonio Orozco
	Date: 08/05/2014
	Purpose: Header file for the d_linkedList.c and test_dll_main.c programs

	d_linkedList.c implements a doubly linked list class-like container that can be used to
	store arbitrary length strings. This exercise introduces the basic form of Object Oriented
	Programming in C.
*/

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Class-like definitions to be used in this exercise

	Node is a class that is instantiated (an object created) whenever new data is added.
	List is the class that holds the meta-data and pointers to the first and last items on the
	list. Here is a list in the heap with two items in it.

	                                         +----------------------+
	                                         |                      |
	                    +-------\            v                      |
	+--------+          v        \      +--------+      +--------+  |
	| myList |      +--------+    \---->| data*  |  +-->| data*  |  |
	| List_p +----->| count 2|   / \----+ prior* |  |   | prior* +--+
	+--------+      | first* +--/       | next*  |--+   | next*  +----0 (NULL)
	                | last*  +-----+    +--------+      +--------+
	                +--------+     |                         ^
	                               |                         |
	                               +-------------------------+

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*********************************************************************************************************
 *                                        Preprocessor Directives
 ********************************************************************************************************/
#include <stdio.h>			// for FILE definition

#ifndef _D_LINKEDLIST_H_
#define _D_LINKEDLIST_H_

// error codes
#define NO_ERROR 0
#define INSERT_ERROR 1
#define DELETE_ERROR 2
#define PRINT_ERROR 3
#define NOT_FOUND_ERROR 4
#define SORT_ERROR 5

// control codes
#define INSERT_BEFORE 0
#define INSERT_AFTER 1
#define SORT_NONE 0
#define SORT_ASCEND 1
#define SORT_DESCEND 2
#define NOT_FOUND 0

// Meta-data codes
#define NO_ORDER 0
#define ASCEND_ORDER 1
#define DESCEND_ORDER 2

#define BUFFER_SIZE 100
#define MAX_CHARS_DATA 500	
#define MAX_LIST_NAME 20
/*********************************************************************************************************
 *                                              ADTs
 ********************************************************************************************************/
typedef struct node {		// the node will hold the data and the links for the list
	char * data;			// can be any arbitrary string, see toString() functions
	struct node * prev;		// use tag declaration so compiler realizes that this is a pointer
	struct node * next;		// to this class object
} Node;

typedef Node * Node_p;		// create a pointer for readability

typedef struct list {		// tag not really needed here, but there is consistency!
	char * listName;		// optional name of the list
	short order;			// New META_DATA to show if list is ordered
	int count;				// keep track of the number of items in the list
	Node_p first;			// points to first item on list, NULL if list is empty
	Node_p last;			// points to last item on list, NULL if list is empty, == first if
							// only one item in the list
} List;

typedef List * List_p;		// in case the user wants to instantiate list in the heap

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Function Prototypes
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
// Node function prototypes

Node_p createNode (const char * data);	
// returns pointer to the node and attaches data to the node
// via strcpy(). Returns NULL if not successful

char * toStringNode (Node_p myNode, char * buff);
// returns a string containing the representation of the
// node contents. buff must be pre-allocated and large
// enough to hold a node including the first 15 characters of
// the data

// List function prototypes

List_p createList (const char* lname); // returns pointer to a list object in the heap if successful
// NULL if not

char * toStringList (List_p myList, char * buff);
// returns a string containing the list head information
// including up to 20 characters of the list name


// CHANGED FUNCTION
void printList (List_p myList, FILE * output, int * error);
// First prints the list string returned by toStringList()
// then iterates through the list calling toStringNode()
// and prints each node's data
// If output == NULL stdout is assumed
// if an error is encountered the error value is set
// to PRINT_ERROR


//void printList (List_p myList, FILE* output);
// First prints the list string returned by toStringList()
// then iterates through the list calling toStringNode()
// and prints each node's data
// If output == NULL stdout is assumed

int appendData (List_p myList, const char * nodeData);
// creates a new node with nodeData and attaches it to the
// end of the list, updating the pointers and count
// returns NO_ERROR on success, INSERT_ERROR if not.

int insertDataAtFront (List_p myList, const char * nodeData);
// same as appendNode but puts the new node as the first item
// in the list. Returns NO_ERROR on success.

// NEW FUNCTION
int insertDataWithKey (List_p mylist, const char * key, const char * nodeData, int mode);
// Finds the node containing key, if it exists, and inserts
// the nodeData either before or after depending on the value
// of mode. mode == INSERT_BEFORE causes the insertion to be
// just before the found key, mode == INSERT_AFTER cause the
// insertion just after the found key. If the key is not
// found the function returns the NOT_FOUND_ERROR


// NEW FUNCTION
List_p sortList (List_p myList, int mode, int * error);
// Sorts the passed list, myList, in ascending or descending
// order depending on the value of mode. mode == SORT_ASCEND
// causes the list to be ordered in lexicographical order
// while SORT_DESCEND causes the list to be reverse ordered.
// Sets error to NO_ERROR and returns the pointer to the new
// list if successful. The original list is deleted
// (deallocated) on success. Otherwise the error is set to
// SORT_ERROR and the original pointer is returned


// NEW FUNCTION
char * removeDataFromTail (List_p myList);
// returns the last item in the list and destroys that
// node (do not destroy the data!)
// Returns NULL when no more items in the list

// NEW FUNCTION
char * removeDataFromHead (List_p myList);
// returns the first item in the list and destroys that
// node (do not destroy the data!) The second item then
// becomes the new first item.
// Returns NULL when no more items in the list


char * findData (List_p myList, const char * searchData);
// finds the node containing the searchData and returns a
// string containing the data without affecting the node

char * removeData (List_p myList, const char * searchData);
// Finds and removes the node containing searchData if found
// returns a string containing the search data if successful
// NULL otherwise

// Helper functions (could be hidden in .c file)

Node_p findNode (List_p myList, const char * searchData);
// Same as findData but used to get the pointer to the node
// Used by findData and removeData

// NEW FUNCTION
int destroyNode (Node_p myNode);
// deletes (deallocate) the data string and then frees the
// node pointer

// Status functions for Node
// NEW FUNCTION
char * getDataFromNode (Node_p myNode);
// returns the pointer to the data in myNode. If the pointer
// is NULL that means the node has no data

// NEW FUNCTION
Node_p getSuccessorNode (Node_p myNode);
// returns the pointer to the successor node if one exists
// otherwise NULL

// NEW FUNCTION
Node_p getPredecessorNode (Node_p myNode);
// returns the pointer to the predecessor node if one exists
// otherwise NULL

// NEW FUNCTION
int destroyList (List_p myList);
// Destroys all nodes in the list and frees the list head

// Status functions for List
// NEW FUNCTION
int sizeList (List_p myList);
// returns the count of nodes in the list

// NEW FUNCTION
int getSortOrder (List_p myList);		
// returns the order code

// NEW FUNCTION
int readList (List_p myList, FILE * input, int mode);
// Reads a file of text lines, each line a data object, and
// fills the initialized myList. If mode == SORTED_ORDER the
// list is ordered lexicographically (by insertion sort).
// input contains a pointer to a file to be read.

char** insertion_sort_ascend(char**, int);
//This function sorts a char array in accending order by insertion sort.

char** insertion_sort_descend(char**, int);
//This function sorts a char array in descending order by insertion sort.

char* remove_mem(char* toFree);
#endif
