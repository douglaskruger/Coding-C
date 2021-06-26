# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	get_ip multicast_basic multicast_thread-2 multicast_thread-3 multicast_thread 

get_ip: get_ip.o
	gcc get_ip.o -o get_ip

get_ip.o: get_ip.c
	gcc -c get_ip.c -o get_ip.o

multicast_basic: multicast_basic.o
	gcc multicast_basic.o -o multicast_basic

multicast_basic.o: multicast_basic.c
	gcc -c multicast_basic.c -o multicast_basic.o

multicast_thread-2: multicast_thread-2.o
	gcc multicast_thread-2.o -o multicast_thread-2

multicast_thread-2.o: multicast_thread-2.c
	gcc -c multicast_thread-2.c -o multicast_thread-2.o

multicast_thread-3: multicast_thread-3.o
	gcc multicast_thread-3.o -o multicast_thread-3

multicast_thread-3.o: multicast_thread-3.c
	gcc -c multicast_thread-3.c -o multicast_thread-3.o

multicast_thread: multicast_thread.o
	gcc multicast_thread.o -o multicast_thread

multicast_thread.o: multicast_thread.c
	gcc -c multicast_thread.c -o multicast_thread.o

clean:
	rm -f get_ip.o get_ip multicast_basic.o multicast_basic \
		multicast_thread-2.o multicast_thread-2 multicast_thread-3.o multicast_thread-3 multicast_thread.o multicast_thread 
