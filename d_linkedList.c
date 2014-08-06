/*
	d_linkedList.c

	Programmer: Mohammad Juma, Antonio Orozco
	Date: 08/05/2014
	Purpose: d_linkedList.c implements a doubly linked list class-like container that can be used to
	store arbitrary length strings. This exercise introduces the basic form of Object Oriented
	Programming in C.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "d_linkedList.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *	Node ADT
 *
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/************************************************************************************************************
 * createNode
 *
 * Synopsis: Node_p createNode (const char * data)
 *
 * Description: Creates a new Node object in the heap. If actual data was passed to this function (data
 * is non-NULL, then a string is allocated in the heap and the data is copied into it. Pointers to next and
 * prior are initialized to NULL.
 *
 * Returns: A pointer to the new node in the heap.
 *
 ************************************************************************************************************/
Node_p createNode (const char * data) {
	Node_p ret = (Node_p) malloc (sizeof(Node));

	if (data != NULL) {
		ret->data = (char *) malloc(sizeof(char) * strlen(data)+1);
		strcpy(ret->data, data);
	}
	ret->next = NULL;	// make certain new node pointers are initialized to NULL
	ret->prev = NULL;
	return ret;
}
/************************************************************************************************************
 * toStringNode
 *
 * Synopsis: char * toStringNode(Node_p myNode, char * buff)
 *
 * Description: If node is a valid pointer the function creates a string representing the contents of the
 * node along with indicators of its prior and next pointer statuses. The string is built in the buff characters
 * array and the calling function needs to ensure the size of that buffer wherever it is allocated.
 *
 * Returns: A pointer to the string representation of the node.
 *
 ************************************************************************************************************/
char* toStringNode (Node_p myNode, char * buff) {
	if (myNode == NULL) return NULL;
	if (buff == NULL) return NULL;

	char tempBuff[MAX_CHARS_DATA+2];

	sprintf (buff, "\nNODE: ");			// from string.h
	strncpy(tempBuff, myNode->data, MAX_CHARS_DATA);
	strcat (buff, tempBuff);
	if (myNode->prev) 
		strcat (buff, "\nHAS PRIOR\n");
	else 
		strcat(buff, "\nNO PRIOR\n");	// should be first in list
	if (myNode->next) 
		strcat (buff, "HAS NEXT\n");
	else 
		strcat (buff, "NO NEXT - End of List\n");
	return buff;
}

/************************************************************************************************************
 * findNode
 *
 * Synopsis: Node_p findNode (List_p myList, const char * searchData)
 *
 * Description: If the list contains valid nodes, then it starts iterating through the list until
 * a match is found.
 *
 * Returns: A pointer to the node in the list.
 *
 ************************************************************************************************************/
Node_p findNode (List_p myList, const char * searchData) {
	Node_p curr = myList->first;
		while (curr != NULL) {
			if (!strcmp(searchData, curr->data)) //returns 0 if equals
				return curr; 
				curr = curr->next;
		}
	return NULL;
}
/************************************************************************************************************
 * destroyNode
 *
 * Synopsis: int destroyNode(Node_p myNode)
 *
 * Description: If node is a valid pointer the function frees the allocated memory for the data string and
 * then frees the node itself.
 *
 * Returns: A DELETE_ERROR if node is not a valid pointer, NO_ERROR otherwise.
 *
 ************************************************************************************************************/
int destroyNode(Node_p myNode) {
	if (!myNode) 
		return DELETE_ERROR;
	if (myNode->data) 
		free (myNode->data);
		free (myNode);
	return NO_ERROR;
}
/************************************************************************************************************
 * getDataFromNode
 *
 * Synopsis: char * getDataFromNode(Node_p myNode)
 *
 * Description: If node is a valid pointer the function copies the data to a new string in the heap and
 * returns the pointer to that new string. The data in the node is left alone.
 *
 * Returns: A pointer to the new string in the heap.
 *
 ************************************************************************************************************/
char * getDataFromNode (Node_p myNode) {
	if (!myNode) 
		return NULL;
	char * data = (char *) malloc (sizeof(char) * strlen(myNode->data)+1);
	strcpy (data, myNode->data);
	return data;
}
/************************************************************************************************************
 * getPredecessorNode
 *
 * Synopsis: Node_p getPredecessorNode (Node_p myNode)
 *
 * Description: If node is a valid pointer the function creates a new node in the heap that points to
 * the previous node.
 *
 * Returns: A pointer to the preceding node in the heap.
 *
 ************************************************************************************************************/
Node_p getPredecessorNode (Node_p myNode) {
	if (!myNode)
		return NULL;
	if (!myNode->prev)
		return NULL;
	Node_p ret_node = createNode(getDataFromNode(myNode->prev));
	return ret_node;
}
/************************************************************************************************************
 * getSuccessorNode
 *
 * Synopsis: Node_p getSuccessorNode (Node_p myNode)
 *
 * Description: If node is a valid pointer the function creates a new node in the heap that points to
 * the following node.
 *
 * Returns: A pointer to the successor node in the heap.
 *
 ************************************************************************************************************/
Node_p getSuccessorNode (Node_p myNode) {
	if (!myNode)
		return NULL;
	if (!myNode->next)
		return NULL;
	Node_p ret_node = createNode(getDataFromNode(myNode->next));
	return ret_node;
}/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *	List ADT
 *
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/************************************************************************************************************
 * createList
 *
 * Synopsis: List_p createList (const char* lname)
 *
 * Description: Creates a new list object in the heap. If actual data was passed to this function (data
 * is non-NULL, then a string is allocated in the heap and the data is copied into it. Pointers to count,
 * , sort order, first node, and last node are initialized to NULL.
 *
 * Returns: A pointer to the new list in the heap.
 *
 ************************************************************************************************************/
List_p createList (const char* lname) {
	List_p myList = (List_p) malloc (sizeof(List));
	if (lname != NULL) {
		myList->listName = (char*) malloc (sizeof(char) * strlen(lname) + 1);
		strcpy(myList->listName, lname);
	}
	myList->count = 0;
	myList->order = NO_ORDER;
	myList->first = NULL;
	myList->last = NULL;
	return myList;
}
/************************************************************************************************************
 * toStringList
 *
 * Synopsis: char* toStringList (List_p myList, char* buff)
 *
 * Description: This function prints a list's information, such as the name of the list, a number of
 * of items the list contains, and the information to the first and last node (if the exit).
 *
 * Returns: A pointer to the string contain the list's information.
 *
 ************************************************************************************************************/
char* toStringList (List_p myList, char* buff) {
	if (myList == NULL || buff == NULL)
		return NULL;

	char tempBuff[MAX_LIST_NAME + 2];

	sprintf(buff, "\nList name: ");
	strncpy(tempBuff, myList->listName, MAX_LIST_NAME);
	strcat(buff, tempBuff);

	char str[MAX_CHARS_DATA];
	sprintf(str, "%d", myList->count); //convert int to string
	strcat(buff, "\nItems in list: ");
	strcat(buff, str);
	strcat(buff, "\n");
	if (myList->first) {
		strcat(buff, "First: ");
		strcat(buff, myList->first->data);
		strcat(buff, "\n");
	}
	else
		strcat(buff, "NO FIRST\n");
	if (myList->last) {
		strcat(buff, "Last: ");
		strcat(buff, myList->last->data);
		strcat(buff, "\n");
	}
	else
		strcat(buff, "NO LAST\n");
	return buff;
}
/************************************************************************************************************
 * findData
 *
 * Synopsis: char* findData (List_p myList, const char * searchData)
 *
 * Description: This function uses findNode to return a pointer to the data of the node.
 *
 * Returns: A pointer to the string contain the node's data.
 *
 ************************************************************************************************************/
char* findData (List_p myList, const char * searchData) {
	return findNode (myList, searchData)->data;
}
/************************************************************************************************************
 * printList
 *
 * Synopsis: void printList (List_p myList, FILE* output, int * error)
 *
 * Description: This function prints the list to a file and the screen as well. Changes the value of error
 * if the the output fle does not exit.
 *
 * Returns: nothing (void).
 *
 ************************************************************************************************************/
void printList (List_p myList, FILE* output, int * error) {
	Node_p temp = myList->first;
	char buffer[BUFFER_SIZE];
	//output = fopen("test_file.txt", "a");
	if (output == NULL) {
		fprintf(stdout, "File not found.");
		*error = PRINT_ERROR;
	} else {
		fprintf(output, toStringList(myList, buffer));
	}

	printf("%s", toStringList(myList, buffer));

	while (temp != NULL) {
		if (error == NO_ERROR)
			fprintf(output, toStringNode(temp, buffer));
		printf("%s\n", toStringNode (temp, buffer));
		temp = temp->next;
	}
	//fclose(output);
}
/************************************************************************************************************
 * appendData
 *
 * Synopsis: int appendData (List_p myList, const char * nodeData)
 *
 * Description: This function creates a node and adds it to the end of the list
 * if nodeData is valid and if the myList exits.
 *
 * Returns: NO_ERROR on success, else INSERT_ERROR on failure.
 *
 ************************************************************************************************************/
int appendData (List_p myList, const char * nodeData) {
	if (nodeData == NULL || nodeData == NULL)
		return INSERT_ERROR;

	Node_p newNode = createNode(nodeData);

	if (myList->first == NULL) {
		myList->first = newNode;
		myList->last = newNode;
		myList->count++;
		return NO_ERROR;
	}
	newNode->prev = myList->last;
	myList->last->next = newNode;
	newNode->next = NULL;
	myList->last = newNode;
	myList->count++;
	return NO_ERROR;
}
/************************************************************************************************************
 * insertDataAtFront
 *
 * Synopsis: int insertDataAtFront (List_p myList, const char * nodeData)
 *
 * Description: This function creates a node and adds it to the front of the list
 * if nodeData is valid and if the myList exits.
 *
 * Returns: NO_ERROR on success, else INSERT_ERROR on failure.
 *
 ************************************************************************************************************/
int insertDataAtFront (List_p myList, const char * nodeData) {
	if (myList == NULL || nodeData == NULL)
		return INSERT_ERROR;

	Node_p newNode = createNode(nodeData);

	if (myList->first == NULL) {
		myList->first = newNode;
		myList->last = newNode;
		myList->count++;
		return NO_ERROR;//First node created in the list successful
	}
	myList->first->prev = newNode;
	newNode->next = myList->first;
	newNode->prev = NULL;
	myList->first = newNode;
	myList->count++;
	return NO_ERROR;
}
/************************************************************************************************************
 * removeData
 *
 * Synopsis: char * removeData (List_p myList, const char * searchData)
 *
 * Description: This function searches through the list until a match is found. Once the match is found,
 * it removes the data from the node. However, the node still exists.
 *
 * Returns: The data removed from the node.
 *
 ************************************************************************************************************/
char * removeData (List_p myList, const char * searchData) {
	Node_p curr = myList->first;
	if (myList->count > 0)
		while (curr != NULL) {
			if (!strcmp(searchData, curr->data)) { //returns 0 if equals
					if (curr->prev != NULL && curr->next != NULL) {
						curr->prev->next = curr->next;
						curr->next->prev = curr->prev;
					}
					else if (curr->prev == NULL && curr->next != NULL) {
						curr->next->prev = NULL;
						myList->first = curr->next;
					}
					else if (curr->prev != NULL && curr->next == NULL) {
						curr->prev->next = NULL;
						myList->last = curr->prev;
					}
					else {
						myList->count--;
						myList->first = NULL;
						myList->last = NULL;
						char* temp = curr->data;
						free(findNode(myList,curr->data));
						return temp;
					}
					myList->count--;
					char* temp = curr->data;
					free(findNode(myList,curr->data));
					return temp;
			}
				curr = curr->next;
		}

	return NULL;
}
/************************************************************************************************************
 * destroyList
 *
 * Synopsis: int destroyList (List_p myList)
 *
 * Description: This function destroys every node in the list first, then it destroyes the memory allocated
 * for the list it self.
 *
 * Returns: NO_ERROR if success, else DELETE_ERROR.
 *
 ************************************************************************************************************/
int destroyList (List_p myList) {
	if (myList->count == 0 || myList == NULL)
		return DELETE_ERROR;

	Node_p curr = myList->first;
	Node_p next;
	while (curr != NULL) {
		next = curr->next;
		destroyNode(curr);
		myList->count--;
		curr = next;
	}
	free(myList);
	return NO_ERROR;
}
/************************************************************************************************************
 * sizeList
 *
 * Synopsis: int sizeList(List_p myList)
 *
 * Description: This function simply returns the size of the list.
 *
 * Returns: # of items if success, else NOT_FOUND.
 *
 ************************************************************************************************************/
int sizeList(List_p myList) {
	if (myList == NULL)
		return NOT_FOUND;
	return myList->count;
}
/************************************************************************************************************
 * getSortOrder
 *
 * Synopsis: int getSortOrder(List_p myList)
 *
 * Description: This function simply returns the order that list was sorted.
 *
 * Returns: sort order if success, else NOT_FOUND.
 *
 ************************************************************************************************************/
int getSortOrder(List_p myList) {
	if (myList == NULL)
		return NOT_FOUND;
	return myList->order;
}
/************************************************************************************************************
 * removeDataFromHead
 *
 * Synopsis: char* removeDataFromHead (List_p myList)
 *
 * Description: This function removes the node at the front of the list. The following node will then
 * become the first in the list.
 *
 * Returns: node's data if success, else NULL.
 *
 ************************************************************************************************************/
char* removeDataFromHead (List_p myList) {
	Node_p curr = myList->first;

	if (curr->next != NULL) {
		curr->next->prev = NULL;
		myList->first = curr->next;
		curr->next = NULL;
		myList->count--;
		char* temp = curr->data;
		free(findNode(myList,curr->data));
		return temp;
	} else if (curr->next == NULL && curr != NULL) {
		myList->first = NULL;
		myList->last = NULL;
		myList->count--;
		char* temp = curr->data;
		free(findNode(myList,curr->data));
		return temp;
	} else
		return NULL;
}
/************************************************************************************************************
 * removeDataFromTail
 *
 * Synopsis: char* removeDataFromTail(List_p myList)
 *
 * Description: This function removes the node at the end of the list. The preceding node will then
 * become the last in the list.
 *
 * Returns: node's data if success, else NULL.
 *
 ************************************************************************************************************/
char* removeDataFromTail(List_p myList) {
	Node_p curr = myList->last;

	if (curr->prev != NULL) { //ensure its the last item.
		curr->prev->next = NULL;
		myList->last = curr->prev;
		curr->prev = NULL;
		myList->count--;
		char* temp = curr->data;
		free(findNode(myList, curr->data));
		return temp;
	} else if (curr->prev == NULL && curr != NULL) {
		myList->first = NULL;
		myList->last = NULL;
		myList->count--;
		char* temp = curr->data;
		free(findNode(myList, curr->data));
		return temp;
	} else
		return NULL;
}
/************************************************************************************************************
 * sortList
 *
 * Synopsis: List_p sortList (List_p myList, int mode, int* error)
 *
 * Description: This function creates a new list to hold the sorted data. It creates a temp array in the
 * heap that copies all the node's data. Then it sorts that temp array according to the sort order
 * pass through the arguement. The sort is done by an implementation of an insertion sort.
 *
 * Returns: The new sorted list.
 *
 ************************************************************************************************************/
List_p sortList (List_p myList, int mode, int* error) {
	List_p sorted_list = createList(myList->listName);

	while(myList->count)
		appendData(sorted_list, removeDataFromHead(myList));


	Node_p curr = sorted_list->first;
	int i = 0, size = 0;
	char** array = (char**) malloc (sizeof(char*));

	while (curr != NULL) {
		array[size] = (char*) malloc (sizeof(char) * strlen(curr->data));
		array[size] = curr->data;
		size++;
		curr = curr->next;
	}

	if (mode == ASCEND_ORDER) {
		sorted_list->order = ASCEND_ORDER;
		printf("Order: %d\n", ASCEND_ORDER);
		array = insertion_sort_ascend(array, size);
		curr = sorted_list->first;
		while (curr != NULL) {
			curr->data = array[i];
			i++;
			curr = curr->next;
		}
	} 
	if (mode == DESCEND_ORDER) {
		sorted_list->order = DESCEND_ORDER;
		printf("Order: %d\n", DESCEND_ORDER);
		array = insertion_sort_descend(array, size);
		curr = sorted_list->first;
		while (curr != NULL) {
			curr->data = array[i];
			i++;
			curr = curr->next;
		}
	}
	/*for(i = 0; i < size; i++) {
		free(array[i]);
	}
	free(array);*/
	free(myList);
	return sorted_list;
}
/************************************************************************************************************
 * insertion_sort_ascend
 *
 * Synopsis: char** insertion_sort_ascend(char** array, int size)
 *
 * Description: This function sorts a char array in accending order by insertion sort.
 *
 * Returns: The sorted char array.
 *
 ************************************************************************************************************/
char** insertion_sort_ascend(char** array, int size) {
	char* temp = NULL;
	int i = 0, j;
	char** ret_array = array;

	while (i < size) {
		for (j = i + 1; j < size; j++) {
			if (strcmp (ret_array[i], ret_array[j]) > 0) {
				temp = ret_array[i];
				ret_array[i] = ret_array[j];
				ret_array[j] = temp;
			}
		}
		i++;
	}
	return ret_array;
}
/************************************************************************************************************
 * insertion_sort_descend
 *
 * Synopsis: char** insertion_sort_descend(char** array, int size)
 *
 * Description: This function sorts a char array in descending order by insertion sort.
 *
 * Returns: The sorted char array.
 *
 ************************************************************************************************************/
char** insertion_sort_descend(char** array, int size) {
	char* temp = NULL;
	int i = 0, j;
	char** ret_array = array;

	while (i < size) {
		for (j = i + 1; j < size; j++) {
			if (strcmp (ret_array[i], ret_array[j]) < 0) {
				temp = ret_array[i];
				ret_array[i] = ret_array[j];
				ret_array[j] = temp;
			}
		}
		i++;
	}
	return ret_array;
}

int readList (List_p myList, FILE* input, int mode)  {
	if (input == NULL || myList == NULL) {
		return NOT_FOUND_ERROR;
	} else {

		/*//char** str_array = (char**) malloc (sizeof(char*));
		char* line = (char*) malloc (sizeof(char));
		char ch;
		int count = 0, i = 0;
		while (ch != EOF) {
			ch = fgetc(input);
			
			if (ch == '\n') {
				count++;
				line = '\0';
				line + count;
				//str_array[i] = (char*) malloc (sizeof(char)*count);
				//strcpy(str_array, line);
				appendData(myList, line);
				i++;
				count = 0;
				line = remove_mem(line);
			}
			line = &ch;
			line + count;
            count++;
		}*/

    	char node_data[MAX_CHARS_DATA];
		/*char node_data[MAX_CHARS_DATA];
		printf("Inside of here\n");
		int x;
		int count = 0;
        while  ((x = fgetc(input) ) != '\n') {
        	node_data[count] = 
        	count++;
            printf( "count: %d   %c", count, x );
        }*/
		while (fgets (node_data, strlen(node_data), input)) {
			//fputs(node_data, stdout);
			printf("%s", node_data);
			appendData(myList, node_data);
   		}
		//fclose(input);
		return NO_ERROR;
	}
}

char* remove_mem(char* toFree) {
	free(toFree);
	char* ret_p = (char*) malloc (sizeof(char));
	return ret_p;
}

int main(int argc, char const *argv[]) {
	FILE* file = fopen( argv[1], "r" );
	List_p list = createList("My List");

	if (!file) {
        printf( "Could not open file.\n" );
        printf("Please pass in the file name via terminal: ");
        printf("example: $ ./programname nameoffile.txt\n");
    } else {

    	if (!readList(list, file, 0));
    		printf("Finished reading file.\n");
    	char selection;
    	printf("Would you like to print contents in the linked list? (y/n) ");
    	scanf("%c", &selection);
    	printf("%c\n", selection);
    	if (selection == 'y') {
    		int* error = 0;
    		FILE* no_file = fopen("contents.txt", "w");
    		printf("In HERE!\n");
    		printList (list, no_file, error);
    		fclose(no_file);
    	}

        /*int x;
        while  ((x = fgetc(file) ) != EOF) {
            printf( "%c", x );
        }*/
        fclose( file );
    }
	return 0;
}
