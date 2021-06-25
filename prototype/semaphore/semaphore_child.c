/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: semaphore_child.c $";

/*
 * Description:
 *   Semaphore demo
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define SEM_NAME "semaphore_example"
#define ITERS 100

int 
main(void) 
{
	sem_t *semaphore = sem_open(SEM_NAME, O_RDWR);
	if (semaphore == SEM_FAILED) 
	{
		perror("sem_open(3) failed");
		exit(EXIT_FAILURE);
	}

	int i;
	for (i = 0; i < ITERS; i++) 
	{
		if (sem_wait(semaphore) < 0) 
		{
			perror("sem_wait(3) failed on child");
			continue;
		}

		printf("Child PID %ld acquired semaphore\n", (long) getpid());

		if (sem_post(semaphore) < 0) 
		{
			perror("sem_post(3) error on child");
		}
		printf("Child PID %ld released semaphore\n", (long) getpid());
		printf("Child PID %ld sleep\n", (long) getpid());

		sleep(1);
	}

	if (sem_close(semaphore) < 0)
		perror("sem_close(3) failed");

	return 0;
}
