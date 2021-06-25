/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: shm_basic.c$";

/*
 * Description:
 * Basic shared memory program - that uses a fork. One forked process will write and 
 * the other will read.
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

void* create_shared_memory(size_t size) {
	// Our memory buffer will be readable and writable:
	int protection = PROT_READ | PROT_WRITE;

	// The buffer will be shared (meaning other processes can access it), but
	// anonymous (meaning third-party processes cannot obtain an address for it),
	// so only this process and its children will be able to use it:
	int visibility = MAP_ANONYMOUS | MAP_SHARED;

	// The remaining parameters to `mmap()` are not important for this use case,
	// but the manpage for `mmap` explains their purpose.
	return mmap(NULL, size, protection, visibility, 0, 0);
}

int 
main() 
{
	char* parent_message = "hello";  // parent process will write this message
	char* child_message = "goodbye"; // child process will then write this one

	void* shmem = create_shared_memory(128);

	memcpy(shmem, parent_message, strlen(parent_message));

	int pid = fork();

	if (pid == 0) {
		printf("Child read: %s\n", (char *)shmem);
		memcpy(shmem, child_message, strlen(child_message));
		printf("Child wrote: %s\n", (char *)shmem);
	} 
	else 
	{
		printf("Parent read: %s\n", (char *)shmem);
		sleep(1);
		printf("After 1s, parent read: %s\n", (char *)shmem);
	}
}
