# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	posix_queue queue_client queue_server 

posix_queue: posix_queue.o
	gcc posix_queue.o -o posix_queue

posix_queue.o: posix_queue.c
	gcc -c posix_queue.c -o posix_queue.o

queue_client: queue_client.o
	gcc queue_client.o -o queue_client

queue_client.o: queue_client.c
	gcc -c queue_client.c -o queue_client.o

queue_server: queue_server.o
	gcc queue_server.o -o queue_server

queue_server.o: queue_server.c
	gcc -c queue_server.c -o queue_server.o

clean:
	rm -f posix_queue.o posix_queue queue_client.o queue_client \
		queue_server.o queue_server 
