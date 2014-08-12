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
#include <math.h>

#include "simulator.h"
#include "queue.h"

/*********************************************************************************************************
 *                                        Global Variables
 ********************************************************************************************************/
// Maximum number of processes for a run (the actual number will be randomly
// determined at runtime but will be no greater than this input value).
int max_proc;
// Average number of processes that will terminate on fixed times 
// (the others are assumed to run in infinite loops). This value is input as a
// percentage of the number of processes (above).
int avg_proc;
// Maximum time ticks to run the simulation (a default minimum might be 50,000 cycles
// and allow the user to specify at top end number).
int max_ticks;
// Mean time between starts (this is the mean of an exponential random distribution
// - the actual starts will be determined at runtime).
int mean_times;
// Specific time slice value (a number between 200 microseconds and 1 milisecond that
// designates how much running time each process is allotted per time slice).
int time_slice;
int counter;
int total_run_count;
int id;
Queue_p ready_queue;
Process_p curr_proc;
Process_p idle_proc;

/*********************************************************************************************************
 *                                           Functions
 ********************************************************************************************************/
/*	Function: main
	Uses library: Standard I/O
	Input: 
	Output: 
*/
int main (int argc, char *argv[]) {

	if ( argc != 6 ) { /* argc should be 2 for correct execution */
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s max_proc, avg_proc, max_ticks, mean_times, time_slice\n", argv[0] );
    }
    else {
    	max_proc = atoi(argv[1]);
    	avg_proc = atoi(argv[2]);
    	max_ticks = atoi(argv[3]);
    	mean_times = atoi(argv[4]); 
    	time_slice = atoi(argv[5]);

    	//printf("%d | %d | %d | %d | %d\n", max_proc, avg_proc, max_ticks, mean_times, time_slice);
    }
	return 0;
}

void start_loop () {
	int randnum = 0;
	counter = 0;
	total_run_count = 0;
	id = 0;
	ready_queue = createQueue("Ready Queue", max_proc);
	idle_proc = createProcess();
	curr_proc = idle_proc;
	for (;;) {
		counter++;
		curr_proc->run_count++;

		if (counter % time_slice == 0) {
			scheduler(0);
		}

		if (expon(avg_proc) > mean_times) {
			Process_p new_proc = createProcess();
			enqueue(ready_queue, new_proc);
		}

		if (expon(avg_proc) == mean_times) {
			scheduler(1);
		}

		if (counter == max_ticks){
			printf("%d\n", total_run_count);
			break;
		}
	}
}

void scheduler(int terminate) {
	if (terminate) {
		total_run_count += curr_proc->run_count;
		free(curr_proc);
	}
	else {
		enqueue(ready_queue, curr_proc);
	}
	curr_proc = dequeue(ready_queue);

	if (isEmpty(ready_queue)) {
		enqueue(ready_queue, idle_proc);
	}
}

Process_p createProcess() {
	Process_p proc = (Process_p) malloc (sizeof(Process));
	proc->id = id++;
	proc->run_count = 0;
	return proc;
}

//===========================================================================
//=  Function to generate exponentially distributed random variables        =
//=    - Input:  Mean value of distribution                                 =
//=    - Output: Returns with exponentially distributed random variable     =
//===========================================================================
double expon(double x) {
  double z;                     // Uniform random number (0 < z < 1)
  double exp_value;             // Computed exponential value to be returned

  // Pull a uniform random number (0 < z < 1)
  do {
    z = rand_val();
  }
  while ((z == 0) || (z == 1));

  // Compute exponential random variable using inversion method
  exp_value = -x * log(z);

  return(exp_value);
}

//=========================================================================
//= Multiplicative LCG for generating uniform(0.0, 1.0) random numbers    =
//=   - x_n = 7^5*x_(n-1)mod(2^31 - 1)                                    =
//=   - With x seeded to 1 the 10000th x value should be 1043618065       =
//=   - From R. Jain, "The Art of Computer Systems Performance Analysis," =
//=     John Wiley & Sons, 1991. (Page 443, Figure 26.2)                  =
//=========================================================================
double rand_val() {
  const long  a =      16807;  // Multiplier
  const long  m = 2147483647;  // Modulus
  const long  q =     127773;  // m div a
  const long  r =       2836;  // m mod a
  static long x = 1;               // Random int value
  long        x_div_q;         // x divided by q
  long        x_mod_q;         // x modulo q
  long        x_new;           // New x value

  // RNG using integer arithmetic
  x_div_q = x / q;
  x_mod_q = x % q;
  x_new = (a * x_mod_q) - (r * x_div_q);
  if (x_new > 0)
    x = x_new;
  else
    x = x_new + m;

  // Return a random value between 0.0 and 1.0
  return((double) x / m);
}