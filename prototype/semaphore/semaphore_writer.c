/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: semaphore_writer.c$";
/*
 * Description:
 * These examples use semaphores to ensure that writer and reader
 * processes have exclusive, alternating access to the shared-memory region.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

char shm_fn[] = "my_shm";
char sem_fn[] = "my_sem";

/**** WRITER ****/
int
main()
{
	caddr_t shmptr;
	unsigned int mode;
	int shmdes, index;
	sem_t *semdes;
	int SHM_SIZE;

	/* Preallocate a shared memory area */
	SHM_SIZE = sysconf(_SC_PAGE_SIZE);
	printf("SHM_Size = %d\n", SHM_SIZE);

	/* Open the shared memory object */
        printf("Shared Memory: shm_open\n");
	mode = S_IRWXU|S_IRWXG;
	if ( (shmdes = shm_open(shm_fn,O_CREAT|O_RDWR|O_TRUNC, mode)) == -1 ) 
	{
		perror("shm_open failure");
		exit(1);
	}

	/* Truncate the shared memory buffer - if required. */
        printf("Shared Memory: ftruncate\n");
	if (ftruncate(shmdes, SHM_SIZE) == -1)
	{
		perror("ftruncate failure");
		exit(1);
	}

        printf("Shared Memory: mmap\n");
	if ((shmptr = mmap(0, SHM_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED, shmdes,0)) == (caddr_t) -1)
	{
		perror("mmap failure");
		exit(1);
	}

	/* Lock the mapped region into physical memory */
	printf("Shared Memory: mlock\n");
	if (mlock(shmptr,SHM_SIZE) != 0)
	{
		perror("mlock failure");
		exit(1);
	}

	/* Create a semaphore in locked state */
	printf("Semaphore: sem_open\n");
	semdes = sem_open(sem_fn, O_CREAT, 0644, 0);
	if (semdes == (void*)-1)
	{
		perror("sem_open failure");
		exit(1);
	}
	sem_post(semdes);

	/* Access to the shared memory area */
	for (index = 0; index < 100; index++)
	{
                /* Lock the semaphore */
                printf("Semaphore: sem_wait (lock)\n");
                if (!sem_wait(semdes))
                {
			printf("Write %d into the shared memory shmptr[%d]\n", index*2, index);
			shmptr[index]=index*2;
                }

		/* Release the semaphore lock */
		printf("Semaphore: sem_post (release)\n");
		sem_post(semdes);

		sleep(10);
	}

	/* Unmap the shared memory */
	printf("Shared Memory: munmap\n");
	munmap(shmptr, SHM_SIZE);

	/* Close the shared memory object */
        printf("Shared Memory: close\n");
	close(shmdes);

	/* Close the Semaphore */
        printf("Semaphore: close\n");
	sem_close(semdes);

	/* Delete the shared memory object */
	shm_unlink(shm_fn);
}


