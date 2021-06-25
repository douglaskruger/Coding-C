/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: shm_reader_test.c $";

/*
 * Description:
 * These examples use semaphores to ensure that writer and reader
 * processes have exclusive, alternating access to the shared-memory region.
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <time.h>

#define SHM_NAME "/rdm_database_shm"
#define SHM_SIZE 40960
#define SEM_NAME "/rdm_database_sem"

caddr_t shm_ptr;
int     shm_des;
sem_t * sem_des;
int SHM_SIZE = 409600;

int
connect()
{

	/* Open the shared memory object */
	// SHM_SIZE = sysconf(_SC_PAGE_SIZE);
        printf("SHM_Size = %d\n", SHM_SIZE);

	printf("Shared Memory: shm_open\n");
	if ( (shm_des = shm_open(SHM_NAME, O_RDWR, 0)) == -1 ) 
	{
		perror("shm_open failure");
		exit(1);
	}

	printf("Shared Memory: mmap\n");
	if ((shm_ptr = mmap(0, SHM_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED, shm_des,0)) == (caddr_t) -1)
	{
		perror("mmap failure");
		exit(1);
	}

	/* Open the Semaphore */
	printf("Semaphore: sem_open\n");
	sem_des = sem_open(SEM_NAME, 0, 0644, 0);
	if (sem_des == (void*) -1)
	{
		perror("sem_open failure");
		exit(1);
	}
	return 1;
}

int
read(float value)
{
	int sem_value;

	/* Lock the semaphore */
	printf("Semaphore: sem_wait (lock)\n");
	if (!sem_wait(sem_des))
	{
		/* Access to the shared memory area */
		for (int index = 0; index < 10; index++)
		{
			printf("Reading shared memory shm_ptr[%d] = %d\n", index, (int)shm_ptr[index]);
		}
	}
	if (sem_getvalue(sem_des, &sem_value) == 0)
		printf("Semaphore: sem_getvalue - %d (after sem_wait)\n", sem_value);

	/* Release the semaphore lock */
	printf("Semaphore: sem_post (release)\n");
	sem_post(sem_des);
	if (sem_getvalue(sem_des, &sem_value) == 0)
		printf("Semaphore: sem_getvalue - %d (after sem_post)\n", sem_value);
	return 1;
}

int
disconnect()
{
	printf("Shared Memory: munmap\n");
	munmap(shm_ptr, SHM_SIZE);

	/* Close the shared memory object */
	printf("Shared Memory: close\n");
	close(shm_des);

	/* Close the Semaphore */
	printf("Semaphore: close\n");
	sem_close(sem_des);
	sem_unlink(SEM_NAME);

	return 1;
}

void
print_time()
{
        struct tm       curTm;
        struct timespec now;

        clock_gettime(CLOCK_REALTIME, &now);
        gmtime_r(&(now.tv_sec), &curTm);
        printf("Time is: %04d-%02d-%02dT%02d:%02d:%02d.%03ldZ\n\n",
             curTm.tm_year + 1900, curTm.tm_mon + 1, curTm.tm_mday,
             curTm.tm_hour, curTm.tm_min, curTm.tm_sec, now.tv_nsec / 1000000);
}

int
main()
{
	float value = 0.0;

	connect();
	while (1) 
	{
		read(value);

                int sleep_time = random()%2;
                printf("Sleeping for %d\n", sleep_time);
                print_time();
                sleep(sleep_time);
	}
	disconnect();
}
