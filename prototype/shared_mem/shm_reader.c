/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: shm_reader.c$";

/*
 * Description:
 * This is a small demo on setting up a shared memory program using two processes
 * on the same server.
 */
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
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

	while (1) 
	{
		for (int count=0;count<100;count++)
		{
			int i = rand() %10000;
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

	// destroy the shared memory 
	shmctl(shmid,IPC_RMID,NULL); 

	return 0; 
} 
