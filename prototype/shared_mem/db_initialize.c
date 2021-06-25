/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: db_initialize.c$";

// *****************************************************************************
// Description:
//    The Real-Time Database Manager
// *****************************************************************************
#include <sys/mman.h>
#include "database_struc.h"
#include "general_socket.h"

// *****************************************************************************
// Define the Database Shared Memory Space
// *****************************************************************************
void* config_shmem; 
void* runtime_shmem;

// *****************************************************************************
// Global Variables
// *****************************************************************************
analog_in_alias * my_analog_in;

// *****************************************************************************
// create_shared_memory
// *****************************************************************************
void* 
create_shared_memory(size_t size) 
{
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

// *****************************************************************************
// initialize_memory
// *****************************************************************************
void
initialize_memory()
{
	// Create the Configuration database memory space
	config_shmem = create_shared_memory(409600);

	// Create the Runtime database memory space
	runtime_shmem = create_shared_memory(409600);
}

// *****************************************************************************
// update_shm_values
// *****************************************************************************
void
update_shm_values()
{
	int i;
	// Populate the shared memory
	for (i=0;i < 1000;i++)
	{
		my_analog_in[i].value = rand();
	} 
}

// *****************************************************************************
// print_shm_values
// *****************************************************************************
void
print_shm_values(char * process_name)
{
	int i;
	// Print shared memory
	for (i=0;i < 10; i++)
	{
		printf("Client: %s,  %f\n",process_name, my_analog_in[i].value);
	} 
}
 

// *****************************************************************************
// main
// *****************************************************************************
int main() {
	initialize_memory();

	my_analog_in = config_shmem;

	// Seed the randome generator
	srand(1000);

	int pid = fork();
	printf("Hello World\n");

	if (pid == 0) 
	{
		for (int i=0; i<5;i++) 
		{
			printf("P1 - update\n");
			update_shm_values();
			printf("P2 - print parent\n");
			print_shm_values("Parent");
			printf("P3 - update\n");
			update_shm_values();
			printf("P4 - print parent\n");
			print_shm_values("Parent");
		}
	} else {
		for (int i=0; i<5;i++) 
		{
			printf("C1 - print child\n");
			print_shm_values("Child");
			sleep(1);
			printf("C2 - update\n");
			update_shm_values();
			printf("C3 - print child\n");
			print_shm_values("Child");
		}
	}
	printf("Good bye World\n");
}
