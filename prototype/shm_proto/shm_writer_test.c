/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: shm_writer_test.c $";

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
#include <time.h>

#define SHM_NAME "/rdm_database_shm"
#define SHM_SIZE 40960
#define SEM_NAME "/rdm_database_sem"

caddr_t shm_ptr;
int     shm_des;
sem_t * sem_des;

int
create_shm(int shm_size, char * shm_name)
{
	/* Preallocate a shared memory area */
	// SHM_SIZE = sysconf(_SC_PAGE_SIZE);
	printf("SHM_Size = %d\n", shm_size);

	/* Open the shared memory object */
        printf("Shared Memory: shm_open\n");
	unsigned int mode = S_IRWXU|S_IRWXG;
	if ( (shm_des = shm_open(shm_name, O_CREAT|O_RDWR|O_TRUNC, mode)) == -1 ) 
	{
		perror("shm_open failure");
		exit(1);
	}

	/* Truncate the shared memory buffer - if required. */
        printf("Shared Memory: ftruncate\n");
	if (ftruncate(shm_des, shm_size) == -1)
	{
		perror("ftruncate failure");
		exit(1);
	}

        printf("Shared Memory: mmap\n");
	if ((shm_ptr = mmap(0, shm_size, PROT_WRITE|PROT_READ, MAP_SHARED, shm_des,0)) == (caddr_t) -1)
	{
		perror("mmap failure");
		exit(1);
	}

	/* Lock the mapped region into physical memory */
	printf("Shared Memory: mlock\n");
	if (mlock(shm_ptr, shm_size) != 0)
	{
		perror("mlock failure");
		exit(1);
	}
	return 1;
}


int
delete_shm()
{
        /* Unmap the shared memory */
        printf("Shared Memory: munmap\n");
        munmap(shm_ptr, SHM_SIZE);

        /* Close the shared memory object */
        printf("Shared Memory: close\n");
        close(shm_des);

        return 1;
}

int
create_sem()
{
        printf("Semaphore: sem_unlink - delete if necessary \n");
        sem_unlink(SEM_NAME);

	/* Create a semaphore in locked state */
	printf("Semaphore: sem_open\n");
	sem_des = sem_open(SEM_NAME, O_CREAT, 0644, 0);
	if (sem_des == (void*)-1)
	{
		perror("sem_open failure");
		exit(1);
	}
	/* Unlock the semaphore */
	sem_post(sem_des);

	return 1;
}


int
delete_sem()
{
        /* Close the Semaphore */
        printf("Semaphore: close\n");
        sem_close(sem_des);

        /* Delete the shared memory object */
        shm_unlink(SEM_NAME);

	return 1;
}

int
startup_db()
{
	create_shm(SHM_SIZE, SHM_NAME);
	create_sem(SEM_NAME);
	return 1;
}

int
shutdown_db()
{
	delete_shm();
	delete_sem();
	return 1;
}

int 
write(float value)
{
	int sem_value;

	/* Access to the shared memory area */
	int index = random()%10;

	/* Lock the semaphore */
	printf("Semaphore: sem_wait (lock)\n");
	if (!sem_wait(sem_des))
	{
		printf("Write %d into the shared memory shm_ptr[%d]\n", index*2, index);
		shm_ptr[index]=index*2;
	}
	if (sem_getvalue(sem_des, &sem_value) == 0)
		printf("Semaphore: sem_getvalue - %d (after sem_wait)\n", sem_value);

	int sleep_time = random()%5;
	printf("Sleeping for %d\n", sleep_time);
	sleep(sleep_time);

	/* Release the semaphore lock */
	printf("Semaphore: sem_post (release)\n");
	sem_post(sem_des);
	if (sem_getvalue(sem_des, &sem_value) == 0)
		printf("Semaphore: sem_getvalue - %d (after sem_post)\n", sem_value);
	return 1;
}

int
initialize_mem()
{
        int sem_value;

        /* Lock the semaphore */
        printf("Semaphore: sem_wait (lock)\n");
        if (!sem_wait(sem_des))
        {
                printf("Initialize the shared memory via shm_ptr\n");
        }
        if (sem_getvalue(sem_des, &sem_value) == 0)
                printf("Semaphore: sem_getvalue - %d (after sem_wait)\n", sem_value);

        /* Initialize the first 1000 records */
        for (int index=0; index<1000; index++)
	{
                shm_ptr[index]=random()%1000;
	}

        /* Release the semaphore lock */
        printf("Semaphore: sem_post (release)\n");
        sem_post(sem_des);
        if (sem_getvalue(sem_des, &sem_value) == 0)
                printf("Semaphore: sem_getvalue - %d (after sem_post)\n", sem_value);
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
	float value = 33.3;

	startup_db();
	initialize_mem();
	while(1)
	{
		write(value);

		int sleep_time = random()%12;
		printf("Sleeping between writes %d\n", sleep_time);
		print_time();
		sleep(sleep_time);
	}
	shutdown_db();
}
