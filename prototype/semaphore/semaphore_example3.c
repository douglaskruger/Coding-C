/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: semaphore_example3.c $";

/*
 * Description:
 *   The following program sends or receives semaphores.
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

char sem_fn[] = "/my_sem";

int 
main()
{
        sem_t *semdes;
	int	sem_value;

        printf("Semaphore: sem_unlink - delete if necessary \n");
	sem_unlink(sem_fn);

        printf("Semaphore: sem_open - create if necessary\n");
        semdes = sem_open(sem_fn, O_CREAT, 0644, 0);
        if (semdes == (void*)-1)
        {
                perror("sem_open failure");
                exit(1);
        }
	if (sem_getvalue(semdes, &sem_value) == 0)
		printf("Semaphore: sem_getvalue - %d - initial value\n", sem_value);
	sem_trywait(semdes);
	if (sem_getvalue(semdes, &sem_value) == 0)
		printf("Semaphore: sem_getvalue - %d - sem_trywait value\n", sem_value);
			
	for (int i=0; i<100; i++)
	{
		printf("Loop - %d of 100\n", i);
		printf("Semaphore: sem_post - %ld\n", (long int)semdes);
		sem_post(semdes);
		if (sem_getvalue(semdes, &sem_value) == 0)
			printf("Semaphore: sem_getvalue - %d (after sem_post)\n", sem_value);

		printf("Semaphore: sem_wait - %ld\n", (long int)semdes);
		sem_wait(semdes);
		if (sem_getvalue(semdes, &sem_value) == 0)
			printf("Semaphore: sem_getvalue - %d (after sem_wait)\n", sem_value);
			
                printf("Simulate work by sleep\n");
		sleep(5);
	}

	// Wait 5 minutes
	sleep(600);
	return 1;
}
