/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: thread_example2.c $";

/*
 * Description:
 *   The following program to demonstrate Posix threads in C under Linux
 */
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 
  
// Let us create a global variable to change it in threads 
int g = 0; 
  
// The function to be executed by all threads 
void * 
myThreadFun(void *vargp) 
{ 
	// Store the value argument passed to this thread 
	int *myid = (int *)vargp; 

	// Let us create a static variable to observe its changes 
	static int s = 0; 

	// Change static and global variables 
	++s; 
    ++g; 

	// Print the argument, static and global variables 
	printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, ++g); 

    return NULL;
} 
  
int 
main() 
{ 
	int i; 
	pthread_t tid; 
	pthread_t tid2; 

	// Let us create three threads 
	for (i = 0; i < 3; i++) 
	{
		pthread_create(&tid, NULL, myThreadFun, (void *)&tid2); 
	}
	pthread_exit(NULL); 
	return 0; 
} 
