/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: nano_time.c $";

/*
 * Description:
 *  This small program is used to demonstrate the subsecond time capabilities
 *  of the Linux UNIX system. It is a measure of elapsed real time using the 
 *  "clock_gettime" call. This is one of the most accurate ways to measure wallclock time.
 * 
 */
#include <stdio.h> 
#include <unistd.h> 
#include <time.h> 
#include <sys/time.h>   
#include <sys/resource.h> 

/*
 * struct timespec {
 *    time_t   tv_sec;         seconds 
 *    long     tv_nsec;        nanoseconds 
 * };  
 */
int
main () 
{ 
	struct timespec start, finish; 

	printf("******************************************************\n");
	printf("Executing nano_time program\n");
	printf("******************************************************\n");

	/* CLOCK_REALTIME
	   System-wide clock that measures real (i.e., wall-clock) time.   Setting  this  clock  
	   requires  appropriate privileges.  This clock is affected by discontinuous jumps in 
	   the system time (e.g., if the system administrator manually changes the clock), and 
	   by the incremental adjustments performed by adjtime(3) and NTP.
	*/
	clock_gettime(CLOCK_REALTIME, &start); 

	/* Sleep for one second to ensure we are over 1 second in our test */
	sleep(1);

	/* Elapse time by doing CPU activities via the loop */
	int i,j; for (i=0,j=0; i<100000000; i++) { j+=i*i; }     

	/* Get the finished time */
	clock_gettime(CLOCK_REALTIME, &finish); 

	/* Determine the elapsed time */
	long seconds = finish.tv_sec - start.tv_sec; 
	long ns = finish.tv_nsec - start.tv_nsec; 
	if (start.tv_nsec > finish.tv_nsec) 
	{ 
		--seconds; 
		ns += 1000000000; 
	} 
	printf("Elapsed seconds without ns: %ld\n", seconds); 
	printf("Elapsed nanoseconds: %ld\n", ns); 
	printf("Elapsed time (integer): %e\n", (double)seconds + (double)ns/(double)1000000000); 
	printf("Elapsed time (float): %3ld.%03ld\n", seconds, ns/1000000); 
} 
