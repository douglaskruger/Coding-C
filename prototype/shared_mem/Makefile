# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	db_initialize shared_mem_demo shared_mem_open sharedmem_example shm_address_change \
	shm_basic shm_client shm_mmap_demo shm_reader shm_server shm_thread \
	shm_writer 

db_initialize: db_initialize.o
	gcc db_initialize.o -o db_initialize

db_initialize.o: db_initialize.c
	gcc -c db_initialize.c -o db_initialize.o

shared_mem_demo: shared_mem_demo.o
	gcc shared_mem_demo.o -o shared_mem_demo

shared_mem_demo.o: shared_mem_demo.c
	gcc -c shared_mem_demo.c -o shared_mem_demo.o

shared_mem_open: shared_mem_open.o
	gcc shared_mem_open.o -o shared_mem_open

shared_mem_open.o: shared_mem_open.c
	gcc -c shared_mem_open.c -o shared_mem_open.o

sharedmem_example: sharedmem_example.o
	gcc sharedmem_example.o -o sharedmem_example

sharedmem_example.o: sharedmem_example.c
	gcc -c sharedmem_example.c -o sharedmem_example.o

shm_address_change: shm_address_change.o
	gcc shm_address_change.o -o shm_address_change

shm_address_change.o: shm_address_change.c
	gcc -c shm_address_change.c -o shm_address_change.o

shm_basic: shm_basic.o
	gcc shm_basic.o -o shm_basic

shm_basic.o: shm_basic.c
	gcc -c shm_basic.c -o shm_basic.o

shm_client: shm_client.o
	gcc shm_client.o -o shm_client

shm_client.o: shm_client.c
	gcc -c shm_client.c -o shm_client.o

shm_mmap_demo: shm_mmap_demo.o
	gcc shm_mmap_demo.o -o shm_mmap_demo

shm_mmap_demo.o: shm_mmap_demo.c
	gcc -c shm_mmap_demo.c -o shm_mmap_demo.o

shm_reader: shm_reader.o
	gcc shm_reader.o -o shm_reader

shm_reader.o: shm_reader.c
	gcc -c shm_reader.c -o shm_reader.o

shm_server: shm_server.o
	gcc shm_server.o -o shm_server

shm_server.o: shm_server.c
	gcc -c shm_server.c -o shm_server.o

shm_thread: shm_thread.o
	gcc shm_thread.o -o shm_thread

shm_thread.o: shm_thread.c
	gcc -c shm_thread.c -o shm_thread.o

shm_writer: shm_writer.o
	gcc shm_writer.o -o shm_writer

shm_writer.o: shm_writer.c
	gcc -c shm_writer.c -o shm_writer.o

clean:
	rm -f db_initialize.o db_initialize shared_mem_demo.o shared_mem_demo \
		shared_mem_open.o shared_mem_open sharedmem_example.o sharedmem_example shm_address_change.o shm_address_change \
		shm_basic.o shm_basic shm_client.o shm_client shm_mmap_demo.o shm_mmap_demo \
		shm_reader.o shm_reader shm_server.o shm_server shm_thread.o shm_thread \
		shm_writer.o shm_writer 
