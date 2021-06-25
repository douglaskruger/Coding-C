/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: semaphore_reader.c$";
/*
 * Description:
 * These examples use semaphores to ensure that writer and reader
 * processes have exclusive, alternating access to the shared-memory region.
 */
/**********  reader.c  ***********/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

char shm_fn[] = "my_shm";
char sem_fn[] = "my_sem";

/**** READER ****/
int
main()
{
	caddr_t shmptr;
	int shmdes, index;
	sem_t *semdes;
	int SHM_SIZE;

	/* Open the shared memory object */
	SHM_SIZE = sysconf(_SC_PAGE_SIZE);
        printf("SHM_Size = %d\n", SHM_SIZE);

	printf("Shared Memory: shm_open\n");
	if ( (shmdes = shm_open(shm_fn, O_RDWR, 0)) == -1 ) 
	{
		perror("shm_open failure");
		exit(1);
	}

	printf("Shared Memory: mmap\n");
	if ((shmptr = mmap(0, SHM_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED, shmdes,0)) == (caddr_t) -1)
	{
		perror("mmap failure");
		exit(1);
	}

	/* Open the Semaphore */
	printf("Semaphore: sem_open\n");
	semdes = sem_open(sem_fn, 0, 0644, 0);
	if (semdes == (void*) -1)
	{
		perror("sem_open failure");
		exit(1);
	}

	/* Access to the shared memory area */
	for (index = 0; index < 100; index++)
	{
		/* Lock the semaphore */
		printf("Semaphore: sem_wait (lock)\n");
		if (!sem_wait(semdes))
		{
			printf("Reading shared memory shmptr[%d] = %d\n", index, (int)shmptr[index]);
		}

		/* Release the semaphore lock */
		printf("Semaphore: sem_post (release)\n");
		sem_post(semdes);
		sleep(2);
	}

	printf("Shared Memory: munmap\n");
	munmap(shmptr, SHM_SIZE);

	/* Close the shared memory object */
	printf("Shared Memory: close\n");
	close(shmdes);

	/* Close the Semaphore */
	printf("Semaphore: close\n");
	sem_close(semdes);
	sem_unlink(sem_fn);
}
