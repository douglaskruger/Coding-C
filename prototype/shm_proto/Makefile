# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	shm_reader_test shm_writer_test 

shm_reader_test: shm_reader_test.o
	gcc shm_reader_test.o -o shm_reader_test

shm_reader_test.o: shm_reader_test.c
	gcc -c shm_reader_test.c -o shm_reader_test.o

shm_writer_test: shm_writer_test.o
	gcc shm_writer_test.o -o shm_writer_test

shm_writer_test.o: shm_writer_test.c
	gcc -c shm_writer_test.c -o shm_writer_test.o

clean:
	rm -f shm_reader_test.o shm_reader_test shm_writer_test.o shm_writer_test 
