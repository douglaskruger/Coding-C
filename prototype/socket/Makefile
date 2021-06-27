# =============================================================================
#   Copyright © 2020 Skynet Consulting Ltd.
#
#   This file is the property of Skynet Consulting Ltd. and shall not be reproduced,
#   copied, or used as the basis for the manufacture or sale of equipment without
#   the express written permission of Skynet Consulting Ltd.
#   =============================================================================
#   This system was written and tested against Debian 9/10 Linux
#   =============================================================================
all:	socket_1_client socket_1_server socket_2_client socket_2_lib socket_2_server \
	socket_2_stats socket_3_file_transfer_client socket_3_file_transfer_server socket_4_heartbeat_client socket_4_heartbeat_server socket_5 

socket_1_client: socket_1_client.o
	gcc socket_1_client.o -o socket_1_client

socket_1_client.o: socket_1_client.c
	gcc -c socket_1_client.c -o socket_1_client.o

socket_1_server: socket_1_server.o
	gcc socket_1_server.o -o socket_1_server

socket_1_server.o: socket_1_server.c
	gcc -c socket_1_server.c -o socket_1_server.o

socket_2_client: socket_2_client.o
	gcc socket_2_client.o -o socket_2_client

socket_2_client.o: socket_2_client.c
	gcc -c socket_2_client.c -o socket_2_client.o

socket_2_lib: socket_2_lib.o
	gcc socket_2_lib.o -o socket_2_lib

socket_2_lib.o: socket_2_lib.c
	gcc -c socket_2_lib.c -o socket_2_lib.o

socket_2_server: socket_2_server.o
	gcc socket_2_server.o -o socket_2_server

socket_2_server.o: socket_2_server.c
	gcc -c socket_2_server.c -o socket_2_server.o

socket_2_stats: socket_2_stats.o
	gcc socket_2_stats.o -o socket_2_stats

socket_2_stats.o: socket_2_stats.c
	gcc -c socket_2_stats.c -o socket_2_stats.o

socket_3_file_transfer_client: socket_3_file_transfer_client.o
	gcc socket_3_file_transfer_client.o -o socket_3_file_transfer_client

socket_3_file_transfer_client.o: socket_3_file_transfer_client.c
	gcc -c socket_3_file_transfer_client.c -o socket_3_file_transfer_client.o

socket_3_file_transfer_server: socket_3_file_transfer_server.o
	gcc socket_3_file_transfer_server.o -o socket_3_file_transfer_server

socket_3_file_transfer_server.o: socket_3_file_transfer_server.c
	gcc -c socket_3_file_transfer_server.c -o socket_3_file_transfer_server.o

socket_4_heartbeat_client: socket_4_heartbeat_client.o
	gcc socket_4_heartbeat_client.o -o socket_4_heartbeat_client

socket_4_heartbeat_client.o: socket_4_heartbeat_client.c
	gcc -c socket_4_heartbeat_client.c -o socket_4_heartbeat_client.o

socket_4_heartbeat_server: socket_4_heartbeat_server.o
	gcc socket_4_heartbeat_server.o -o socket_4_heartbeat_server

socket_4_heartbeat_server.o: socket_4_heartbeat_server.c
	gcc -c socket_4_heartbeat_server.c -o socket_4_heartbeat_server.o

socket_5: socket_5.o
	gcc socket_5.o -o socket_5

socket_5.o: socket_5.c
	gcc -c socket_5.c -o socket_5.o

clean:
	rm -f socket_1_client.o socket_1_client socket_1_server.o socket_1_server \
		socket_2_client.o socket_2_client socket_2_lib.o socket_2_lib socket_2_server.o socket_2_server \
		socket_2_stats.o socket_2_stats socket_3_file_transfer_client.o socket_3_file_transfer_client socket_3_file_transfer_server.o socket_3_file_transfer_server \
		socket_4_heartbeat_client.o socket_4_heartbeat_client socket_4_heartbeat_server.o socket_4_heartbeat_server socket_5.o socket_5 
