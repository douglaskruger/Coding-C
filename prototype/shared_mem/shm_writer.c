/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: shm_writer.c$";

/*
 * Description:
 * This is a small demo on setting up a shared memory program using two processes
 * on the same server.
 *
 * Two components: shm_reader.c and shm_writer.c
 * A block of shared memory is created and then updated by the writer. The reader 
 * (separate process) can then see the updates.
 */
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <time.h>
#include <errno.h>
  
typedef struct TEM_IO
{
	char   Name[100];
	short  ObjectId;
	double Voltage;
	double Current;
	double Temperature;
 	double StateOfCharge;	
} tzTEM_IO;

int 
main() 
{ 
	int i;
	time_t t;

	/* Intializes random number generator */
	srand((unsigned) time(&t));

	// ftok to generate unique key 
	key_t key = ftok("shmfile",65); 

	// shmget returns an identifier in shmid 
	int shmid = shmget(key,4096000,0666|IPC_CREAT); 
	if (shmid < 0) 
	{ 
		printf("Could not get shared memory. Error=%d\n. Exiting.\n\n", errno);
		exit(1);
	}

	// shmat to attach to shared memory 
	tzTEM_IO *tem = (tzTEM_IO *) shmat(shmid,(void*)0,0); 

	/* Populate the initial values */
	printf("*** Initialization\n");
	for (i=0; i<10000; i++)
	{
		sprintf(tem[i].Name, "TEM I/O-%d", i);
		tem[i].Voltage = rand() % 20;
		tem[i].ObjectId = i +10000;
		tem[i].Current = rand() % 20;
		tem[i].Temperature = rand() % 20;
		tem[i].StateOfCharge = rand() % 20;

		printf("Object Index=%d\n",i);
		printf("  Name: %s\n", tem[i].Name); 
		printf("  ObjectId: %d\n", tem[i].ObjectId); 
		printf("  Voltage: %f\n", tem[i].Voltage); 
		printf("  Current: %f\n", tem[i].Current); 
		printf("  Temperature: %f\n", tem[i].Temperature); 
		printf("  StateOfCharge: %f\n", tem[i].StateOfCharge); 
	}
	printf("*** Running\n");
	while (1) 
	{
		printf("Update a million records\n");
		for (int count=0;count<1000000;count++)
		{
			i = rand() %10000;
			sprintf(tem[i].Name, "TEM I/O-%d-%d", i, rand() %80);
			tem[i].Voltage = rand() % 20;
			tem[i].Current = rand() % 20;
			tem[i].Temperature = rand() % 20;
			tem[i].StateOfCharge = rand() % 20;
		}
		for (int count=0;count<3;count++)
		{
			i = rand() %10000;
			printf("Object Index=%d\n",i);
			printf("  Name: %s\n", tem[i].Name); 
			printf("  ObjectId: %d\n", tem[i].ObjectId); 
			printf("  Voltage: %f\n", tem[i].Voltage); 
			printf("  Current: %f\n", tem[i].Current); 
			printf("  Temperature: %f\n", tem[i].Temperature); 
			printf("  StateOfCharge: %f\n", tem[i].StateOfCharge); 
		}
		sleep(1);
	}
	//detach from shared memory  
	shmdt(tem); 

    return 0; 
} 
