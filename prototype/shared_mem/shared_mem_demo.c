/* =============================================================================
   Copyright © 2019 Skynet Consulting Ltd.

   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
   copied, or used as the basis for the manufacture or sale of equipment without
   the express written permission of Skynet Consulting Ltd.
   =============================================================================
*/
static const char module_id[] __attribute__((used)) = "$Id: shared_mem_demo.c$";

/*
 * Description:
 * This program locks the virtual memory address that was returned from the 
 * mmap() function into memory. 
 */
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include "general_socket.h"

int
main()
{
	int fd;
	caddr_t pg_addr;

	int size = 40960;
	int mode =  S_IRWXO|S_IRWXG|S_IRWXU;

	/* Create a file */
	fd = shm_open("example", O_RDWR|O_CREAT, mode);
	printf("Exec: shm_open\n");
	if(fd < 0)
	{
		perror("open error ");
		exit(1);
	}

	/* Set the size */
	if((ftruncate(fd, size)) == -1)
	{
		perror("ftruncate failure");
		exit(1);
	}

	/* Map the file into the address space of the process */
	pg_addr = (caddr_t) mmap(0, size, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_SHARED, fd, 0);
	if(pg_addr == (caddr_t) -1)
	{
		perror("mmap failure");
		exit(1);
	}

	/* Lock the mapped region into memory */
	if(mlock(pg_addr,size) != 0)
	{
		perror("mlock failure");
		exit(1);
	}

	/* Unmap of the address region removes the memory lock established on the 
       address region by this process   
    */
	sleep(15);
	printf("Exec: mumap\n");
	if (munmap(pg_addr, size) < 0)
		perror("unmap error");
	printf("Exec: close\n");
	close(fd);
	shm_unlink("example");
	exit(1);
}
