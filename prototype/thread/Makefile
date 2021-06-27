# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	thread_example1 thread_example2 thread_example3 

thread_example1: thread_example1.o
	gcc thread_example1.o -o thread_example1

thread_example1.o: thread_example1.c
	gcc -c thread_example1.c -o thread_example1.o

thread_example2: thread_example2.o
	gcc thread_example2.o -o thread_example2

thread_example2.o: thread_example2.c
	gcc -c thread_example2.c -o thread_example2.o

thread_example3: thread_example3.o
	gcc thread_example3.o -o thread_example3

thread_example3.o: thread_example3.c
	gcc -c thread_example3.c -o thread_example3.o

clean:
	rm -f thread_example1.o thread_example1 thread_example2.o thread_example2 \
		thread_example3.o thread_example3 
