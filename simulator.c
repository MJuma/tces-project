/*
	simulator.c

	Programmer: Mohammad Juma, Antonio Orozco
	Date: 08/05/2014
	Revision: 0

	Purpose: Simulate a round-robin operating system scheduler

	simulator.c is ...

*/

/*********************************************************************************************************
 *                                        Preprocessor Directives
 ********************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#include "queue.h"

/*********************************************************************************************************
 *                                           Functions
 ********************************************************************************************************/

/*	Function: main
	Uses library: Standard I/O
	Input: 
	Output: 
*/
int main (int argc, char *argv[]) {
	int max_proc;
	int avg_proc;
	int max_ticks;
	int mean_times;
	int time_slice;

	if ( argc != 6 ) { /* argc should be 2 for correct execution */
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s max_proc, avg_proc, max_ticks, mean_times, time_slice", argv[0] );
    }
    else {
    	max_proc = atoi(argv[1]);
    	avg_proc = atoi(argv[2]);
    	max_ticks = atoi(argv[3]);
    	mean_times = atoi(argv[4]); 
    	time_slice = atoi(argv[5]);

    	printf("%d | %d | %d | %d | %d\n", max_proc, avg_proc, max_ticks, mean_times, time_slice);
    }
	return 0;
}